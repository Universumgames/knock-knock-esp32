#include "stringHelper.h"

#include <stdlib.h>
#include <string.h>

char* intToString(int value, int base) {
    static char buf[32] = {0};
    memset(buf, 0, 32);
    int i = 30;
    if (value == 0) {
        buf[i] = '0';
        return &buf[i];
    }
    int isNegative = value < 0;
    if (isNegative) value = -value;
    for (; value && i; --i, value /= base)
        buf[i] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
    if (isNegative) buf[i--] = '-';
    return &buf[i + 1];
}

int stringToInt(const char* str, int base) {
    return strtol(str, NULL, base);
}

int* splitString(const char* str, const char* delim, int* len) {
    int* indices = (int*)calloc(sizeof(int), strlen(str));
    int count = 1;
    int delimLen = strlen(delim);
    int strLen = strlen(str);
    // indices[0] = 0; // first index is always 0, uncommented because calloc sets all values to 0
    for (int i = 1; i < strLen; i++) {
        if (strncmp(str + i, delim, delimLen) == 0) {
            indices[count++] = i;
        }
    }
    if (len != NULL) *len = count;
    return indices;
}