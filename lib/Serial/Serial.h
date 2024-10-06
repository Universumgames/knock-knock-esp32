#pragma once

// Created by: Tom Arlt

void beginSerial(int baud);

void serialWrite(const char *data);

void serialRead(char *data, int len);

char serialReadChar();