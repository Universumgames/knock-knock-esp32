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
        for (int g = 0; g < 255; g++) {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        for (int r = 0; r < 255; r++) {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        for (int b = 0; b < 255; b++) {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(1 / portTICK_PERIOD_MS);
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
    // writeHWLED(0, 50, 0);
    // showHWLED();

    xTaskCreate(lsd, "lsd_led_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}
