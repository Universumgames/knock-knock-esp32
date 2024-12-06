#pragma once
#include "basicDefs.h"

HEADER_BEGIN
/**
 * @brief various states of the status LED
 *
 */
typedef enum {
    SCHLOSS_VERRIEGELT,
    SCHLOSS_ENTRIEGELT,
    MUSTER_AUFNAHME,
    MUSTER_FAST_KORREKT,
    FEHLERFALL
} SchlossStatus;

HEADER_END
