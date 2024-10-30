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
    if (indices == NULL) return NULL;
    int count = 1;
    int delimLen = strlen(delim);
    int strLen = strlen(str);
    for (int i = 1; i < strLen; i++) {
        if (strncmp(str + i, delim, delimLen) == 0) {
            indices[count++] = i;
        }
    }
    if (len != NULL) *len = count;
    return indices;
}

char* substring(const char* str, int start, int end) {
    int strLen = strlen(str);
    if (start < 0 || start >= strLen || end < 0 || end >= strLen || start > end) return NULL;
    int len = end - start + 1;
    char* substr = (char*)calloc(sizeof(char), len + 1);
    if (substr == NULL) return NULL;
    memcpy(substr, str + start, len);
    return substr;
}

char* concat(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* str = (char*)calloc(sizeof(char), len1 + len2 + 1);
    if (str == NULL) return NULL;
    memcpy(str, str1, len1);
    memcpy(str + len1, str2, len2);
    return str;
}

char* concat3(const char* str1, const char* str2, const char* str3) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len3 = strlen(str3);
    char* str = (char*)calloc(sizeof(char), len1 + len2 + len3 + 1);
    if (str == NULL) return NULL;
    memcpy(str, str1, len1);
    memcpy(str + len1, str2, len2);
    memcpy(str + len1 + len2, str3, len3);
    return str;
}

char* randomString(int len) {
    static char* charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static int charsetLen = 62;
    char* str = (char*)calloc(sizeof(char), len + 1);
    if (str == NULL) return NULL;
    for (int i = 0; i < len; i++) {
        str[i] = charset[rand() % charsetLen];
    }
    return str;
}