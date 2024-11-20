#pragma once
#include "PatternTypes.h"
#include "basicDefs.h"
#include "linkedList.h"

HEADER_BEGIN

// TODO(tom) convert pattern list to linked list

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
 * @param existingPatterns the existing patterns in the storage, if NULL, the
 * patterns will be loaded
 * @param existingPatternsLen the length of the existing patterns
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
bool deletePattern(int id);

HEADER_END