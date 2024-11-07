#pragma once

// #define max(a, b) ((a) > (b) ? (a) : (b))

// reserve memory for a value and store it in this pointer, return the pointer
#define storeAsPtr(type, value)                                                \
    ({                                                                         \
        type* ptr = (type*)malloc(sizeof(type));                               \
        *ptr = value;                                                          \
        ptr;                                                                   \
    })
