#include "PatternRecorder.h"

#include "../lock_open/lock_open.h"
#include "../lock_status/lock_status.h"
#include "AnalogRead.h"
#include "PatternMatcher.h"

#include <PatternEncoder.h>
#include <PatternStorage.h>
#include <PatternTypes.h>
#include <freertos/FreeRTOS.h>

#define PATTERN_RECORDER_ANALOG_CHANNEL ((adc_channel_t)ADC_CHANNEL_0)
#define PATTERN_RECORDER_ANALOG_UNIT ((adc_unit_t)ADC_UNIT_1)
#define PATTERN_RECORDER_GAIN ((adc_atten_t)ADC_ATTEN_DB_0)

static const char* TAG_PATTERN_RECORDER = "PatternRecorder";

static AnalogReadHandle* analogReadHandle = NULL;

[[noreturn]] static void analogReadTask(void* pvParameters) {
    uint64_t lastRead = pdTICKS_TO_MS(xTaskGetTickCount());
    int value = 0;
    SchlossStatus lastStatus = get_current_status();
    while (true) {
        if (dflag_pattern_recorder_pause) {
            vTaskDelay(1000);
            continue;
        }
        bool suc = readAnalogValuePtr(analogReadHandle, &value);
        if (suc) {
            SchlossStatus currentStatus = get_current_status();
            const uint64_t now = pdTICKS_TO_MS(xTaskGetTickCount());
            const uint64_t delta = now - lastRead;
            lastRead = now;
            // LOGI(TAG_PATTERN_RECORDER, "Read %d in %llu ms", value, delta);
            if (currentStatus != lastStatus) {
                LOGI(TAG_PATTERN_RECORDER,
                     "Status changed to %u, resetting encoder", currentStatus);
                resetPatternEncoder();
                lastStatus = currentStatus;
            }
            PatternData* patternData = encodeAnalogData((analog_v)value, delta);
            if (patternData != NULL) {
                LOGI(TAG_PATTERN_RECORDER, "Encoded pattern data");

                switch (currentStatus) {
                    case SCHLOSS_VERRIEGELT:
                        bool matched = matchPattern(patternData, NULL);
                        if (matched) {
                            openLock();
                        }
                        break;
                    case MUSTER_AUFNAHME:
                        storePattern(patternData);
                        updateLEDStatus(SCHLOSS_VERRIEGELT);
                        break;
                    default:
                        LOGW(TAG_PATTERN_RECORDER, "Unknown status");
                        break;
                }

                free(patternData->deltaTimesMillis);
                free(patternData);
            } else {
                LOGD(TAG_PATTERN_RECORDER, "Pattern recording not finished");
            }
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

    initPatternEncoder();
    xTaskCreate(analogReadTask, "analog_read_task", THREAD_STACK_RECORDING,
                NULL, THREAD_PRIO_RECORDING, NULL);
    ESP_LOGI(TAG_PATTERN_RECORDER, "ADC continuous started");
    goto end;

error:
    ret = false;
end:
    return ret;
}