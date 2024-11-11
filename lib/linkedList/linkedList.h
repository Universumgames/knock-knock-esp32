#pragma once
#include <stddef.h>

#include "basicDefs.h"

HEADER_BEGIN

struct __ll_list;

typedef struct __ll_list list_t;

list_t* list_create();

void list_destroy(list_t* list);

void __list_push_back(list_t* list, void* data);

void __list_push_front(list_t* list, void* data);

void* list_pop_back(list_t* list);

void* list_pop_front(list_t* list);

void* list_get(list_t* list, size_t index);

size_t list_size(const list_t* list);

void list_foreach(list_t* list, void (*callback)(void*));

void* list_next(list_t* list);
void list_reset(list_t* list);

#define list_push_back(list, obj) __list_push_back(list, (void*)(obj))
#define list_push_front(list, obj) __list_push_front(list, (void*)(obj))

HEADER_END