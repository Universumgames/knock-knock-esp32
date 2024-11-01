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

// ----------------------------------------------------------------------------------------
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define LED_BRIGHTNESS 10 // 0-255
#define LED_FADE_DELAY 10

void fadeHardwareLED(void *pvParameters)
{
    while (1)
    {
        for (int g = 0; g < LED_BRIGHTNESS; g++)
        {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int g = LED_BRIGHTNESS; g > 0; g--)
        {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int r = 0; r < LED_BRIGHTNESS; r++)
        {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int r = LED_BRIGHTNESS; r > 0; r--)
        {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int b = 0; b < LED_BRIGHTNESS; b++)
        {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int b = LED_BRIGHTNESS; b > 0; b--)
        {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
    }
}

void fadeStatusLED(void *pvParameters)
{
    while (1)
    {
        for (int g = 0; g < LED_BRIGHTNESS; g++)
        {
            writeSTLED(0, g, 0);
            showSTLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int g = LED_BRIGHTNESS; g > 0; g--)
        {
            writeSTLED(0, g, 0);
            showSTLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int r = 0; r < LED_BRIGHTNESS; r++)
        {
            writeSTLED(r, 0, 0);
            showSTLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int r = LED_BRIGHTNESS; r > 0; r--)
        {
            writeSTLED(r, 0, 0);
            showSTLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int b = 0; b < LED_BRIGHTNESS; b++)
        {
            writeSTLED(0, 0, b);
            showSTLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int b = LED_BRIGHTNESS; b > 0; b--)
        {
            writeSTLED(0, 0, b);
            showSTLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
    }
}
