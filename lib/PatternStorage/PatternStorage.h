#pragma once
#include "PatternTypes.h"
#include "basicDefs.h"
#include "linkedList.h"

HEADER_BEGIN

/**
 * @brief Initialize the pattern storage
 * WARNING: on embedded devices, the storage must be mounted before calling this
 * function
 *
 * @return true if the pattern storage was initialized successfully
 */
bool initPatternStorage();

/**
 * @brief Store a pattern in the pattern storage
 * Adds the pattern to the cached pattern storage and saves it to the disk
 *
 * @param pattern the pattern to store
 * @return true if the pattern was stored successfully
 */
bool storePattern(PatternData* pattern);

/**
 * @brief Load all patterns from the disk
 * Load all patterns from the disk and return them as a linked list
 * Caches the patterns in memory, so that they can be accessed faster by
 * getPatterns Clears and frees the cache if called again WARNING: Returns
 * internal linked list, do not free the returned linked list
 *
 * @return LinkedList<PatternData*> the patterns
 */
LinkedList loadPatternsFromDisk();

/**
 * @brief Get the patterns as a linked list
 *
 * @return LinkedList<PatternData*> the patterns
 */
LinkedList getPatterns();

/**
 * @brief Delete a pattern from the pattern storage
 * Deletes the pattern from the cached pattern storage and from the disk
 *
 * @param id the id of the pattern to delete
 * @return true if the pattern was deleted successfully
 */
bool deletePattern(pattern_id_t id);

/**
 * @brief List all patterns to the console
 */
void listPatternsToConsole();

HEADER_END