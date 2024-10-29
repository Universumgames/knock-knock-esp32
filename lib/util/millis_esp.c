#include <freertos/FreeRTOS.h>

#include "time.h"

uint64_t millisSinceStartup() {
    return pdTICKS_TO_MS(xTaskGetTickCount());
}

uint32_t ticksSinceStartup() {
    return xTaskGetTickCount();
}