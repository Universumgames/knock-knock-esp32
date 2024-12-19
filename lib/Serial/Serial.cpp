#include "Serial.h"

// Copied from
// https://github.com/espressif/esp-idf/blob/master/examples/peripherals/uart/uart_events/main/uart_events_example_main.c
// Modified by: Tom Arlt

#include <cstdio>
#include <cstring>
#include <list>
#include <CommandLine.h>
#include <driver/uart.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include "_Serial.hpp"
#include <queue>
#include <string>

/**
 * This example shows how to use the UART driver to handle special UART events.
 *
 * It also reads data from UART0 directly, and echoes it to console.
 *
 * - Port: UART0
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: on
 * - Pin assignment: TxD (default), RxD (default)
 */

static std::list<std::pair<SerialInterrupt, SerialInterruptCallback>>
    interruptCallbacks;

static std::pmr::string line;
static std::queue<char> charQueue;

void serialWrite(const char* data) {
    uart_write_bytes(HW_UART_NUM, data, strlen(data));
}

void serialFlush() {
    uart_flush(HW_UART_NUM);
}

void serialRead(char* data, const int len) {
    for (int i = 0; i < len - 1; i++) {
        if (charQueue.empty()) {
            data[i] = '\0';
            return;
        }
        data[i] = charQueue.front();
        charQueue.pop();
    }
    data[len - 1] = '\0';
}

char serialReadChar() {
    if (charQueue.empty()) {
        return '\0';
    }
    char nextChar = charQueue.front();
    charQueue.pop();
    return nextChar;
}

char* serialReadLine() {
    if (line.empty()) {
        return nullptr;
    }
    char* lineCopy = new char[line.size() + 1];
    std::strcpy(lineCopy, line.c_str());
    line.clear();
    return lineCopy;
}

int interruptHandlerCountChar = 0;
int interruptHandlerCountLine = 0;

void attachSerialInterrupt(SerialInterruptCallback callback,
                           SerialInterrupt interrupt) {
    interruptCallbacks.emplace_back(interrupt, callback);
    if (interrupt == SERIAL_INTERRUPT_CHAR) {
        interruptHandlerCountChar++;
    } else if (interrupt == SERIAL_INTERRUPT_LINE) {
        interruptHandlerCountLine++;
    }
}

void uartCharHandler(char c) {
    if (interruptHandlerCountChar > 0) {
        charQueue.push(c);
        charInterruptHandler(c);
    }

    if (interruptHandlerCountLine > 0) {
        if (c == '\n') {
            lineInterruptHandler(line.c_str());
            line.clear();
        } else if (c != '\r')
            line.push_back(c);
    }
}

void charInterruptHandler(char c) {
    for (auto& callback : interruptCallbacks) {
        if (callback.first == SERIAL_INTERRUPT_CHAR) {
            callback.second(&c);
        }
    }
}

void lineInterruptHandler(const char* c) {
    for (auto& callback : interruptCallbacks) {
        if (callback.first == SERIAL_INTERRUPT_LINE) {
            callback.second(c);
        }
    }
}