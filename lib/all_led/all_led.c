#include "all_led.h"
#include <FastLED.h>

#define RMT_LED_STRIP_GPIO_NUM (GPIO_NUM_8) // GPIO 8 laut Plan

#define LED_STRIP_LENGTH 3 // Index startet bei 0

static FastLEDConfig *config = NULL;
const char *TAG_ALL_LED = "All-LEDs"; // Meint Status-LED und Wiedergabe-LED
const char *TAG_ST_LED = "Status-LED";
const char *TAG_WI_LED = "Wiedergabe-LED";
const char *TAG_HW_LED = "HardwareLED";

void initExternLEDs()
{
    if (config != NULL)
    {
        LOGD(TAG_ALL_LED, "External LEDs already initialized");
        return;
    }
    config = initFastLED(LED_STRIP_LENGTH, RMT_LED_STRIP_GPIO_NUM);
    LOGD(TAG_ALL_LED, "External LEDs initialized");
}

void writeHWLED(uint8_t red, uint8_t green, uint8_t blue)
{
    if (config == NULL)
    {
        LOGE(TAG_HW_LED, "Hardware LED not initialized");
        return;
    }
    writeLED(config, 0, red, green, blue);
    LOGV(TAG_HW_LED, "Wrote to Hardware LED memory: %d %d %d", red, green, blue);
}

void showHWLED()
{
    if (config == NULL)
    {
        LOGE(TAG_HW_LED, "Hardware LED not initialized");
        return;
    }
    showLED(config);
    LOGV(TAG_HW_LED, "Showed Hardware LED");
}

void writeSTLED(uint8_t red, uint8_t green, uint8_t blue)
{
    if (config == NULL)
    {
        LOGE(TAG_ALL_LED, "External LEDs not initialized");
        return;
    }
    writeLED(config, 1, red, green, blue);
    LOGV(TAG_ST_LED, "Wrote to Status-LED memory: %d %d %d", red, green, blue);
}

void showSTLED()
{
    if (config == NULL)
    {
        LOGE(TAG_ALL_LED, "External LEDs not initialized");
        return;
    }
    showLED(config);
    LOGV(TAG_ST_LED, "Showed Status-LED");
}

void writeWILED(uint8_t red, uint8_t green, uint8_t blue)
{
    if (config == NULL)
    {
        LOGE(TAG_ALL_LED, "External LEDs not initialized");
        return;
    }
    writeLED(config, 2, red, green, blue);
    LOGV(TAG_WI_LED, "Wrote to Wiedergabe-LED memory: %d %d %d", red, green, blue);
}

void showWILED()
{
    if (config == NULL)
    {
        LOGE(TAG_ALL_LED, "External LEDs not initialized");
        return;
    }
    showLED(config);
    LOGV(TAG_WI_LED, "Showed Wiedergabe-LED");
}
