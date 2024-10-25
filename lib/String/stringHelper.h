#pragma once
#include "basicDefs.h"

HEADER_BEGIN

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

/**
 * @brief Get a substring of a string
 * WARNING: This function allocates memory for the substring, make sure to free it after usage
 *
 * @param str the string to get the substring from
 * @param start the start index of the substring
 * @param end the end index of the substring
 * @return char* the substring
 */
char* substring(const char* str, int start, int end);

/**
 * @brief Concatenate two strings
 * WARNING: This function allocates memory for the concatenated string, make sure to free it after usage
 *
 * @param str1 the first string
 * @param str2 the second string
 * @return char* the concatenated string
 */
char* concat(const char* str1, const char* str2);

/**
 * @brief Concatenate three strings
 * WARNING: This function allocates memory for the concatenated string, make sure to free it after usage
 *
 * @param str1 the first string
 * @param str2 the second string
 * @param str3 the third string
 * @return char* the concatenated string
 */
char* concat3(const char* str1, const char* str2, const char* str3);

/**
 * @brief Generate a random string
 * WARNING: This function allocates memory for the random string, make sure to free it after usage
 *
 * @param len the length of the random string
 * @return char* the random string
 */
char* randomString(int len);

HEADER_END