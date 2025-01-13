#include "PatternManagement.h"

#include <PatternStorage.h>
#include <linkedList.h>
#include <lock_status.h>
#include <pattern_play.h>

static size_t selectedPatternIndex = 0;

static const char* TAG_PATTERN_MANAGEMENT = "PatternManagement";

void selectPatternChange(LinkedList patterns) {
    PatternData* toPlay =
        (PatternData*)list_get(patterns, selectedPatternIndex);
    LOGI(TAG_PATTERN_MANAGEMENT, "Playing pattern with id %lu (index %u)",
         toPlay->id, selectedPatternIndex);
    playPattern(toPlay);
}

void _handleButtonPress(uint8_t pin) {
    LinkedList patterns = getPatterns();
    size_t patternLength = list_size(patterns);

    LOGI(TAG_PATTERN_MANAGEMENT, "Button press on pin %u", pin);

    /*if (pin == PIN_BUTTON_PLAY) {
        // play button was pressed
        PatternData* toPlay =
            (PatternData*)list_get(patterns, selectedPatternIndex);
        LOGI(TAG_PATTERN_MANAGEMENT, "Playing pattern with id %lu (index %u)",
             toPlay->id, selectedPatternIndex);
        playPattern(toPlay);
    } else */
    if (pin == PIN_BUTTON_UP) {
        // up button was pressed
        selectedPatternIndex =
            (selectedPatternIndex + patternLength - 1) % patternLength;
        LOGI(TAG_PATTERN_MANAGEMENT, "Selected pattern index: %u",
             selectedPatternIndex);
        selectPatternChange(patterns);
    } else if (pin == PIN_BUTTON_DOWN) {
        // down button was pressed
        selectedPatternIndex = (selectedPatternIndex + 1) % patternLength;
        LOGI(TAG_PATTERN_MANAGEMENT, "Selected pattern index: %u",
             selectedPatternIndex);
        selectPatternChange(patterns);
    } else if (pin == PIN_BUTTON_RECORD) {
        // record button was pressed
        LOGI(TAG_PATTERN_MANAGEMENT, "Recording new pattern");
        updateLEDStatus(MUSTER_AUFNAHME);
    } else if (pin == PIN_BUTTON_DELETE) {
        // delete button was pressed
        PatternData* toDelete =
            (PatternData*)list_get(patterns, selectedPatternIndex);
        LOGI(TAG_PATTERN_MANAGEMENT, "Deleting pattern with id %lu",
             toDelete->id);
        deletePattern(toDelete->id);
    }
}