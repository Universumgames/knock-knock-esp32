#include "PatternRecorder.h"

#include "AnalogRead.h"

#define PATTERN_RECORDER_ANALOG_BUFFER_SIZE 256
#define PATTERN_RECORDER_ANALOG_CHANNEL ((adc_channel_t)ADC_CHANNEL_0)
#define PATTERN_RECORDER_GAIN ((adc_atten_t)ADC_ATTEN_DB_0)
#define ECHO_TASK_STACK_SIZE 2048

static bool patternRecorderInitialized = false;

static const char* TAG_PATTERN_RECORDER = "PatternRecorder";

union {
    adc_continuous_handle_t handle;
    uint8_t value[PATTERN_RECORDER_ANALOG_BUFFER_SIZE];
    adc_channel_t* channels;
    adc_continuous_evt_cbs_t cbs;
} PatternRecorderData;

static TaskHandle_t s_task_handle;

static bool IRAM_ATTR s_conv_done_cb(adc_continuous_handle_t handle, const adc_continuous_evt_data_t* edata, void* user_data) {
    BaseType_t mustYield = pdFALSE;
    // Notify that ADC continuous driver has done enough number of conversions
    vTaskNotifyGiveFromISR(s_task_handle, &mustYield);

    return (mustYield == pdTRUE);
}

static void analogReadTask(void* pvParameters) {
    s_task_handle = xTaskGetCurrentTaskHandle();
    uint64_t lastRead = pdTICKS_TO_MS(xTaskGetTickCount());
    while (1) {
        uint32_t read = read_continuous(PatternRecorderData.handle, PatternRecorderData.value, PATTERN_RECORDER_ANALOG_BUFFER_SIZE);
        if (read > 0) {
            uint64_t now = pdTICKS_TO_MS(xTaskGetTickCount());
            uint64_t delta = now - lastRead;
            lastRead = now;
            LOGI(TAG_PATTERN_RECORDER, "Read %lu values in %llu ms", read, delta);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

bool initPatternRecorder() {
    if (patternRecorderInitialized) {
        return true;
    }
    bool ret = true;

    PatternRecorderData.channels = (adc_channel_t*)calloc(1, sizeof(adc_channel_t));
    PatternRecorderData.channels[0] = PATTERN_RECORDER_ANALOG_CHANNEL;
    PatternRecorderData.cbs.on_conv_done = s_conv_done_cb;
    ret &= continuous_init(PatternRecorderData.channels, 1, PATTERN_RECORDER_GAIN, &PatternRecorderData.handle);
    CHECK_DO(!ret, LOGE(TAG_PATTERN_RECORDER, "Failed to initialize continuous ADC"); goto error);

    CHECK_ESP_DO(adc_continuous_register_event_callbacks(PatternRecorderData.handle, &PatternRecorderData.cbs, NULL),
                 LOGE(TAG_PATTERN_RECORDER, "Failed to register event callbacks");
                 goto error);

    CHECK_ESP_DO(adc_continuous_start(PatternRecorderData.handle),
                 LOGE(TAG_PATTERN_RECORDER, "Failed to start ADC continuous");
                 goto error);

    xTaskCreate(analogReadTask, "analog_read_task", ECHO_TASK_STACK_SIZE, NULL, 5, NULL);
    ESP_LOGI(TAG_PATTERN_RECORDER, "ADC continuous started");
    goto end;

error:
    ret = false;
end:
    patternRecorderInitialized = ret;
    return ret;
}