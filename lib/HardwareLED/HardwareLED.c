#include "HardwareLED.h"

#include "FastLed.h"
#include "esp_log.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000  // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define RMT_LED_STRIP_GPIO_NUM ((gpio_num_t)8)

#define LED_STRIP_LENGTH 1

static FastLEDConfig* config = NULL;
const char* TAG_HW_LED = "HardwareLED";

static rmt_tx_channel_config_t tx_chan_config = {
    .gpio_num = RMT_LED_STRIP_GPIO_NUM,
    .clk_src = RMT_CLK_SRC_DEFAULT,  // select source clock
    .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
    .mem_block_symbols = 64,  // increase the block size can make the LED less flickering
    .trans_queue_depth = 4,   // set the number of transactions that can be pending in the background
};

static led_strip_encoder_config_t encoder_config = {
    .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
};

void initHardwareLED() {
    if (config != NULL) {
        ESP_LOGD(TAG_HW_LED, "Hardware LED already initialized");
        return;
    }
    config = initFastLED(LED_STRIP_LENGTH, &tx_chan_config, &encoder_config);
}

void writeHWLED(uint8_t red, uint8_t green, uint8_t blue) {
    writeLED(config, 0, red, green, blue);
}

void showHWLED() {
    showLED(config);
}