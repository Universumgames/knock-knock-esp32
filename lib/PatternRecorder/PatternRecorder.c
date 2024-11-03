#include "PatternRecorder.h"

#include "AnalogRead.h"

#include <freertos/FreeRTOS.h>

#define PATTERN_RECORDER_ANALOG_CHANNEL ((adc_channel_t)ADC_CHANNEL_0)
#define PATTERN_RECORDER_ANALOG_UNIT ((adc_unit_t)ADC_UNIT_1)
#define PATTERN_RECORDER_GAIN ((adc_atten_t)ADC_ATTEN_DB_0)
#define ECHO_TASK_STACK_SIZE 2048

static const char* TAG_PATTERN_RECORDER = "PatternRecorder";

static AnalogReadHandle* analogReadHandle = NULL;

[[noreturn]]
static void analogReadTask(void* pvParameters) {
    uint64_t lastRead = pdTICKS_TO_MS(xTaskGetTickCount());
    int value = 0;
    while (true) {
        bool suc = readAnalogValuePtr(analogReadHandle, &value);
        if (suc) {
            const uint64_t now = pdTICKS_TO_MS(xTaskGetTickCount());
            const uint64_t delta = now - lastRead;
            lastRead = now;
            LOGI(TAG_PATTERN_RECORDER, "Read %d values in %llu ms", value,
                 delta);
        } else {
        }
        vTaskDelay(1);
    }
}

bool initPatternRecorder() {
    if (analogReadHandle != NULL) {
        return true;
    }
    bool ret = true;

    analogReadHandle =
        initAnalogRead(PATTERN_RECORDER_ANALOG_UNIT, PATTERN_RECORDER_GAIN,
                       PATTERN_RECORDER_ANALOG_CHANNEL);
    if (analogReadHandle == NULL) {
        ESP_LOGE(TAG_PATTERN_RECORDER, "Failed to initialize analog read");
        goto error;
    }

    xTaskCreate(analogReadTask, "analog_read_task", ECHO_TASK_STACK_SIZE, NULL,
                5, NULL);
    ESP_LOGI(TAG_PATTERN_RECORDER, "ADC continuous started");
    goto end;

error:
    ret = false;
end:
    return ret;
}