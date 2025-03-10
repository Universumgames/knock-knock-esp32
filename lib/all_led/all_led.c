#include "all_led.h"
#include <FastLed.h>

#define RMT_LED_STRIP_GPIO_NUM (PIN_STATUS_LED)

#define BRIGHTNESS_ADJUST(r, g, b, brightness)                                 \
    (r * brightness / 255), (g * brightness / 255), (b * brightness / 255)

#define LED_STRIP_LENGTH 3 // Index startet bei 0

static FastLEDConfig* config = NULL;
const char* TAG_LED = "All-LEDs";

void initExternLEDs() {
    if (config != NULL) {
        LOGD(TAG_LED, "External LEDs already initialized");
        return;
    }
    config = initFastLED(LED_STRIP_LENGTH, RMT_LED_STRIP_GPIO_NUM);
    LOGD(TAG_LED, "External LEDs initialized");
}

/**
 * @brief set the color values of the hardware LED
 *
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void setHWLED(uint8_t red, uint8_t green, uint8_t blue) {
    if (config == NULL) {
        LOGE(TAG_LED, "Hardware LED not initialized");
        return;
    }
    writeLED(config, 0, red, green, blue);
    LOGV(TAG_LED, "Wrote to Hardware LED memory: %d %d %d", red, green, blue);
    showLED(config);
    LOGV(TAG_LED, "Showed Hardware LED");
}

void setWILED(uint8_t red, uint8_t green, uint8_t blue) {
    if (config == NULL) {
        LOGE(TAG_LED, "External LEDs not initialized");
        return;
    }
    writeLED(config, 1, red, green, blue);
    LOGV(TAG_LED, "Wrote to Wiedergabe-LED memory: %d %d %d", red, green, blue);
    showLED(config);
    LOGV(TAG_LED, "Showed Wiedergabe-LED");
}

void setSTLED(uint8_t red, uint8_t green, uint8_t blue) {
    if (config == NULL) {
        LOGE(TAG_LED, "External LEDs not initialized");
        return;
    }
    writeLED(config, 2, red, green, blue);
    writeLED(config, 0, BRIGHTNESS_ADJUST(red, green, blue, 50));
    LOGV(TAG_LED, "Wrote to Status-LED memory: %d %d %d", red, green, blue);
    showLED(config);
    LOGV(TAG_LED, "Showed Status-LED");
}
