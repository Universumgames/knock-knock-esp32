#pragma once
#include "PatternTypes.h"
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief Initialize the pattern storage
 * WARNING: on embedded devices, the storage must be mounted before calling this function
 *
 * @return true if the pattern storage was initialized successfully
 */
bool initPatternStorage();

/**
 * @brief Store a pattern in the pattern storage
 *
 * @param pattern the pattern to store
 * @param existingPatterns the existing patterns in the storage, if NULL, the patterns will be loaded
 * @param existingPatternsLen the length of the existing patterns
 * @return true if the pattern was stored successfully
 */
bool storePattern(PatternData* pattern, PatternData* existingPatterns, size_t existingPatternsLen);

/**
 * @brief Load all patterns from the pattern storage
 *
 * @param len the length of the returned array
 * @return PatternData* the patterns
 */
PatternData** loadPatterns(size_t* len);

/**
 * @brief Delete a pattern from the pattern storage
 *
 * @param id the id of the pattern to delete
 * @return true if the pattern was deleted successfully
 */
bool deletePattern(int id);

HEADER_END