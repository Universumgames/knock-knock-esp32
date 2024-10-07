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
            for (int r = 0; r < 255; r++) {
                for (int b = 0; b < 255; b++) {
                    writeHWLED(r, g, b);
                    showHWLED();
                    serialWrite(intToString(r, 10));
                    serialWrite(" ");
                    serialWrite(intToString(g, 10));
                    serialWrite(" ");
                    serialWrite(intToString(b, 10));
                    serialWrite("\n");
                    serialFlush();
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
            }
        }
        for (int g = 255; g > 0; g--) {
            for (int r = 255; r > 0; r--) {
                for (int b = 255; b > 0; b--) {
                    writeHWLED(r, g, b);
                    showHWLED();
                    serialWrite(intToString(r, 10));
                    serialWrite(" ");
                    serialWrite(intToString(g, 10));
                    serialWrite(" ");
                    serialWrite(intToString(b, 10));
                    serialWrite("\n");
                    serialFlush();
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
            }
        }
    }
}

#ifdef __cplusplus
extern "C"
#endif
    void
    app_main5() {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    esp_log_level_set("main", ESP_LOG_VERBOSE);
    // esp_task_wdt_init(0, false);
    beginSerial(115200);

    // serialWrite("test\n");
    const char* test = intToString(5, 10);
    serialWrite(test);

    initHardwareLED();
    writeHWLED(0, 50, 0);
    showHWLED();

    int len = 0;
    int* indices = splitString("Hello, World!", ", ", &len);
    serialWrite(intToString(indices[0], 10));
    serialWrite("\n");
    serialWrite(intToString(indices[1], 10));
    serialWrite("\n");
    ESP_LOGI("main", "len: %d", len);
    ESP_LOGI("main", "index 0: %d", indices[0]);
    ESP_LOGI("main", "index 1: %d", indices[1]);

    // xTaskCreate(lsd, "lsd_led_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}
