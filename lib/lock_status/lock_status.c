#include "lock_status.h"
#include "all_led.h"

#define COLOR_RED 255, 0, 0
#define COLOR_GREEN 0, 255, 0
#define COLOR_BLUE 0, 0, 255
#define COLOR_ORANGE 255, 165, 0
#define COLOR_WHITE 255, 255, 255

// Natürlich muss hier noch writeHWLED gegen writeSTLED und selbiges für show...
// ausgetauscht werden
static SchlossStatus currentStatus = -1; // Initialisierung auf ungültigen Wert

void initialize_lock_state() {
    if (currentStatus != -1)
        return;

    initExternLEDs(); // siehe all_led.c

    updateLEDStatus(SCHLOSS_VERRIEGELT);
}

void updateLEDStatus(SchlossStatus status) {
    if (status != currentStatus) {
        currentStatus = status;
        switch (status) {
        case SCHLOSS_VERRIEGELT:
            setSTLED(COLOR_RED);
            break;
        case SCHLOSS_ENTRIEGELT:
            setSTLED(COLOR_GREEN);
            break;
        case MUSTER_AUFNAHME:
            setSTLED(COLOR_BLUE);
            break;
        case MUSTER_FAST_KORREKT:
            setSTLED(COLOR_ORANGE);
            break;
        case FEHLERFALL:
            setSTLED(COLOR_WHITE);
            break;
        }
    }
}

SchlossStatus get_current_status() { return currentStatus; }