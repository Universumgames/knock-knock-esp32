#pragma once
#include "basicDefs.h"
#include <queue>

#define HW_UART_NUM UART_NUM_0

static const char* TAG_SERIAL = "uart_events";

void uartCharHandler(char c);

void charInterruptHandler(const char c);

void lineInterruptHandler(const char* c);