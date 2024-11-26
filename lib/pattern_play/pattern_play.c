#include "pattern_play.h"
#include "all_led.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


#define KNOCK_DURATION_MS 50 // Klopfzeit ist ca. 50ms
#define PLAY_LED_COLOUR 255, 0, 255 // Magenta (PINK)
#define PLAY_LED_OFF 0, 0, 0

bool playPattern(PatternData* pattern) {
    if (pattern == NULL || pattern->lengthPattern == 0 || pattern->deltaTimesMillis == NULL) {
        return false;
    }
    
    // play the pattern
    for (size_t i = 0; i < pattern->lengthPattern; i++) {
        if (pattern->deltaTimesMillis[i] < KNOCK_DURATION_MS) { //Fehlerbehandlung deltaTimesMillis[i] < KNOCK_DURATION_MS 
            LOGD("PatternPlay", "Pattern too short");
            return false;
        }

        setWILED(PLAY_LED_COLOUR); //Fehlerbehandlung bereits in all.led gemacht

        vTaskDelay(pdMS_TO_TICKS(KNOCK_DURATION_MS)); //Funktion, die Division durch portTICK_PERIOD_MS ausführt

        setWILED(PLAY_LED_OFF); //Fehlerbehandlung bereits in all.led gemacht

        vTaskDelay(pdMS_TO_TICKS(pattern->deltaTimesMillis[i] - KNOCK_DURATION_MS)); // Abziehen der bereits Ausgegebenen Zeit

    }

    return true;
}

