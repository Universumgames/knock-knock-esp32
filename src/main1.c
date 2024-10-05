#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void app_main1()
{
    while (true)
    {
        ESP_LOGI("TEST", "ESP32-C3 running!");
        vTaskDelay(pdMS_TO_TICKS(1000)); // 1-second delay
    }
}