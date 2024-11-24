#pragma once
#include "_logging.h"
#include <esp_heap_caps.h>
#include <esp_system.h>

/*#define HEAP_LOG \
    LOGI("HEAP", "heap: %u, line %s:%d",                                       \
         heap_caps_get_free_size(MALLOC_CAP_8BIT), __FILE__, __LINE__);        \
    heap_caps_print_heap_info(MALLOC_CAP_32BIT | MALLOC_CAP_8BIT);             \
    uint32_t freelen = esp_get_free_heap_size();                               \
    uint32_t minimum = esp_get_minimum_free_heap_size();                       \
    printf("heap_caps_get_free_size: %d\n",                                    \
           heap_caps_get_free_size(MALLOC_CAP_8BIT));                          \
    printf("heap_caps_get_minimum_free_size: %d\n",                            \
           heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT));                  \
    printf("heap_caps_get_largest_free_block: %d\n",                           \
           heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));*/
