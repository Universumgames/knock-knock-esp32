#pragma once
#include <stddef.h>

#include "basicDefs.h"

HEADER_BEGIN

struct __ll_list;

typedef struct __ll_list linked_list_t;
typedef linked_list_t* LinkedList;

LinkedList list_create();

void list_destroy(LinkedList list);

void list_clear(LinkedList list, bool freeData);

LinkedList list_copy_shallow(LinkedList list);

void __list_push_back(LinkedList list, void* data);

void __list_push_front(LinkedList list, void* data);

void* list_pop_back(LinkedList list);

void* list_pop_front(LinkedList list);

void* list_get(LinkedList list, size_t index);

size_t list_size(const LinkedList list);

void list_foreach(LinkedList list, void (*callback)(void*));

void list_removeIndex(LinkedList list, size_t index);

void* list_next(LinkedList list);
void* list_prev(LinkedList list);
void* list_reset(LinkedList list);

#define list_push_back(list, obj) __list_push_back(list, (void*)(obj))
#define list_push_front(list, obj) __list_push_front(list, (void*)(obj))

#define list_foreach_raw(list, type, method)                                   \
    {                                                                          \
        type* it = (type*)list_reset(list);                                    \
        while (it != NULL) {                                                   \
            method;                                                            \
            it = (type*)list_next(list);                                       \
        }                                                                      \
    }

HEADER_END