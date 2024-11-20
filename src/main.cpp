#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "HardwareLED.h"
#include "PatternRecorder.h"
#include "PatternStorage.h"
#include "Serial.h"
#include "Storage.h"
#include "_AnalogRead_internal.h"
#include "basicDefs.h"
#include "lock_open.h"
#include "lock_status.h"

#define ECHO_TASK_STACK_SIZE 2048

CPP_BEGIN void app_main() {
    esp_log_level_set("*", ESP_LOG_INFO);
    beginSerial(CONFIG_MONITOR_BAUD);

    initialize_lock_state();

    bool ptStor = initPatternStorage();
    if (!ptStor) {
        ESP_LOGE("main", "Failed to initialize pattern storage");
        esp_restart();
    }

    ESP_LOGV("main", "Log test verbose");
    ESP_LOGD("main", "Log test debug");
    ESP_LOGI("main", "Log test info");
    ESP_LOGW("main", "Log test warn");
    ESP_LOGE("main", "Log test error");

    size_t len2 = 0;
    PatternData** pattern = loadPatterns(&len2);

    initPatternRecorder();

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
