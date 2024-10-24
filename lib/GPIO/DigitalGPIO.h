#pragma once

#include <driver/gpio.h>

#include "basicDefs.h"

#define HIGH (1)
#define LOW (0)

#define INPUT (GPIO_MODE_INPUT)
#define OUTPUT (GPIO_MODE_OUTPUT)

HEADER_BEGIN

/**
 * @brief Setup a digital GPIO pin
 *
 * @param pin the GPIO pin number
 * @param mode the mode to set the pin to (INPUT or OUTPUT)
 */
void setupDigitalGPIO(gpio_num_t pin, gpio_mode_t mode);

/**
 * @brief Write a value to a digital GPIO pin
 *
 * @param pin the GPIO pin number
 * @param value the value to write (HIGH or LOW)
 */
void writeDigitalGPIO(gpio_num_t pin, int value);

/**
 * @brief Read the value of a digital GPIO pin
 *
 * @param pin the GPIO pin number
 * @return int the value of the pin (HIGH or LOW)
 */
int readDigitalGPIO(gpio_num_t pin);

HEADER_END