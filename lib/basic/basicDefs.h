#pragma once
#include <stdint.h>

// include for bool, true and false
#include <stdbool.h>

#define HIGH 1
#define LOW 0

#ifdef __cplusplus
#define HEADER_BEGIN extern "C" {
#define HEADER_END }
#else
#define HEADER_BEGIN
#define HEADER_END
#endif