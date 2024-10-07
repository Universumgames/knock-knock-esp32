#pragma once

// Created by: Tom Arlt

#ifdef __cplusplus
extern "C" {
#endif

void beginSerial(int baud);

void serialWrite(const char *data);

void serialFlush();

void serialRead(char *data, int len);

char serialReadChar();

#ifdef __cplusplus
}
#endif