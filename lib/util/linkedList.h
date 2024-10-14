#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __list;

typedef struct __list list_t;

list_t* list_create();

void list_destroy(list_t* list);

void list_push_back(list_t* list, void* data);

void list_push_front(list_t* list, void* data);

void* list_pop_back(list_t* list);

void* list_pop_front(list_t* list);

void* list_get(list_t* list, size_t index);

size_t list_size(list_t* list);

void list_foreach(list_t* list, void (*callback)(void*));

#ifdef __cplusplus
}
#endif