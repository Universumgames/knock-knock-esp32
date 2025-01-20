#include "all_led.h"
#include "pattern_play.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define KNOCK_DURATION_MS 80        // Klopfzeit ist ca. 50ms
#define PLAY_LED_COLOUR 255, 0, 255 // Magenta
#define PLAY_LED_OFF 0, 0, 0

bool playPattern(PatternData* pattern) {
    if (pattern == NULL || pattern->lengthPattern == 0 ||
        pattern->deltaTimesMillis == NULL) {
        return false;
    }

    // play the pattern
    for (size_t i = 0; i < pattern->lengthPattern; i++) {
        if (pattern->deltaTimesMillis[i] < KNOCK_DURATION_MS) {
            LOGD("PatternPlay", "Pattern too short");
            return false;
        }

        setWILED(PLAY_LED_COLOUR);

        vTaskDelay(pdMS_TO_TICKS(KNOCK_DURATION_MS));

        setWILED(PLAY_LED_OFF);

        vTaskDelay(pdMS_TO_TICKS(
            pattern->deltaTimesMillis[i] -
            KNOCK_DURATION_MS)); // Abziehen der bereits Ausgegebenen Zeit
    }
    setWILED(PLAY_LED_COLOUR);
    vTaskDelay(pdMS_TO_TICKS(KNOCK_DURATION_MS));
    setWILED(PLAY_LED_OFF);

    return true;
}
