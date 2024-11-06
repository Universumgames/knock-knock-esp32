#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "HardwareLED.h"
#include "PatternRecorder.h"
#include "Serial.h"
#include "Storage.h"
#include "_AnalogRead_internal.h"
#include "basicDefs.h"
#include "lock_open.h"
#include "lock_status.h"

#define ECHO_TASK_STACK_SIZE 2048

int values[4096] = {0};
size_t len = 0;

static void oneshotAnalogRead(void* pvParameters) {
    int value;
    adc_oneshot_unit_handle_t handle;
    adc_cali_handle_t cali_handle;
    init_oneshot(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_CHANNEL_0, &handle,
                 &cali_handle);

    while (1) {
        read_oneshot(handle, ADC_CHANNEL_0, &value);
        // serialWrite("Analog value: ");
        // serialWrite(intToString(value, 10));
        // serialWrite("\n");
        values[len++] = value;
        if (len >= 4096) {
            FILE* file = fopen(STORAGE_MOUNT_POINT "/data.bin", "wb");
            LOGI("main", "Int size: %d", sizeof(int));
            fwrite(values, sizeof(int), 4096, file);
            fclose(file);
            LOGI("main", "Wrote data to file");
            vTaskDelete(NULL);
        }
        // ESP_LOGI("main", "Analog value: %d", value);
        vTaskDelay(1);
        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

CPP_BEGIN void app_main() {
    esp_log_level_set("*", ESP_LOG_INFO);
    beginSerial(115200);

    initialize_lock_state();

    ESP_LOGV("main", "Log test verbose");
    ESP_LOGD("main", "Log test debug");
    ESP_LOGI("main", "Log test info");
    ESP_LOGW("main", "Log test warn");
    ESP_LOGE("main", "Log test error");

    xTaskCreate(oneshotAnalogRead, "oneshot_analog_read_task",
                ECHO_TASK_STACK_SIZE * 2, NULL, 5, NULL);
    // initPatternRecorder();

    mountFS();
    size_t len;
    char** list = lsDir(STORAGE_MOUNT_POINT, &len);
    for (int i = 0; i < len; i++) {
        char* path = list[i];
        ESP_LOGI("main", "File: %s", path);
        free(path);
    };
    free(list);

    // Test-Code
    openLock();
    vTaskDelay(11000 / portTICK_PERIOD_MS);
    updateLEDStatus(MUSTER_AUFNAHME);
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    updateLEDStatus(MUSTER_FAST_KORREKT);
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    updateLEDStatus(FEHLERFALL);
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    openLock();
}
