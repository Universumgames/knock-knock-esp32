#pragma once
#include "_logging.h"

#define HEAP_LOG                                                               \
    LOGI("HEAP", "heap: %u, line %s:%d",                                       \
         heap_caps_get_free_size(MALLOC_CAP_8BIT), __FILE__, __LINE__);
