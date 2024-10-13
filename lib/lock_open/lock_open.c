#include "lock_open.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

// #include "DigitalGPIO.h" // Datei von Tom PINMODE, DIGITALWRITE, DIGITALREAD

#define RELAY_GPIO GPIO_NUM_19
#define opentime 10000 // 10 Sekunden

void openLock(void *pvParameters)
{
    gpio_reset_pin(RELAY_GPIO);
    gpio_set_direction(RELAY_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(RELAY_GPIO, 1);             // Relais auf HIGH schalten
    vTaskDelay(opentime / portTICK_PERIOD_MS); // 10 Sekunde warten
    gpio_set_level(RELAY_GPIO, 0);             // Relais auf LOW schalten

    vTaskDelete(NULL); // Task löschen, nachdem die Ausführung abgeschlossen ist
}

// Aufruf mit: xTaskCreate(openLock, "open_lock_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);