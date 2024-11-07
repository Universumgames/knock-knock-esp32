#include "ring_buffer.h"

struct ring_buffer__internal {
    size_t size;
    size_t elementSize;
    size_t headIndex;
    void** elements;
};

RingBuffer ringBufferCreate(size_t size, size_t elementSize) {
    RingBuffer buffer = calloc(sizeof(struct ring_buffer__internal), 1);
    if (buffer == NULL) {
        return NULL;
    }
    buffer->headIndex = 0;
    buffer->size = size;
    buffer->elementSize = elementSize;
    buffer->elements = calloc(sizeof(void*), size);
    if (buffer->elements == NULL) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

void ringBufferAdd(RingBuffer buffer, void* element) {
    if (buffer == NULL || element == NULL)
        return;
    free(buffer->elements[buffer->headIndex]);
    buffer->elements[buffer->headIndex] = element;
    buffer->headIndex = (buffer->headIndex + 1) % buffer->size;
}

void** ringBufferGetAll(RingBuffer buffer) {
    if (buffer == NULL)
        return NULL;
    return buffer->elements;
}

void** ringBufferGetAllInOrder(RingBuffer buffer) {
    if (buffer == NULL)
        return NULL;
    void** elements = calloc(sizeof(void*), buffer->size);
    if (elements == NULL)
        return NULL;
    for (size_t i = 0; i < buffer->size; i++) {
        elements[i] = buffer->elements[(buffer->headIndex + i) % buffer->size];
    }
    return elements;
}

void ringBufferDestroy(RingBuffer buffer) {
    if (buffer == NULL)
        return;
    free(buffer->elements);
    free(buffer);
}

void ringBufferDestroyWithElements(RingBuffer buffer) {
    if (buffer == NULL)
        return;
    for (size_t i = 0; i < buffer->size; i++) {
        free(buffer->elements[i]);
    }
    free(buffer->elements);
    free(buffer);
}

void* ringBufferGetElement(RingBuffer buffer, int index) {
    if (buffer == NULL)
        return NULL;
    int indexToUse = index;
    // if index is negative, add the buffer length to it
    while (indexToUse < 0) {
        indexToUse += buffer->size;
    }
    size_t bufferIndex = (buffer->headIndex + indexToUse) % buffer->size;
    LOGD("RingBuffer", "Index: %d, BufferIndex: %d", index, bufferIndex);
    return buffer->elements[bufferIndex];
}

void ringBufferClear(RingBuffer buffer) {
    if (buffer == NULL)
        return;
    for (size_t i = 0; i < buffer->size; i++) {
        if (buffer->elements[i] != NULL)
            free(buffer->elements[i]);
    }
    free(buffer->elements);
    buffer->headIndex = 0;
}

int getRingBufferHead(RingBuffer buffer) {
    if (buffer == NULL)
        return -1;
    return buffer->headIndex;
}