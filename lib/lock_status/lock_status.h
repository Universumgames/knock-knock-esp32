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

/**
 * @brief initialize the status and the LED
 *
 */
void initialize_lock_state();

/**
 * @brief update the LED status
 *
 * @param status the new status
 */
void updateLEDStatus(SchlossStatus status);

/**
 * @brief get the current status for other funktions
 *
 */
SchlossStatus get_current_status();

HEADER_END