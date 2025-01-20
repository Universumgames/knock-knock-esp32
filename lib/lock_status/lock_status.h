#pragma once
#include "basicDefs.h"
#include "lock_status_t.h"

HEADER_BEGIN

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

char* get_status_string(SchlossStatus status);

HEADER_END