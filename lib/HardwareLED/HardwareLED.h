#pragma once
#include <stdint.h>

#include "basicDefs.h"

// Datasheet WS2812 https://www.digikey.com/en/htmldatasheets/production/2755926/0/0/1/ws2812b-led

HEADER_BEGIN

/**
 * @brief initialize the hardware LED
 *
 */
void initHardwareLED();

/**
 * @brief write the color values to the hardware LED
 *
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void writeHWLED(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief send the color values to the hardware LED
 *
 */
void showHWLED();

HEADER_END