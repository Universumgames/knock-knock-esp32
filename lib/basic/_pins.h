#pragma once

#define PIN_STATUS_LED (8)
#define PIN_LOCK_RELAY (3)
// Serial: 20,21
// Storage: 4,5,6,7
// Piezo: 0

HEADER_BEGIN
typedef enum {
    PIN_BUTTON_NONE = -2,
    PIN_BUTTON_UP = 2,
    PIN_BUTTON_DOWN = 1,
    PIN_BUTTON_RECORD = 18,
    PIN_BUTTON_DELETE = 10,
    PIN_BUTTON_PLAY = -1
} MenuButton;
HEADER_END