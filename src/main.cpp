#include <Serial.h>
#include <stdio.h>

#include "HardwareLED.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stringHelper.hpp"

#define ECHO_TASK_STACK_SIZE 2048

extern "C" void app_main() {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    // esp_task_wdt_init(0, false);
    beginSerial(115200);

    serialWrite("test\n");
    const char* test = intToString(5, 10);
    serialWrite(test);
    // const char* test2 = intToString(square(5), 10);
    // serialWrite(test2);
    initHardwareLED();
    // while (1) {
    writeLED(50, 50, 50);
    show();
    //}

    // readLoop();
    //  xTaskCreate(readLoop, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}
