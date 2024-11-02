#include "lock_open.h"
#include "basicDefs.h"

#include <driver/gpio.h>       //Bibliothek für GPIO des ESP32
#include <freertos/FreeRTOS.h> //Betriebssytem Bibliothek des ESP32
// Die OPENTIME wird in basicDefs.h definiert

#define RELAY_GPIO GPIO_NUM_3

void lockTask(void* pvParameters) {
    gpio_reset_pin(RELAY_GPIO);
    gpio_set_direction(RELAY_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_level(RELAY_GPIO, 1);             // Relais auf HIGH schalten
    vTaskDelay(OPENTIME / portTICK_PERIOD_MS); // 10 Sekunde warten
    gpio_set_level(RELAY_GPIO, 0);             // Relais auf LOW schalten

    vTaskDelete(NULL); // Task löschen, nachdem die Ausführung abgeschlossen ist
}

void openLock() {
    xTaskCreate(lockTask, "open_lock_task", 2048, NULL, 10,
                NULL); // Task erstellen und ausführen
}
