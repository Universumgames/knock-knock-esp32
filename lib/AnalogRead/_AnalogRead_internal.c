#include "_AnalogRead_internal.h"

const static char* TAG_ANALOG_READ = "AnalogRead";

#define READ_LEN (SOC_ADC_DIGI_DATA_BYTES_PER_CONV * 64)

bool continuous_init(const adc_channel_t* channel, const uint8_t channel_num,
                     adc_atten_t atten, adc_continuous_handle_t* out_handle) {
    adc_continuous_handle_t handle = NULL;

    adc_continuous_handle_cfg_t adc_config = {
        .max_store_buf_size = 1024,
        .conv_frame_size = READ_LEN,
    };
    LOGI(TAG_ANALOG_READ, "Creating continuous ADC handle");
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &handle));

    adc_continuous_config_t dig_cfg = {
        .sample_freq_hz = 20 * 1000,
        .conv_mode = ADC_CONV_SINGLE_UNIT_1,
        .format =
            ADC_DIGI_OUTPUT_FORMAT_TYPE2, // 12 bit // ESP32C3 has 12 bit ADC
    };

    adc_digi_pattern_config_t adc_pattern[SOC_ADC_PATT_LEN_MAX] = {0};
    dig_cfg.pattern_num = channel_num;

    LOGI(TAG_ANALOG_READ, "Setting up continuous ADC channels");
    for (int i = 0; i < channel_num; i++) {
        adc_pattern[i].atten = atten;
        adc_pattern[i].channel = channel[i] & 0x7;
        adc_pattern[i].unit = ADC_UNIT_1;
        adc_pattern[i].bit_width = SOC_ADC_DIGI_MAX_BITWIDTH;

        LOGI(TAG_ANALOG_READ, "adc_pattern[%d].atten is :%" PRIx8, i,
             adc_pattern[i].atten);
        LOGI(TAG_ANALOG_READ, "adc_pattern[%d].channel is :%" PRIx8, i,
             adc_pattern[i].channel);
        LOGI(TAG_ANALOG_READ, "adc_pattern[%d].unit is :%" PRIx8, i,
             adc_pattern[i].unit);
    }
    dig_cfg.adc_pattern = adc_pattern;

    ESP_ERROR_CHECK(adc_continuous_config(handle, &dig_cfg));
    LOGI(TAG_ANALOG_READ, "Continuous ADC channel setup done");

    *out_handle = handle;

    return true;
}

uint32_t read_continuous(adc_continuous_handle_t handle, uint8_t* valueBuf,
                         size_t bufSize) {
    uint32_t out_length = 0;
    esp_err_t ret =
        adc_continuous_read(handle, valueBuf, bufSize, &out_length, 1000);
    if (ret != ESP_OK) {
        LOGE(TAG_ANALOG_READ, "adc_continuous_read error %d", ret);
    }
    return out_length;
}

bool adc_calibration_init(adc_unit_t unit, adc_channel_t channel,
                          adc_atten_t atten, adc_cali_handle_t* out_handle) {
    adc_cali_handle_t handle = NULL;
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        LOGI(TAG_ANALOG_READ, "calibration scheme version is %s",
             "Curve Fitting");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        LOGI(TAG_ANALOG_READ, "calibration scheme version is %s",
             "Line Fitting");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT,
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, &handle);
        if (ret == ESP_OK) {
            calibrated = true;
        }
    }
#endif

    *out_handle = handle;
    if (ret == ESP_OK) {
        LOGI(TAG_ANALOG_READ, "Calibration Success");
    } else if (ret == ESP_ERR_NOT_SUPPORTED || !calibrated) {
        LOGW(TAG_ANALOG_READ, "eFuse not burnt, skip software calibration");
    } else {
        LOGE(TAG_ANALOG_READ, "Invalid arg or no memory");
    }

    return calibrated;
}

bool init_oneshot(adc_unit_t adc_unit, adc_atten_t attenuation,
                  adc_channel_t channel, adc_oneshot_unit_handle_t* out_handle,
                  adc_cali_handle_t* out_cali_handle) {
    adc_oneshot_unit_handle_t adc_oneshot_handle;
    adc_oneshot_unit_init_cfg_t adc_oneshot_unit_init_cfg = {
        .unit_id = adc_unit,
    };

    esp_err_t err =
        adc_oneshot_new_unit(&adc_oneshot_unit_init_cfg, &adc_oneshot_handle);
    ESP_ERROR_CHECK(err);

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = attenuation,
    };

    err = adc_oneshot_config_channel(adc_oneshot_handle, channel, &config);
    ESP_ERROR_CHECK(err);

    adc_cali_handle_t adc_cali_handle = NULL;
    bool calibrated =
        adc_calibration_init(adc_unit, channel, attenuation, &adc_cali_handle);

    *out_handle = adc_oneshot_handle;
    if (out_cali_handle) {
        *out_cali_handle = adc_cali_handle;
    }

    return calibrated;
}

void read_oneshot(adc_oneshot_unit_handle_t handle, adc_channel_t channel,
                  int* value) {
    adc_oneshot_read(handle, channel, value);
}

void readVoltage_oneshot(adc_oneshot_unit_handle_t handle,
                         adc_channel_t channel, adc_cali_handle_t cali_handle,
                         int* voltage) {
    int value = 0;
    read_oneshot(handle, channel, &value);
    adc_cali_raw_to_voltage(cali_handle, value, voltage);
}