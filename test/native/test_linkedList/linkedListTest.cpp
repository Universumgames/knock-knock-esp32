#include <gtest/gtest.h>

#include "basicDefs.h"
#include "linkedList.h"

LinkedList list = NULL;
#define NUMBERS_SIZE 3
int numbers[] = {1, 2, 3};

TEST(LinkedList, createList) {
    list = list_create();
    EXPECT_TRUE(list != NULL);
}

TEST(LinkedList, pushBack) {
    list_push_back(list, &numbers[0]);
    list_push_back(list, &numbers[1]);
    list_push_back(list, &numbers[2]);
    EXPECT_EQ(3, list_size(list));
}

TEST(LinkedList, forEach) {
    int sum = 0;
    void* data = list_reset(list);
    while (data != NULL) {
        sum += *(int*)data;
        data = list_next(list);
    }
    int normalSum = 0;
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        normalSum += numbers[i];
    }
    EXPECT_EQ(normalSum, sum);
}

TEST(LinkedList, foreach_pramga_test) {
    int sum = 0;
    list_foreach_raw(list, int, { sum += *(int*)it; });
    int normalSum = 0;
    for (int i = 0; i < NUMBERS_SIZE; i++) {
        normalSum += numbers[i];
    }
    EXPECT_EQ(normalSum, sum);
}

TEST(LinkedList, deleteElement) {
    list_removeIndex(list, 1);
    EXPECT_EQ(2, list_size(list));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}