#pragma once
#include "PatternTypes.h"
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief Initialize the pattern storage
 *
 * @return true if the pattern storage was initialized successfully
 */
bool initPatternStorage();

/**
 * @brief Store a pattern in the pattern storage
 *
 * @param pattern the pattern to store
 * @return true if the pattern was stored successfully
 */
bool storePattern(PatternData* pattern);

/**
 * @brief Load all patterns from the pattern storage
 *
 * @param len the length of the returned array
 * @return PatternData* the patterns
 */
PatternData* loadPatterns(size_t* len);

HEADER_END