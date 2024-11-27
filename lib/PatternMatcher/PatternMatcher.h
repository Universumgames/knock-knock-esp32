#pragma once
#include "PatternTypes.h"
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief Match the given pattern with the patterns in the storage
 *
 * @param pattern The pattern to match
 * @param matchedPattern The matched pattern, can be NULL
 * @return true if a pattern was matched, false otherwise
 */
bool matchPattern(const PatternData* pattern, PatternData* matchedPattern);

HEADER_END