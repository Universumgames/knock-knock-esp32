#pragma once
#include "freertos/FreeRTOS.h"

void initHardwareLED();

void writeLED(uint8_t red, uint8_t green, uint8_t blue);

void show();