#pragma once
#include "basicDefs.h"

#define PATTERN_FILE_VERSION ((uint8_t)1)

HEADER_BEGIN

typedef uint16_t analog_v;     // Pattern-Sensor Data
typedef uint16_t delta_t;      // Pattern-Sensor Data
typedef uint8_t pattern_ver_t; // Pattern version

typedef struct {
    pattern_ver_t patternVersion;
    int id;
    delta_t totalDurationMillis;
    size_t lengthPattern;
    delta_t* deltaTimesMillis;
} PatternData;

void logPatternData(PatternData* pattern);

HEADER_END