#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Convert an integer to a string
 * WARNING: This function uses a static buffer. If you need to keep the result, copy it to another buffer.
 *
 * @param value the integer to convert
 * @param base the base to convert the integer to
 * @return char*
 */
char* intToString(int value, int base);

int stringToInt(const char* str, int base);

/**
 * @brief Splits a string by a delimiter and returns the start index of each substring
 *
 * @param str the string to split
 * @param delim the delimiter to split the string by
 * @param len the length of the returned array
 * @return int* the start index of each substring
 */
int* splitString(const char* str, const char* delim, int* len);

#ifdef __cplusplus
}
#endif