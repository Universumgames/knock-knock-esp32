#pragma once
#include "basicDefs.h"
#include <stdint.h>

HEADER_BEGIN

/**
 * @brief initialize the extern LEDs
 *
 */
void initExternLEDs();

/**
 * @brief set the color values of the Wiedergabe-LED
 *
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void setWILED(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief set the color values of the Status-LED
 *
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void setSTLED(uint8_t red, uint8_t green, uint8_t blue);

HEADER_END