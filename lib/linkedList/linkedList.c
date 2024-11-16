#include "linkedList.h"

#include <stdlib.h>

typedef struct __llnode {
    void* data;
    struct __llnode* next;
} ll_node_t;

struct __ll_list {
    ll_node_t* head;
    ll_node_t* tail;
    ll_node_t* current;
    size_t size;
};

list_t* list_create() {
    list_t* list = malloc(sizeof(list_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void list_destroy(list_t* list) {
    ll_node_t* current = list->head;
    while (current != NULL) {
        ll_node_t* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void __list_push_back(list_t* list, void* data) {
    ll_node_t* node = malloc(sizeof(ll_node_t));
    node->data = data;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void __list_push_front(list_t* list, void* data) {
    ll_node_t* node = malloc(sizeof(ll_node_t));
    node->data = data;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) {
        list->tail = node;
    }
    list->size++;
}

void* list_pop_back(list_t* list) {
    if (list->size == 0) {
        return NULL;
    }
    void* data = list->tail->data;
    ll_node_t* current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }
    free(list->tail);
    list->tail = current;
    list->size--;
    return data;
}

void* list_pop_front(list_t* list) {
    if (list->size == 0) {
        return NULL;
    }
    void* data = list->head->data;
    ll_node_t* next = list->head->next;
    free(list->head);
    list->head = next;
    list->size--;
    return data;
}

void* list_get(list_t* list, size_t index) {
    if (index >= list->size) {
        return NULL;
    }
    ll_node_t* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

size_t list_size(const list_t* list) {
    return list->size;
}

void list_foreach(list_t* list, void (*callback)(void*)) {
    ll_node_t* current = list->head;
    while (current != NULL) {
        callback(current->data);
        current = current->next;
    }
}

void list_reset(list_t* list) {
    list->current = list->head;
}

void* list_next(list_t* list) {
    if (list->current == NULL)
        return NULL;
    void* data = list->current->data;
    list->current = list->current->next;
    return data;
}