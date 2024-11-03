#pragma once
#include <driver/gpio.h>

#include "basicDefs.h"

HEADER_BEGIN

struct __WS2812Config;

typedef struct __WS2812Config WS2812Config;

WS2812Config* create_ws2812_encoder(gpio_num_t gpio_num, int led_count);

void setWS2812Pixel(WS2812Config* config, int index, uint8_t red, uint8_t green,
                    uint8_t blue);

void showWS2812(WS2812Config* config);

HEADER_END