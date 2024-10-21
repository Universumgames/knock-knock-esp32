#pragma once
#include <esp_adc/adc_cali.h>
#include <esp_adc/adc_cali_scheme.h>
#include <esp_adc/adc_continuous.h>
#include <esp_adc/adc_oneshot.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <soc/soc_caps.h>

#include "basicDefs.h"

#ifdef __cplusplus
extern "C" {
#endif

#if false
bool init_oneshot(adc_unit_t unit, adc_atten_t atten, adc_channel_t channel);

void read_oneshot(adc_unit_t unit, adc_channel_t channel, int* value);

void readVoltage_oneshot(adc_unit_t unit, adc_channel_t channel, int* voltage);
#endif

#ifdef __cplusplus
}
#endif