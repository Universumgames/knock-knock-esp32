#pragma once
#include <driver/rmt_tx.h>

#include "basicDefs.h"

HEADER_BEGIN

struct __FastLED_Config_internal;

typedef struct __FastLED_Config_internal FastLEDConfig;

/*typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} LED_Pixel;*/

/**
 * @brief Initialize the FastLEDConfig object with the given length and pin number for a WS2812B LED strip
 *
 * @param length the number of LEDs in the strip
 * @param pin_number the GPIO pin number
 * @return FastLEDConfig* the FastLEDConfig object
 */
FastLEDConfig* initFastLED(int length, gpio_num_t pin_number);

/**
 * @brief Write the pixel data to the FastLEDConfig object
 *
 * @param config the FastLEDConfig object
 * @param index the index of the pixel
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Send the pixel data to the LED strip
 *
 * @param config the FastLEDConfig object
 */
void showLED(FastLEDConfig* config);

HEADER_END