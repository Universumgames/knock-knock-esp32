#pragma once
#include "driver/rmt_tx.h"
#include "led_strip_encoder.h"

#ifdef __cplusplus
extern "C" {
#endif

struct __FastLED_Config_internal;

typedef struct __FastLED_Config_internal FastLEDConfig;

FastLEDConfig* initFastLED(int length, rmt_tx_channel_config_t* tx_chan_config, led_strip_encoder_config_t* encoder_config);

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue);

void showLED(FastLEDConfig* config);

#ifdef __cplusplus
}
#endif