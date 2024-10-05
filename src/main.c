#include <Serial.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define ECHO_TASK_STACK_SIZE 2048

void app_main()
{
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    // esp_task_wdt_init(0, false);
    beginSerial(115200);
    // readLoop();
    //  xTaskCreate(readLoop, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
}
