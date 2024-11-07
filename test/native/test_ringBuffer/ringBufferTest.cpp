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
    ASSERT_EQ(getRingBufferHead(buffer), 0);
}

TEST(BufferTest, getAllElementsTest) {
    void** elements = ringBufferGetAll(buffer);
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        ASSERT_EQ(*(int*)elements[i], values[i]);
    }
}

TEST(BufferTest, getSingleElementTest) {
    ASSERT_EQ(getRingBufferHead(buffer), 0);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 0), values[0]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 1), values[1]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 2), values[2]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 3), values[3]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 4), values[4]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 5), values[5]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 6), values[6]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 7), values[7]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 8), values[8]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, 9), values[9]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -1), values[9]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -2), values[8]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -3), values[7]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -4), values[6]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -5), values[5]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -6), values[4]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -7), values[3]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -8), values[2]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -9), values[1]);
    ASSERT_EQ(*(int*)ringBufferGetElement(buffer, -10), values[0]);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}