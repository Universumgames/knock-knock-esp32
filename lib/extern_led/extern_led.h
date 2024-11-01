#pragma once
#include <stdint.h>
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief Initialisiere die externen LEDs
 *
 */
void initExternLED();

/**
 * @brief Schreibe die Farbwerte auf die Status-LED
 *
 * @param red der Rotwert
 * @param green der Grünwert
 * @param blue der Blauwert
 */
void writeSTLED(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Anzeigen der Farbwerte auf der Status-LED
 *
 */
void showSTLED();

/**
 * @brief Schreibe die Farbwerte auf die Wiedergabe-LED
 *
 * @param red der Rotwert
 * @param green der Grünwert
 * @param blue der Blauwert
 */
void writeWILED(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Anzeigen der Farbwerte auf der Wiedergabe-LED
 *
 */
void showWILED();

HEADER_END