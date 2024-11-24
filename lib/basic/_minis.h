#pragma once

// #define max(a, b) ((a) > (b) ? (a) : (b))

// reserve memory for a value and store it in this pointer, return the pointer
#define storeAsPtr(type, value)                                                \
    ({                                                                         \
        type* ptr = (type*)malloc(sizeof(type));                               \
        if (ptr != NULL)                                                       \
            *ptr = value;                                                      \
        else                                                                   \
            LOGE("storeAsPtr", "Failed to allocate memory for %s", #type);     \
        ptr;                                                                   \
    })

#define storeAsVoidPtr(value) storeAsPtr(void, value)