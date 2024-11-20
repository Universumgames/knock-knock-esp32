#include "ring_buffer.h"

static const char* TAG_RINGBUFFER = "RingBuffer";

struct ring_buffer__internal {
    size_t size;
    size_t elementSize;
    size_t headIndex;
    void** elements;
};

bool bufferIsUsable(RingBuffer buffer) {
    if (buffer == NULL) {
        LOGE(TAG_RINGBUFFER, "Buffer is NULL");
        return false;
    }
    if (buffer->elements == NULL) {
        LOGE(TAG_RINGBUFFER, "Buffer storage is NULL");
        return false;
    }
    return true;
}

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
        LOGE(TAG_RINGBUFFER, "Failed to allocate memory for elements");
        free(buffer);
        return NULL;
    }
    return buffer;
}

void ringBufferAdd(RingBuffer buffer, void* element) {
    if (!bufferIsUsable(buffer)) {
        return;
    }
    if (element == NULL) {
        LOGE(TAG_RINGBUFFER, "Element is NULL");
        return;
    }

    void* oldElement = buffer->elements[buffer->headIndex];
    if (oldElement != NULL) {
        free(oldElement);
    }
    buffer->elements[buffer->headIndex] = element;
    buffer->headIndex = (buffer->headIndex + 1) % buffer->size;
}

void** ringBufferGetAll(RingBuffer buffer) {
    if (!bufferIsUsable(buffer)) {
        return NULL;
    }
    return buffer->elements;
}

void** ringBufferGetAllInOrder(RingBuffer buffer) {
    if (!bufferIsUsable(buffer)) {
        return NULL;
    }
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
    LOGD("RingBuffer", "Index: %d, BufferIndex: %u", index, bufferIndex);
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