#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "Serial.h"
#include "Storage.h"
#include "basicDefs.h"
#include "lock_open.h"
#include "lock_status.h"

#define ECHO_TASK_STACK_SIZE 2048

CPP_BEGIN void app_main() {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    esp_log_level_set("main", ESP_LOG_VERBOSE);
    beginSerial(115200);

    initialize_lock_state();

    ESP_LOGV("main", "Log test verbose");
    ESP_LOGD("main", "Log test debug");
    ESP_LOGI("main", "Log test info");
    ESP_LOGW("main", "Log test warn");
    ESP_LOGE("main", "Log test error");

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
