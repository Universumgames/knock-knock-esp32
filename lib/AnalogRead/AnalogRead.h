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

/**
 * @brief Initialize the continuous ADC
 *
 * @param channel the array of channels to read from
 * @param channel_num the number of channels
 * @param atten the attenuation to use
 * @param out_handle the handle to the continuous ADC
 * @return true on success
 * @return false on failure
 */
bool continuous_init(adc_channel_t* channel, uint8_t channel_num, adc_atten_t atten, adc_continuous_handle_t* out_handle);

/**
 * @brief Read analog values from the ADC buffer
 *
 * @param handle the handle to the continuous ADC
 * @param valueBuf the buffer to store the values
 * @param bufSize the size of the buffer
 * @return size_t the number of values read
 */
size_t read_continuous(adc_continuous_handle_t handle, uint8_t* valueBuf, size_t bufSize);

#if false
bool init_oneshot(adc_unit_t unit, adc_atten_t atten, adc_channel_t channel);

void read_oneshot(adc_unit_t unit, adc_channel_t channel, int* value);

void readVoltage_oneshot(adc_unit_t unit, adc_channel_t channel, int* voltage);
#endif

#ifdef __cplusplus
}
#endif