#pragma once
#include "basicDefs.h"

HEADER_BEGIN

typedef struct {
    int id;
    long* deltaTimes;
    size_t lengthPattern;
    unsigned long durationMillis;
} PatternData;

HEADER_END