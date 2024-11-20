#pragma once
#include "basicDefs.h"

HEADER_BEGIN

struct ring_buffer__internal;

typedef struct ring_buffer__internal* RingBuffer;

/**
 * @brief Create a new ring buffer
 *
 * @param size The element size of the ring buffer
 * @param elementSize The size of the elements in the ring buffer
 * @return RingBuffer The created ring buffer
 */
RingBuffer ringBufferCreate(size_t size, size_t elementSize);

/**
 * @brief Add an element to the ring buffer, deletes the oldest element
 *
 * @param buffer The ring buffer to add the element to
 * @param element The element to add
 */
void ringBufferAdd(RingBuffer buffer, void* element);

#define ringBufferAddElement(buffer, element)                                  \
    ringBufferAdd(buffer, storeAsVoidPtr(element))

/**
 * @param buffer The ring buffer to get the elements from
 * @return void* The elements in the ring buffer as an array
 */
void** ringBufferGetAll(RingBuffer buffer);

/**
 * @param buffer The ring buffer to get the elements from in order of ring
 * buffer state
 * @return void* The elements in the ring buffer as an array
 */
void** ringBufferGetAllInOrder(RingBuffer buffer);

/**
 * @brief Destroy the ring buffer
 * WARNING: This will free the memory of the ring buffer, but not the elements
 */
void ringBufferDestroy(RingBuffer buffer);

/**
 * @brief Destroy the ring buffer and the elements
 * WARNING: This will free the memory of the ring buffer and the elements
 */
void ringBufferDestroyWithElements(RingBuffer buffer);

/**
 * @brief Get an element from the ring buffer relative to the head index
 * @return void* The element at the index
 */
void* ringBufferGetElement(RingBuffer buffer, int index);

/**
 * @brief Clear the ring buffer
 * WARNING: This will free the memory of the ring buffer and the elements
 */
void ringBufferClear(RingBuffer buffer);

/**
 * @brief Get the head index of the ring buffer
 * @return int The head index
 */
int getRingBufferHead(RingBuffer buffer);

HEADER_END