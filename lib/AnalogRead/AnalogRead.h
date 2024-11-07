#pragma once
#include "basicDefs.h"
#include <hal/adc_types.h>

#define ANALOG_READ_ONESHOT
// #define ANALOG_READ_CONTINUOUS

HEADER_BEGIN

struct AnalogReadHandle_internal;

typedef struct AnalogReadHandle_internal AnalogReadHandle;

AnalogReadHandle* initAnalogRead(adc_unit_t adc_unit, adc_atten_t attenuation,
                                 adc_channel_t channel);

int readAnalogValue(AnalogReadHandle* handle);

bool readAnalogValuePtr(AnalogReadHandle* handle, int* rawValue);

HEADER_END