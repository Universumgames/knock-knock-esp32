#include <gtest/gtest.h>

#include "basicDefs.h"
#include "ring_buffer.h"

#define BUFFER_SIZE 10

static int values[BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static RingBuffer buffer;

TEST(BufferTest, initBufferTest) {
    buffer = ringBufferCreate(BUFFER_SIZE, sizeof(int));
    ASSERT_NE(buffer, nullptr);
}

TEST(BufferTest, addElementsTest) {
    ASSERT_TRUE(ringBufferAdd(buffer, (void*)storeAsPtr(int, values[0])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[1])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[2])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[3])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[4])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[5])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[6])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[7])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[8])));
    ASSERT_TRUE(ringBufferAdd(buffer, storeAsPtr(int, values[9])));
}

TEST(BufferTest, getAllElementsTest) {
    void** elements = ringBufferGetAll(buffer);
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        ASSERT_EQ(*(int*)elements[i], values[i]);
    }
    free(elements);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}