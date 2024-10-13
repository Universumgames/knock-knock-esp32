#pragma once

#include "driver/gpio.h"

#define HIGH (1)
#define LOW (0)

#ifdef __cplusplus
extern "C" {
#endif

void setupDigitalGPIO(gpio_num_t pin, gpio_mode_t mode);
void writeDigitalGPIO(gpio_num_t pin, int value);
int readDigitalGPIO(gpio_num_t pin);

#ifdef __cplusplus
}
#endif