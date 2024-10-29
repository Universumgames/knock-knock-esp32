#pragma once

#define CHECK_DO(condition, doX) \
    if (condition) {             \
        doX;                     \
    }

#define CHECK_ESP_DO(esp, doX) \
    CHECK_DO(esp != ESP_OK, doX)

#define CHECK_NULL_DO(ptr, doX) \
    CHECK_DO(ptr == NULL, doX)

#define CHECK_NULL_GOTO(ptr, label) \
    CHECK_NULL_DO(ptr, goto label)

#define CHECK_NULL_RET(ptr, returnVal) \
    CHECK_NULL_DO(ptr, return returnVal)

#define CHECK_NULL_GOTO_LOG_DO(ptr, label, log, doX) \
    CHECK_NULL_DO(ptr, {log; doX; goto label; })

#define CHECK_NULL_GOTO_LOG(ptr, label, log) \
    CHECK_NULL_GOTO_LOG_DO(ptr, label, log, )
