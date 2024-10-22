#include "FastLed.h"

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <string.h>

const char* TAG_FAST_LED = "FastLED";

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000  // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)

FastLEDConfig* initFastLED(int length, gpio_num_t pin_number) {
    rmt_tx_channel_config_t tx_chan_config = {
        .gpio_num = pin_number,          // select the GPIO pin
        .clk_src = RMT_CLK_SRC_DEFAULT,  // select source clock
        .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
        .mem_block_symbols = 64,  // increase the block size can make the LED less flickering
        .trans_queue_depth = 4,   // set the number of transactions that can be pending in the background
    };
    led_strip_encoder_config_t encoder_config = {
        .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
    };
    return __initFastLED(length, tx_chan_config, encoder_config);
}

struct __FastLED_Config_internal {
    rmt_channel_handle_t led_chan;
    rmt_encoder_handle_t led_encoder;
    rmt_transmit_config_t tx_config;
    led_strip_encoder_config_t encoder_config;
    rmt_tx_channel_config_t tx_chan_config;
    uint8_t* led_strip_pixels;
    int lengthRGB;
    int lengthPixels;
};

FastLEDConfig* __initFastLED(int length, rmt_tx_channel_config_t _tx_chan_config, led_strip_encoder_config_t _encoder_config) {
    esp_log_level_set(TAG_FAST_LED, ESP_LOG_VERBOSE);
    FastLEDConfig* config = (FastLEDConfig*)malloc(sizeof(FastLEDConfig));
    config->lengthRGB = length;
    config->lengthPixels = length * 3;
    config->led_strip_pixels = (uint8_t*)calloc(sizeof(int), config->lengthPixels);

    config->tx_chan_config = _tx_chan_config;
    ESP_ERROR_CHECK(rmt_new_tx_channel(&config->tx_chan_config, &config->led_chan));

    ESP_LOGV(TAG_FAST_LED, "Install led strip encoder");

    config->tx_config.loop_count = 0;
    config->encoder_config = _encoder_config;

    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&config->encoder_config, &config->led_encoder));

    ESP_LOGD(TAG_FAST_LED, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(config->led_chan));
    // turn off all leds
    memset(config->led_strip_pixels, 0, config->lengthPixels * sizeof(uint8_t));
    showLED(config);
    ESP_LOGD(TAG_FAST_LED, "FastLED initialized, LED strip length on pin %d: %d", config->tx_chan_config.gpio_num, length);
    return config;
}

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= config->lengthRGB) {
        ESP_LOGE(TAG_FAST_LED, "Index out of range: %d", index);
        return;
    }
    config->led_strip_pixels[index * 3] = green;
    config->led_strip_pixels[index * 3 + 1] = blue;
    config->led_strip_pixels[index * 3 + 2] = red;
}

void showLED(FastLEDConfig* config) {
    ESP_ERROR_CHECK(rmt_transmit(config->led_chan, config->led_encoder, config->led_strip_pixels, config->lengthPixels, &config->tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(config->led_chan, portMAX_DELAY));
}