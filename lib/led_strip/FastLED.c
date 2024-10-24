#include "FastLed.h"

#include <driver/gpio.h>
#include <driver/i2s_std.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <hal/spi_hal.h>
#include <string.h>

#include "ws2812.h"

const char* TAG_FAST_LED = "FastLED";

struct __FastLED_Config_internal {
    gpio_num_t pin_number;
    ws2812_pixel_t* led_data;
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
        .led_data = (ws2812_pixel_t*)calloc(sizeof(ws2812_pixel_t), length),
        .lengthRBGStrip = length,
    };

    ws2812_init();

    showLED(config);

    return config;
}

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= config->lengthRBGStrip) {
        ESP_LOGE(TAG_FAST_LED, "Index out of range: %d", index);
        return;
    }
    config->led_data[index] = (ws2812_pixel_t){
        .red = red,
        .green = green,
        .blue = blue,
    };
}

void showLED(FastLEDConfig* config) {
    ws2812_update(config->led_data);
}