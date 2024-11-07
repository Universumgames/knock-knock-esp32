#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "Serial.h"
#include "Storage.h"
#include "basicDefs.h"
#include "lock_open.h"
#include "lock_status.h"

#define ECHO_TASK_STACK_SIZE 2048

static int values[4096] = {0};

[[noreturn]] static void oneshotAnalogRead(void* pvParameters) {
    static size_t len = 0;
    int value = 0;
    adc_oneshot_unit_handle_t handle = nullptr;
    adc_cali_handle_t cali_handle = nullptr;
    init_oneshot(ADC_UNIT_1, ADC_ATTEN_DB_0, ADC_CHANNEL_0, &handle,
                 &cali_handle);

    while (true) {
        read_oneshot(handle, ADC_CHANNEL_0, &value);
        // serialWrite("Analog value: ");
        // serialWrite(intToString(value, 10));
        // serialWrite("\n");
        values[len++] = value;
        if (len >= 4096) {
            FILE* file = fopen(STORAGE_MOUNT_POINT "/data.bin", "wbe");
            LOGI("main", "Int size: %d", sizeof(int));
            fwrite(values, sizeof(int), 4096, file);
            fclose(file);
            LOGI("main", "Wrote data to file");
            vTaskDelete(nullptr);
        }
        // ESP_LOGI("main", "Analog value: %d", value);
        vTaskDelay(1);
        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

CPP_BEGIN void app_main() {
    esp_log_level_set("*", ESP_LOG_INFO);
    beginSerial(CONFIG_MONITOR_BAUD);

    initialize_lock_state();

    ESP_LOGV("main", "Log test verbose");
    ESP_LOGD("main", "Log test debug");
    ESP_LOGI("main", "Log test info");
    ESP_LOGW("main", "Log test warn");
    ESP_LOGE("main", "Log test error");

    mountFS();
    size_t len = 0;
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
