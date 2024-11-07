#pragma once
#include "basicDefs.h"

#define PATTERN_FILE_VERSION ((uint8_t)1)

HEADER_BEGIN

typedef uint16_t analog_v; // Pattern-Sensor Data

typedef struct {
    uint8_t patternVersion;
    int id;
    unsigned long totalDurationMillis;
    size_t lengthPattern;
    unsigned long* deltaTimesMillis;
} PatternData;

HEADER_END