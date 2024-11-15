#include "lock_open.h"
#include "lock_status.h"

#include <driver/gpio.h>       //Bibliothek für GPIO des ESP32
#include <freertos/FreeRTOS.h> //Betriebssytem Bibliothek des ESP32
// Die OPENTIME wird in basicDefs.h definiert

#define OPENTIME_LOCK_MS 10000 // 10 Sekunden

void lockTask(void* pvParameters) {
    gpio_reset_pin(PIN_LOCK_RELAY);
    gpio_set_direction(PIN_LOCK_RELAY, GPIO_MODE_OUTPUT);

    gpio_set_level(PIN_LOCK_RELAY, 1); // Relais auf HIGH schalten
    updateLEDStatus(SCHLOSS_ENTRIEGELT);

    vTaskDelay(OPENTIME_LOCK_MS / portTICK_PERIOD_MS); // 10 Sekunde warten
    gpio_set_level(PIN_LOCK_RELAY, 0); // Relais auf LOW schalten
    updateLEDStatus(SCHLOSS_VERRIEGELT);

    vTaskDelete(NULL); // Task löschen, nachdem die Ausführung abgeschlossen ist
}

void openLock() {
    xTaskCreate(lockTask, "open_lock_task", 2048, NULL, THREAD_PRIO_LOCK,
                NULL); // Task erstellen und ausführen
}
