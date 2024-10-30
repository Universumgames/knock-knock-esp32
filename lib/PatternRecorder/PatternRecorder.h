#pragma once
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief Initialize the pattern recorder, starts the recording task and passes that data to the the pattern matcher
 *
 * @return true if the pattern recorder was initialized successfully
 * @return false if the initialisation failed
 */
bool initPatternRecorder();

HEADER_END