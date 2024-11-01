#pragma once
#include <stdint.h>
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief initialize the extern LEDs
 *
 */
void initExternLEDs();

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

/**
 * @brief write the color values to the Status-LED
 *
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void writeSTLED(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief send the color values to the Status-LED
 *
 */
void showSTLED();

/**
 * @brief write the color values to the Wiedergabe-LED
 *
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 */
void writeWILED(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief write the color values to the Wiedergabe-LED
 *
 */
void showWILED();

HEADER_END