#include "stringHelper.hpp"

char* intToString(int value, int base) {
    static char buf[32] = {0};
    int i = 30;
    for (; value && i; --i, value /= base)
        buf[i] = "0123456789abcdef"[value % base];
    return &buf[i + 1];
}