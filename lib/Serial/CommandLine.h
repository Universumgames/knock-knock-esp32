#pragma once
#include "basicDefs.h"

HEADER_BEGIN

typedef enum {
    UNKNOWN,
    HELP,
    LS_FLAGS,
    LIST_PATTERNS,
    ENCODER_LOG_BRANCHES,
    RECORDER_PAUSE,
    ENCODER_STORE_ALL
} Command;

void initCommandLine();

Command parseCommand(const char* command);

void handleCommand(const char* command);

HEADER_END