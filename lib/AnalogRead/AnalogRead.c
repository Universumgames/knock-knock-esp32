#include "AnalogRead.h"
#include "_AnalogRead_internal.h"

#if ANALOG_READ_ONESHOT

struct AnalogReadHandle_internal {
    adc_oneshot_unit_handle_t handle;
    adc_cali_handle_t cali_handle;
    adc_atten_t attenuation;
    adc_channel_t channel;
    adc_unit_t adc_unit;
};

AnalogReadHandle* initAnalogRead(adc_unit_t adc_unit, adc_atten_t attenuation,
                                 adc_channel_t channel) {
    AnalogReadHandle* handle =
        (AnalogReadHandle*)calloc(sizeof(AnalogReadHandle), 1);
    if (!handle) {
        return NULL;
    }
    handle->adc_unit = adc_unit;
    handle->attenuation = attenuation;
    handle->channel = channel;
    init_oneshot(adc_unit, attenuation, channel, &handle->handle,
                 &handle->cali_handle);
    return handle;
}

bool readAnalogValuePtr(AnalogReadHandle* handle, int* rawValue) {
    if (rawValue == NULL) {
        return false;
    }
    if (!handle) {
        *rawValue = -1;
        return false;
    }
    read_oneshot(handle->handle, handle->channel, rawValue);
    return true;
}

int readAnalogValue(AnalogReadHandle* handle) {
    int value;
    readAnalogValuePtr(handle, &value);
    return value;
}

#else if ANALOG_READ_CONTINUOUS

// TODO: Implement continuous mode

#endif