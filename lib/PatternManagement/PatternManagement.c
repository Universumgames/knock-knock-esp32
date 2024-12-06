#include "PatternManagement.h"

#include <PatternStorage.h>
#include <linkedList.h>
#include <lock_status.h>
#include <pattern_play.h>

static size_t selectedPatternIndex = 0;

void _handleButtonPress(uint8_t pin) {
    LinkedList patterns = getPatterns();
    size_t patternLength = list_size(patterns);

    if (pin == PIN_BUTTON_PLAY) {
        // play button was pressed
        PatternData* toPlay =
            (PatternData*)list_get(patterns, selectedPatternIndex);
        playPattern(toPlay);
    } else if (pin == PIN_BUTTON_UP) {
        // up button was pressed
        selectedPatternIndex =
            (selectedPatternIndex + patternLength - 1) % patternLength;
    } else if (pin == PIN_BUTTON_DOWN) {
        // down button was pressed
        selectedPatternIndex = (selectedPatternIndex + 1) % patternLength;
    } else if (pin == PIN_BUTTON_RECORD) {
        // record button was pressed
        updateLEDStatus(MUSTER_AUFNAHME);
    } else if (pin == PIN_BUTTON_DELETE) {
        // delete button was pressed
        PatternData* toDelete =
            (PatternData*)list_get(patterns, selectedPatternIndex);
        deletePattern(toDelete->id);
    }
}