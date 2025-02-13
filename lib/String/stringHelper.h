#pragma once
#include "basicDefs.h"

HEADER_BEGIN

enum Base_t {
    BASE_BINARY = 2,
    BASE_OCTAL = 8,
    BASE_DECIMAL = 10,
    BASE_HEXADECIMAL = 16
};

typedef enum Base_t Base;

/**
 * @brief Convert an integer to a string
 * WARNING: This function uses a static buffer. If you need to keep the result,
 * copy it to another buffer.
 *
 * @param value the integer to convert
 * @param base the base to convert the integer to
 * @return char*
 */
char* intToString(int value, Base base);

/**
 * @brief Convert a long to a string
 * WARNING: This function uses a static buffer. If you need to keep the result,
 * copy it to another buffer.
 *
 * @param value the long to convert
 * @param base the base to convert the long to
 * @return char*
 */
char* longToString(long value, Base base);

char* ulongToString(unsigned long value, Base base);

/**
 * @brief Convert a string to an integer
 *
 * @param str the string to convert
 * @param base the base of the integer
 * @return int the integer
 */
int stringToInt(const char* str, int base);

/**
 * @brief Splits a string by a delimiter and returns the start index of each
 * substring
 *
 * @param str the string to split
 * @param delim the delimiter to split the string by
 * @param len the length of the returned array
 * @return int* the start index of each substring
 */
size_t* splitString(const char* str, const char* delim, size_t* len);

/**
 * @brief Get a substring of a string
 * WARNING: This function allocates memory for the substring, make sure to free
 * it after usage
 *
 * @param str the string to get the substring from
 * @param start the start index of the substring
 * @param end the end index of the substring
 * @return char* the substring
 */
char* substring(const char* str, int start, int end);

/**
 * @brief Concatenate two strings
 * WARNING: This function allocates memory for the concatenated string, make
 * sure to free it after usage
 *
 * @param str1 the first string
 * @param str2 the second string
 * @return char* the concatenated string
 */
char* concat(const char* str1, const char* str2);

/**
 * @brief Concatenate three strings
 * WARNING: This function allocates memory for the concatenated string, make
 * sure to free it after usage
 *
 * @param str1 the first string
 * @param str2 the second string
 * @param str3 the third string
 * @return char* the concatenated string
 */
char* concat3(const char* str1, const char* str2, const char* str3);

/**
 * @brief Generate a random string
 * WARNING: This function allocates memory for the random string, make sure to
 * free it after usage
 *
 * @param len the length of the random string
 * @return char* the random string
 */
char* randomString(int len);

HEADER_END