#pragma once
#include "basicDefs.h"

#define PATTERN_FILE_VERSION ((uint8_t)1)

HEADER_BEGIN

typedef uint16_t analog_v;     // Pattern-Sensor Data
typedef uint16_t delta_t;      // Pattern-Sensor Data
typedef uint8_t pattern_ver_t; // Pattern version
typedef uint32_t pattern_id_t; // Pattern ID

typedef struct {
    pattern_ver_t patternVersion;
    pattern_id_t id;
    delta_t totalDurationMillis;
    size_t lengthPattern;
    delta_t* deltaTimesMillis;
} PatternData;

void logPatternData(PatternData* pattern);

HEADER_END