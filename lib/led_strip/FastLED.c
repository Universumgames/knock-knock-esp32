#include "FastLed.h"

#include <driver/gpio.h>
#include <driver/i2s_std.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <hal/spi_hal.h>
#include <string.h>

const char* TAG_FAST_LED = "FastLED";

#define WS1812_ENCODED_BYTES_PER_BYTE (4)
#define WS2812_BYTES_PER_LED (3 * WS1812_ENCODED_BYTES_PER_BYTE)
#define SAMPLE_RATE (93750)
#define ZERO_BUFFER 48

static const uint16_t bitpatterns[4] = {0x88, 0x8e, 0xe8, 0xee};

/**
 * @brief Clever way to encode the WS2812 protocol into SPI bits
 *
 * @param data the byte to encode
 * @param buf the buffer to write the encoded data to
 */
void set_data_bit(uint8_t data, uint8_t* buf) {
    *(buf + 0) = bitpatterns[(data >> 6) & 0x03];
    *(buf + 1) = bitpatterns[(data >> 4) & 0x03];
    *(buf + 2) = bitpatterns[(data >> 2) & 0x03];
    *(buf + 3) = bitpatterns[(data >> 0) & 0x03];
}

/**
 * @brief Generate the data for a single LED
 *
 * @param index the index of the LED
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 * @param buf the buffer to write the data to
 */
void generate_data(uint32_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t* buf) {
    uint8_t* startAddr = buf + index * WS2812_BYTES_PER_LED;
    memset(startAddr, 0, WS2812_BYTES_PER_LED);
    set_data_bit(green, startAddr);
    set_data_bit(red, startAddr + WS1812_ENCODED_BYTES_PER_BYTE);
    set_data_bit(blue, startAddr + WS1812_ENCODED_BYTES_PER_BYTE * 2);
}

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB_LED;

struct __FastLED_Config_internal {
    gpio_num_t pin_number;
    RGB_LED* led_data;
    int lengthRBGStrip;
    uint8_t* encoded_led_data;
    int lengthEncoded;

    i2s_chan_handle_t tx_handle;
    i2s_chan_config_t chan_cfg;
    i2s_std_config_t std_cfg;
};

FastLEDConfig* initFastLED(int length, gpio_num_t pin_number) {
    FastLEDConfig* config = (FastLEDConfig*)calloc(sizeof(FastLEDConfig), 1);
    *config = (FastLEDConfig){
        .pin_number = pin_number,
        .led_data = (RGB_LED*)calloc(sizeof(RGB_LED), length),
        .lengthRBGStrip = length,
        .encoded_led_data = (uint8_t*)calloc(sizeof(uint8_t), length * WS2812_BYTES_PER_LED),
        .lengthEncoded = length * WS2812_BYTES_PER_LED,

    };

    config->chan_cfg = (i2s_chan_config_t)I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    i2s_new_channel(&config->chan_cfg, &config->tx_handle, NULL);
    config->std_cfg = (i2s_std_config_t){
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(93750),
        .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
            .bclk = I2S_GPIO_UNUSED,
            .ws = I2S_GPIO_UNUSED,
            .dout = pin_number,
            .din = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };

    i2s_channel_init_std_mode(config->tx_handle, &config->std_cfg);
    i2s_channel_enable(config->tx_handle);

    showLED(config);
    writeLED(config, 0, 128, 128, 128);
    showLED(config);

    return config;
}

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= config->lengthRBGStrip) {
        ESP_LOGE(TAG_FAST_LED, "Index out of range: %d", index);
        return;
    }
    config->led_data[index] = (RGB_LED){
        .red = red,
        .green = green,
        .blue = blue,
    };
    generate_data(index, red, green, blue, config->encoded_led_data);
}

void showLED(FastLEDConfig* config) {
    size_t bytes_written = 0;
    i2s_channel_write(config->tx_handle, config->encoded_led_data, config->lengthEncoded, NULL, pdMS_TO_TICKS(100));
}