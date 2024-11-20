#include "ws2812.h"

#include <driver/rmt_encoder.h>
#include <driver/rmt_tx.h>
#include <esp_err.h>

#include "FastLed.h"

#include <portmacro.h>

#define RMT_LED_STRIP_RESOLUTION_HZ                                            \
    10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high
             // resolution)
#define WS2812_BYTES_PER_PIXEL 3

static const char* TAG_WS2812 = "WS2812";

static const rmt_symbol_word_t ws2812_zero = {
    .level0 = 1,
    .duration0 = 0.3 * RMT_LED_STRIP_RESOLUTION_HZ / 1000000, // T0H=0.3us
    .level1 = 0,
    .duration1 = 0.9 * RMT_LED_STRIP_RESOLUTION_HZ / 1000000, // T0L=0.9us
};

static const rmt_symbol_word_t ws2812_one = {
    .level0 = 1,
    .duration0 = 0.9 * RMT_LED_STRIP_RESOLUTION_HZ / 1000000, // T1H=0.9us
    .level1 = 0,
    .duration1 = 0.3 * RMT_LED_STRIP_RESOLUTION_HZ / 1000000, // T1L=0.3us
};

// reset defaults to 50uS
static const rmt_symbol_word_t ws2812_reset = {
    .level0 = 1,
    .duration0 = RMT_LED_STRIP_RESOLUTION_HZ / 1000000 * 50 / 2,
    .level1 = 0,
    .duration1 = RMT_LED_STRIP_RESOLUTION_HZ / 1000000 * 50 / 2,
};

struct __WS2812Config {
    rmt_tx_channel_config_t tx_chan_config;
    rmt_channel_handle_t led_chan;
    rmt_simple_encoder_config_t simple_encoder_cfg;
    rmt_transmit_config_t tx_config;
    rmt_encoder_handle_t simple_encoder;

    uint8_t* led_data;
    int led_count;
};

static size_t encoder_callback(const void* data, size_t data_size,
                               size_t symbols_written, size_t symbols_free,
                               rmt_symbol_word_t* symbols, bool* done,
                               void* arg) {
    // We need a minimum of 8 symbol spaces to encode a byte. We only
    // need one to encode a reset, but it's simpler to simply demand that
    // there are 8 symbol spaces free to write anything.
    if (symbols_free < 8) {
        return 0;
    }

    // We can calculate where in the data we are from the symbol pos.
    // Alternatively, we could use some counter referenced by the arg
    // parameter to keep track of this.
    size_t data_pos = symbols_written / 8;
    const uint8_t* data_bytes = (uint8_t*)data;
    if (data_pos < data_size) {
        // Encode a byte
        size_t symbol_pos = 0;
        for (int bitmask = 0x80; bitmask != 0; bitmask >>= 1) {
            symbols[symbol_pos++] =
                data_bytes[data_pos] & bitmask ? ws2812_one : ws2812_zero;
        }
        // We're done; we should have written 8 symbols.
        return symbol_pos;
    } else {
        // All bytes already are encoded.
        // Encode the reset, and we're done.
        symbols[0] = ws2812_reset;
        *done = 1; // Indicate end of the transaction.
        return 1;  // we only wrote one symbol
    }
}

WS2812Config* create_ws2812_encoder(gpio_num_t gpio_num, int led_count) {
    LOGI(TAG_WS2812, "Create RMT TX channel");
    WS2812Config* led_config = (WS2812Config*)calloc(sizeof(WS2812Config), 1);
    led_config->led_data =
        (uint8_t*)calloc(led_count * WS2812_BYTES_PER_PIXEL, sizeof(uint8_t));
    led_config->led_count = led_count;
    led_config->tx_chan_config = (rmt_tx_channel_config_t){
        .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
        .gpio_num = gpio_num,
        .mem_block_symbols =
            64, // increase the block size can make the LED less flickering
        .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
        .trans_queue_depth = 4, // set the number of transactions that can be
                                // pending in the background
    };
    ESP_ERROR_CHECK(
        rmt_new_tx_channel(&led_config->tx_chan_config, &led_config->led_chan));

    LOGI(TAG_WS2812, "Create simple callback-based encoder");
    LOGI(TAG_WS2812, "Create simple callback-based encoder");
    led_config->simple_encoder_cfg = (rmt_simple_encoder_config_t){
        .callback = encoder_callback
        // Note we don't set min_chunk_size here as the default of 64 is good
        // enough.
    };
    ESP_ERROR_CHECK(rmt_new_simple_encoder(&led_config->simple_encoder_cfg,
                                           &led_config->simple_encoder));

    LOGI(TAG_WS2812, "Enable RMT TX channel");
    LOGI(TAG_WS2812, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(led_config->led_chan));

    led_config->tx_config = (rmt_transmit_config_t){
        .loop_count = 0, // no transfer loop
    };

    return led_config;
}

void setWS2812Pixel(WS2812Config* config, int index, uint8_t red, uint8_t green,
                    uint8_t blue) {
    if (index >= config->led_count) {
        LOGE(TAG_WS2812, "Index out of range: %d", index);
        LOGE(TAG_WS2812, "Index out of range: %d", index);
        return;
    }
    config->led_data[index * WS2812_BYTES_PER_PIXEL] = green;
    config->led_data[index * WS2812_BYTES_PER_PIXEL + 1] = red;
    config->led_data[index * WS2812_BYTES_PER_PIXEL + 2] = blue;
}

void showWS2812(WS2812Config* config) {
    LOGD(TAG_WS2812, "Transmitting %d pixels", config->led_count);
    ESP_ERROR_CHECK(rmt_transmit(
        config->led_chan, config->simple_encoder, config->led_data,
        config->led_count * WS2812_BYTES_PER_PIXEL * sizeof(uint8_t),
        &config->tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(config->led_chan, portMAX_DELAY));
}
