#pragma once
#include "basicDefs.h"
#include <queue>

#define HW_UART_NUM UART_NUM_0

void uartCharHandler(char c);

void charInterruptHandler(const char c);

void lineInterruptHandler(const char* c);