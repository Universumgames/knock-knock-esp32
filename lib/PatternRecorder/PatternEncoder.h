#pragma once
#include "PatternTypes.h"
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief Initialize the pattern recorder
 *
 * @return true if the initialization was successful
 * @return false if the initialization failed
 */
bool initPatternEncoder();

/**
 * @brief Consecutively encode the value and the delta time into a PatternData
 * struct Encode the recorded analog value and the delta time since the last
 * `encode` call returns a PatternData struct with the encoded data when a
 * pattern is complete, if its not detecting a pattern or the pattern is not
 * complete it returns NULL
 *
 * @param value the value to encode
 * @param deltaMs the delta time in milliseconds
 * @return PatternData* the encoded pattern data or NULL if the pattern is not
 * complete
 */
PatternData* encodeAnalogData(analog_v value, delta_t deltaMs);

HEADER_END