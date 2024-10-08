#include <Serial.h>
#include <stdio.h>

#include "HardwareLED.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stringHelper.h"

#define ECHO_TASK_STACK_SIZE 2048

static void lsd(void* pvParameters) {
    while (1) {
        for (int g = 0; g < 50; g++) {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        for (int g = 50; g > 0; g--) {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        for (int r = 0; r < 50; r++) {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        for (int r = 50; r > 0; r--) {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        for (int b = 0; b < 50; b++) {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        for (int b = 50; b > 0; b--) {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
    }
}

#ifdef __cplusplus
extern "C"
#endif
    void
    app_main() {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    esp_log_level_set("main", ESP_LOG_VERBOSE);
    // esp_task_wdt_init(0, false);
    beginSerial(115200);

    // serialWrite("test\n");
    const char* test = intToString(5, 10);
    serialWrite(test);

    initHardwareLED();

    ESP_LOGV("main", "Log test verbose");
    ESP_LOGD("main", "Log test debug");
    ESP_LOGI("main", "Log test info");
    ESP_LOGW("main", "Log test warn");
    ESP_LOGE("main", "Log test error");
    // writeHWLED(0, 50, 0);
    // showHWLED();

    xTaskCreate(lsd, "lsd_led_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}
