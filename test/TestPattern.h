#pragma once
#include "PatternTypes.h"
#include "linkedList.h"

#define TEST_PATTERN_CREATE(idT, duration, length, ...)                        \
    delta_t deltaTimes##idT[] = {__VA_ARGS__};                                 \
    PatternData testPattern##idT = {.patternVersion = PATTERN_FILE_VERSION,    \
                                    .id = idT,                                 \
                                    .totalDurationMillis = duration,           \
                                    .lengthPattern = length,                   \
                                    .deltaTimesMillis = deltaTimes##idT}

#define TEST_PATTERN_DEINIT(id)

// sample patterns
TEST_PATTERN_CREATE(0, 1000, 3, 500, 500, 500);
TEST_PATTERN_CREATE(5, 3800, 6, 1000, 300, 1000, 500, 1000);

LinkedList createTestPatternStorage() {
    LinkedList patterns = list_create();
    list_push_back(patterns, storeAsPtr(PatternData*, &testPattern0));
    list_push_back(patterns, storeAsPtr(PatternData*, &testPattern5));
    return patterns;
}