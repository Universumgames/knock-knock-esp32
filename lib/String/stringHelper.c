#include "stringHelper.h"

#include <stdlib.h>
#include <string.h>

#define MAX_INT_STRING_LEN 32

#define createNumberToCharMethod(type, name)                                   \
    char* name##ToString(type value, Base base) {                              \
        static char buf[MAX_INT_STRING_LEN] = {0};                             \
        memset(buf, 0, MAX_INT_STRING_LEN);                                    \
        int index = MAX_INT_STRING_LEN - 2;                                    \
        if (value == 0) {                                                      \
            buf[index] = '0';                                                  \
            return &buf[index];                                                \
        }                                                                      \
        int isNegative = value < 0;                                            \
        if (isNegative)                                                        \
            value = -value;                                                    \
        for (; value && index; --index, value /= base)                         \
            buf[index] = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base]; \
        if (isNegative)                                                        \
            buf[index--] = '-';                                                \
        return &buf[index + 1];                                                \
    }

createNumberToCharMethod(int, int);
createNumberToCharMethod(long, long);
createNumberToCharMethod(unsigned long, ulong);

int stringToInt(const char* str, int base) {
    return strtol(str, NULL, base);
}

size_t* splitString(const char* str, const char* delim, size_t* len) {
    size_t* indices = (size_t*)calloc(sizeof(size_t), strlen(str));
    if (indices == NULL)
        return NULL;
    int count = 1;
    size_t delimLen = strlen(delim);
    size_t strLen = strlen(str);
    // indices[0] = 0; // first index is always 0, uncommented because calloc
    // sets all values to 0
    for (size_t i = 1; i < strLen; i++) {
        if (strncmp(str + i, delim, delimLen) == 0 || i == strLen - 1) {
            indices[count++] = i;
        }
    }
    if (len != NULL)
        *len = count;
    return indices;
}

char* substring(const char* str, int start, int end) {
    size_t strLen = strlen(str);
    if (start < 0 || start >= strLen || end < 0 || end >= strLen || start > end)
        return strdup(str);
    int len = end - start + 1;
    char* substr = (char*)calloc(sizeof(char), len + 2);
    if (substr == NULL)
        return NULL;
    strncpy(substr, str + start, len);
    return substr;
}

char* concat(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL)
        return NULL;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* str = calloc(sizeof(char), len1 + len2 + 1);
    if (str == NULL)
        return NULL;
    memcpy(str, str1, len1);
    memcpy(str + len1, str2, len2);
    return str;
}

char* concat3(const char* str1, const char* str2, const char* str3) {
    if (str1 == NULL || str2 == NULL || str3 == NULL)
        return NULL;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t len3 = strlen(str3);
    char* str = calloc(sizeof(char), len1 + len2 + len3 + 1);
    if (str == NULL)
        return NULL;
    memcpy(str, str1, len1);
    memcpy(str + len1, str2, len2);
    memcpy(str + len1 + len2, str3, len3);
    return str;
}

char* randomString(int len) {
    const static char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static size_t charsetLen = sizeof(charset);
    char* str = calloc(sizeof(char), len + 1);
    if (str == NULL)
        return NULL;
    for (int i = 0; i < len; i++) {
        str[i] = charset[rand() % charsetLen];
    }
    return str;
}