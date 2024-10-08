#include "HardwareLED.h"

#include "FastLed.h"
#include "esp_log.h"

#define RMT_LED_STRIP_GPIO_NUM ((gpio_num_t)8)

#define LED_STRIP_LENGTH 1

static FastLEDConfig* config = NULL;
const char* TAG_HW_LED = "HardwareLED";

void initHardwareLED() {
    esp_log_level_set(TAG_HW_LED, ESP_LOG_DEBUG);
    if (config != NULL) {
        ESP_LOGD(TAG_HW_LED, "Hardware LED already initialized");
        return;
    }
    config = initFastLED(LED_STRIP_LENGTH, RMT_LED_STRIP_GPIO_NUM);
    ESP_LOGD(TAG_HW_LED, "Hardware LED initialized");
}

void writeHWLED(uint8_t red, uint8_t green, uint8_t blue) {
    writeLED(config, 0, red, green, blue);
    ESP_LOGV(TAG_HW_LED, "Wrote to Hardware LED memory: %d %d %d", red, green, blue);
}

void showHWLED() {
    showLED(config);
    ESP_LOGV(TAG_HW_LED, "Showed Hardware LED");
}