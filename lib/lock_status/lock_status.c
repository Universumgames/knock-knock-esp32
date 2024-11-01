#include "lock_status.h"
#include "all_led.h"
// Natürlich muss hier noch writeHWLED gegen writeSTLED und selbiges für show... ausgetauscht werden
static SchlossStatus currentStatus = SCHLOSS_VERRIEGELT;

void initialize_lock_state()
{
    currentStatus = SCHLOSS_VERRIEGELT;
    writeHWLED(255, 0, 0); // Rot
    showHWLED();
}

void updateLEDStatus(SchlossStatus status)
{
    if (status != currentStatus) // Hat sich der Status geändert?
    {
        currentStatus = status;
        switch (status)
        {
        case SCHLOSS_VERRIEGELT:
            writeHWLED(255, 0, 0); // Rot
            showHWLED();
            break;
        case SCHLOSS_ENTRIEGELT:
            writeHWLED(0, 255, 0); // Grün
            showHWLED();
            break;
        case MUSTER_AUFNAHME:
            writeHWLED(0, 0, 255); // Blau
            showHWLED();
            break;
        case MUSTER_FAST_KORREKT:
            writeHWLED(255, 165, 0); // Orange
            showHWLED();
            break;
        case FEHLERFALL:
            writeHWLED(255, 255, 255); // Weiß
            showHWLED();
            break;
        }
    }
}