#include "HardwareLED.h"

#include <FastLed.h>

#define RMT_LED_STRIP_GPIO_NUM (GPIO_NUM_8)

#define LED_STRIP_LENGTH (1)

static FastLEDConfig* config = NULL;
const static char* TAG_HW_LED = "HardwareLED";

void initHardwareLED() {
    if (config != NULL) {
        LOGD(TAG_HW_LED, "Hardware LED already initialized");
        return;
    }
    config = initFastLED(LED_STRIP_LENGTH, RMT_LED_STRIP_GPIO_NUM);
    LOGD(TAG_HW_LED, "Hardware LED initialized");
}

void writeHWLED(uint8_t red, uint8_t green, uint8_t blue) {
    if (config == NULL) {
        LOGE(TAG_HW_LED, "Hardware LED not initialized");
        return;
    }
    writeLED(config, 0, red, green, blue);
    LOGV(TAG_HW_LED, "Wrote to Hardware LED memory: %d %d %d", red, green,
         blue);
}

void showHWLED() {
    if (config == NULL) {
        LOGE(TAG_HW_LED, "Hardware LED not initialized");
        return;
    }
    showLED(config);
    LOGV(TAG_HW_LED, "Showed Hardware LED");
}