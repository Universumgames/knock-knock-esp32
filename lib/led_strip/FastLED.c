#include "FastLed.h"

#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"

const char* TAG_FAST_LED = "FastLED";

struct __FastLED_Config_internal {
    rmt_channel_handle_t led_chan;
    rmt_encoder_handle_t led_encoder;
    rmt_transmit_config_t tx_config;
    led_strip_encoder_config_t* encoder_config;
    uint8_t* led_strip_pixels;
    int length;
};

FastLEDConfig* initFastLED(int length, rmt_tx_channel_config_t* tx_chan_config, led_strip_encoder_config_t* encoder_config) {
    esp_log_level_set(TAG_FAST_LED, ESP_LOG_VERBOSE);
    FastLEDConfig* config = (FastLEDConfig*)malloc(sizeof(FastLEDConfig));
    config->length = length;
    config->led_strip_pixels = (uint8_t*)calloc(sizeof(int), length * 3);

    ESP_ERROR_CHECK(rmt_new_tx_channel(tx_chan_config, &config->led_chan));

    ESP_LOGD(TAG_FAST_LED, "Install led strip encoder");

    config->tx_config.loop_count = 0;
    config->encoder_config = encoder_config;

    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(config->encoder_config, &config->led_encoder));

    ESP_LOGD(TAG_FAST_LED, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(config->led_chan));
    // turn off all leds
    memset(config->led_strip_pixels, 0, length * 3);
    showLED(config);
    return config;
}

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue) {
    config->led_strip_pixels[index * 3] = green;
    config->led_strip_pixels[index * 3 + 1] = blue;
    config->led_strip_pixels[index * 3 + 2] = red;
}

void showLED(FastLEDConfig* config) {
    ESP_ERROR_CHECK(rmt_transmit(config->led_chan, config->led_encoder, config->led_strip_pixels, config->length, &config->tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(config->led_chan, portMAX_DELAY));
}