#pragma once
#include <stdint.h>

// Datasheet WS2812 https://www.digikey.com/en/htmldatasheets/production/2755926/0/0/1/ws2812b-led

#ifdef __cplusplus
extern "C" {
#endif

void initHardwareLED();

void writeHWLED(uint8_t red, uint8_t green, uint8_t blue);

void showHWLED();

#ifdef __cplusplus
}
#endif