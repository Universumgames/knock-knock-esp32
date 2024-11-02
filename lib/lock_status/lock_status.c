#include "lock_status.h"
#include "all_led.h"
#include "lock_open.h"
#include <freertos/FreeRTOS.h>

#define COLOR_RED 255, 0, 0
#define COLOR_GREEN 0, 255, 0
#define COLOR_BLUE 0, 0, 255
#define COLOR_ORANGE 255, 165, 0
#define COLOR_WHITE 255, 255, 255

// Natürlich muss hier noch writeHWLED gegen writeSTLED und selbiges für show...
// ausgetauscht werden
static SchlossStatus currentStatus = SCHLOSS_VERRIEGELT;

void initialize_lock_state() {
    initExternLEDs(); // siehe all_led.c

    currentStatus = SCHLOSS_VERRIEGELT;
    setHWLED(COLOR_RED);
}

void set_back_to_locked() { // Geht das anders besser?
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    updateLEDStatus(SCHLOSS_VERRIEGELT);
    vTaskDelete(NULL);
}

void updateLEDStatus(SchlossStatus status) {
    if (status != currentStatus) {
        currentStatus = status;
        switch (status) {
        case SCHLOSS_VERRIEGELT:
            setHWLED(COLOR_RED);
            break;
        case SCHLOSS_ENTRIEGELT:
            setHWLED(COLOR_GREEN);
            openLock(); // Ist auch ein Task, siehe lock_open.c
            xTaskCreate(set_back_to_locked, "set_back_to_locked_task", 2048,
                        NULL, 10, NULL);
            break;
        case MUSTER_AUFNAHME:
            setHWLED(COLOR_BLUE);
            break;
        case MUSTER_FAST_KORREKT:
            setHWLED(COLOR_ORANGE);
            break;
        case FEHLERFALL:
            setHWLED(COLOR_WHITE);
            break;
        }
    }
}

SchlossStatus get_current_status() { return currentStatus; }