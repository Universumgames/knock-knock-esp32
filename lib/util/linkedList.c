#include "linkedList.h"

#include <stdlib.h>

typedef struct __node {
    void* data;
    struct __node* next;
} node_t;

struct __list {
    node_t* head;
    node_t* tail;
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
    node_t* current = list->head;
    while (current != NULL) {
        node_t* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void list_push_back(list_t* list, void* data) {
    node_t* node = malloc(sizeof(node_t));
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

void list_push_front(list_t* list, void* data) {
    node_t* node = malloc(sizeof(node_t));
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
    node_t* current = list->head;
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
    node_t* next = list->head->next;
    free(list->head);
    list->head = next;
    list->size--;
    return data;
}

void* list_get(list_t* list, size_t index) {
    if (index >= list->size) {
        return NULL;
    }
    node_t* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

size_t list_size(list_t* list) {
    return list->size;
}

void list_foreach(list_t* list, void (*callback)(void*)) {
    node_t* current = list->head;
    while (current != NULL) {
        callback(current->data);
        current = current->next;
    }
}
