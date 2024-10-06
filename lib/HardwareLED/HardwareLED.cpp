#include "HardwareLED.h"

#include <string.h>

#include "driver/rmt_tx.h"
#include "esp_log.h"
#include "led_strip_encoder.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000  // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define RMT_LED_STRIP_GPIO_NUM ((gpio_num_t)8)

#define EXAMPLE_LED_NUMBERS 1
#define EXAMPLE_CHASE_SPEED_MS 10

static uint8_t led_strip_pixels[EXAMPLE_LED_NUMBERS * 3];

const char *TAG = "HardwareLED";

static rmt_channel_handle_t led_chan = NULL;

rmt_transmit_config_t tx_config = {
    .loop_count = 0,  // no transfer loop
};

static rmt_encoder_handle_t led_encoder = NULL;
led_strip_encoder_config_t encoder_config = {
    .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
};

void initHardwareLED() {
    rmt_tx_channel_config_t tx_chan_config = {
        .gpio_num = RMT_LED_STRIP_GPIO_NUM,
        .clk_src = RMT_CLK_SRC_DEFAULT,  // select source clock
        .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
        .mem_block_symbols = 64,  // increase the block size can make the LED less flickering
        .trans_queue_depth = 4,   // set the number of transactions that can be pending in the background
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &led_chan));

    ESP_LOGD(TAG, "Install led strip encoder");

    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&encoder_config, &led_encoder));

    ESP_LOGD(TAG, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(led_chan));

    ESP_LOGD(TAG, "Start LED rainbow chase");
}

void writeLED(uint8_t red, uint8_t green, uint8_t blue) {
    led_strip_pixels[0] = red;
    led_strip_pixels[1] = green;
    led_strip_pixels[2] = blue;
}

void show() {
    ESP_ERROR_CHECK(rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(led_chan, portMAX_DELAY));
    vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
}