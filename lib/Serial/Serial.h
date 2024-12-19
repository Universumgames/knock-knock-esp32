#pragma once
#include "basicDefs.h"

HEADER_BEGIN

/**
 * @brief initialize Hardware Serial
 *
 * @param baud the baud rate to use
 */
void beginSerial(int baud);

/**
 * @brief write a string to the serial port
 *
 * @param data the string to write
 */
void serialWrite(const char* data);

/**
 * @brief flush the serial port
 *
 */
void serialFlush();

/**
 * @brief read a string from the serial port buffer
 * WARNING: this function is only reading the buffer, it is not waiting for new
 * data
 *
 * @param data the buffer to write to
 * @param len the length of the buffer
 */
void serialRead(char* data, int len);

/**
 * @brief read a single character from the serial port buffer
 * WARNING: this function is only reading the buffer, it is not waiting for new
 * data
 *
 * @return char the character read
 */
char serialReadChar();

char* serialReadLine();

typedef enum { SERIAL_INTERRUPT_CHAR, SERIAL_INTERRUPT_LINE } SerialInterrupt;

typedef void (*SerialInterruptCallback)(const char*);
void attachSerialInterrupt(SerialInterruptCallback callback,
                           SerialInterrupt interrupt);

HEADER_END