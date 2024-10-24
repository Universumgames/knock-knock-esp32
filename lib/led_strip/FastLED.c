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
    LED_Pixel* led_data;
    int lengthRBGStrip;
    uint8_t* encoded_led_data;
    int lengthEncoded;

    WS2812Config* ws2812_config;
};

FastLEDConfig* initFastLED(int length, gpio_num_t pin_number) {
    FastLEDConfig* config = (FastLEDConfig*)calloc(sizeof(FastLEDConfig), 1);
    *config = (FastLEDConfig){
        .pin_number = pin_number,
        .led_data = (LED_Pixel*)calloc(sizeof(LED_Pixel), length),
        .lengthRBGStrip = length,
        .ws2812_config = create_ws2812_encoder(pin_number, length),
    };

    showLED(config);

    return config;
}

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= config->lengthRBGStrip) {
        ESP_LOGE(TAG_FAST_LED, "Index out of range: %d", index);
        return;
    }
    config->led_data[index] = (LED_Pixel){
        .red = red,
        .green = green,
        .blue = blue,
    };
    setWS2812Pixel(config->ws2812_config, index, red, green, blue);
}

void showLED(FastLEDConfig* config) {
    showWS2812(config->ws2812_config);
}