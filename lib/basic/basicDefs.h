#pragma once
#include <stdint.h>

// include for bool, true and false
#include <stdbool.h>

#include "_env.h"
#include "_logging.h"

#define HIGH 1
#define LOW 0

#ifdef __cplusplus
#define HEADER_BEGIN extern "C" {
#define HEADER_END }
#else
#define HEADER_BEGIN
#define HEADER_END
#endif

#if ENV_IS_ESP32
#include "_defs_esp.h"
#elif ENV_IS_NATIVE
#include "_defs_native.h"
#endif

#define CHECK_DO(condition, doX) \
    if (condition) {             \
        doX;                     \
    }

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
