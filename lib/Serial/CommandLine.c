#include "../PatternStorage/PatternStorage.h"
#include "CommandLine.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "sdkconfig.h"

#include "../lock_open/lock_open.h"
#include "Serial.h"
#include "stringHelper.h"
#include <string.h>

#define PATTERN_CHR_NUM (3)
#define UART_RX_BUFFER_SIZE 1024

static char* TAG_COMMAND_LINE = "CommandLine";

void initCommandLine() {
    attachSerialInterrupt(handleCommand, SERIAL_INTERRUPT_LINE);
}

#define CMD_STR_HELP "help"
#define CMD_STR_LS_FLAGS "flags"
#define CMD_STR_LIST "ls"
#define CMD_STR_ENCODER_LOG_BRANCHES "elb"
#define CMD_STR_RECORDER_PAUSE "rp"
#define CMD_STR_ENCODER_STORE_ALL "esa"
#define CMD_STR_UNLOCK_TRIGGER "unlock"

Command parseCommand(const char* command) {
    size_t splitLen = 0;
    size_t* arr = splitString(command, " ", &splitLen);
    char* cmd = substring(command, 0, splitLen > 1 ? arr[1] : strlen(command));
    Command ret = UNKNOWN;
    if (cmd == NULL) {
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_HELP) == 0) {
        ret = HELP;
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_LS_FLAGS) == 0) {
        ret = LS_FLAGS;
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_LIST) == 0) {
        ret = LIST_PATTERNS;
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_ENCODER_LOG_BRANCHES) == 0) {
        ret = ENCODER_LOG_BRANCHES;
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_RECORDER_PAUSE) == 0) {
        ret = RECORDER_PAUSE;
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_ENCODER_STORE_ALL) == 0) {
        ret = ENCODER_STORE_ALL;
        goto command_parse_end;
    }
    if (strcmp(cmd, CMD_STR_UNLOCK_TRIGGER) == 0) {
        ret = TRIGGER_UNLOCK;
        goto command_parse_end;
    }

command_parse_end:
    free(arr);
    free(cmd);
    return ret;
}

void handleCommand(const char* command) {
    Command cmd = parseCommand(command);
    switch (cmd) {
        case HELP:
            printf("\nAvailable commands:\n");
            printf("\t%s - show this help\n", CMD_STR_HELP);
            printf("\t%s - list all flags\n", CMD_STR_LS_FLAGS);
            printf("\t%s - list patterns\n", CMD_STR_LIST);
            printf("\t%s - toggle encoder log branches\n",
                   CMD_STR_ENCODER_LOG_BRANCHES);
            printf("\t%s - toggle recorder pause\n", CMD_STR_RECORDER_PAUSE);
            printf("\t%s - toggle encoder store all patterns to file\n",
                   CMD_STR_ENCODER_STORE_ALL);
            printf("\t%s - trigger unlock\n", CMD_STR_UNLOCK_TRIGGER);
            break;
        case LS_FLAGS:
            printf("\nListing flags\n");
            printf("\tEncoder log branches: %s\n",
                   dflag_pattern_encoder_printf_if_branches ? "enabled"
                                                            : "disabled");
            printf("\tRecorder pause: %s\n",
                   dflag_pattern_recorder_pause ? "enabled" : "disabled");
            printf("\tEncoder store all: %s\n",
                   dflag_pattern_store_recorded_pattern ? "enabled"
                                                        : "disabled");
            break;
        case LIST_PATTERNS:
            printf("\nListing patterns\n");
            listPatternsToConsole();
            break;
        case ENCODER_LOG_BRANCHES:
            dflag_pattern_encoder_printf_if_branches =
                !dflag_pattern_encoder_printf_if_branches;
            printf("\tEncoder log branches: %s\n",
                   dflag_pattern_encoder_printf_if_branches ? "enabled"
                                                            : "disabled");
            break;
        case RECORDER_PAUSE:
            dflag_pattern_recorder_pause = !dflag_pattern_recorder_pause;
            printf("\tRecorder pause: %s\n",
                   dflag_pattern_recorder_pause ? "enabled" : "disabled");
            break;
        case ENCODER_STORE_ALL:
            dflag_pattern_store_recorded_pattern =
                !dflag_pattern_store_recorded_pattern;
            printf("\tEncoder store all: %s\n",
                   dflag_pattern_store_recorded_pattern ? "enabled"
                                                        : "disabled");
            break;
        case TRIGGER_UNLOCK:
            printf("\nTriggering unlock\n");
            openLock();
            break;
        case UNKNOWN:
            LOGE(TAG_COMMAND_LINE, "Unknown command: %s", command);
            break;
        default:
            LOGE(TAG_COMMAND_LINE, "Unhandled command: %s", command);
    }
}