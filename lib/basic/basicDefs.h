#pragma once
#include "_env.h"
#include "_lib_includes.h"
#include "_logging.h"

#define HIGH 1
#define LOW 0

#ifdef __cplusplus
#define HEADER_BEGIN extern "C" {
#define HEADER_END }
#define CPP_BEGIN extern "C"
#else
#define HEADER_BEGIN
#define HEADER_END
#define CPP_BEGIN
#endif

#if ENV_IS_ESP32
#include "_defs_esp.h"
#include "_minis_esp.h"
#elif ENV_IS_NATIVE
#include "_defs_native.h"
#endif

#include "_checks.h"
#include "_minis.h"
#include "_pins.h"
#include "_threads.h"