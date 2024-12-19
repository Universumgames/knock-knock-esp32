#include "../PatternStorage/PatternStorage.h"
#include "CommandLine.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_intr_alloc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "Serial.h"
#include <freertos/task.h>
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

Command parseCommand(const char* command) {
    if (strcmp(command, CMD_STR_HELP) == 0) {
        return HELP;
    }
    if (strcmp(command, CMD_STR_LS_FLAGS) == 0) {
        return LS_FLAGS;
    }
    if (strcmp(command, CMD_STR_LIST) == 0) {
        return LIST_PATTERNS;
    }
    if (strcmp(command, CMD_STR_ENCODER_LOG_BRANCHES) == 0) {
        return ENCODER_LOG_BRANCHES;
    }
    if (strcmp(command, CMD_STR_RECORDER_PAUSE) == 0) {
        return RECORDER_PAUSE;
    }
    if (strcmp(command, CMD_STR_ENCODER_STORE_ALL) == 0) {
        return ENCODER_STORE_ALL;
    }
    return UNKNOWN;
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
        case UNKNOWN:
            LOGE(TAG_COMMAND_LINE, "Unknown command: %s", command);
            break;
        default:
            LOGE(TAG_COMMAND_LINE, "Unhandled command: %s", command);
    }
}