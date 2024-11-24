#include <gtest/gtest.h>

#include "basicDefs.h"
#include "mini.h"

TEST(MiniTest, max) {
    EXPECT_EQ(2, max(1, 2));
    EXPECT_EQ(2200, max(2200, 445));
    EXPECT_EQ(768, max(768, 23));
}

TEST(MiniTest, min) {
    EXPECT_EQ(1, min(1, 2));
    EXPECT_EQ(445, min(2200, 445));
    EXPECT_EQ(23, min(768, 23));
}

CPP_BEGIN int app_main() {
    void* scrambler = calloc(sizeof(int), 3);
    int i = 8;
    int* ptr = (int*)scrambler;
    *ptr = i;
    free(scrambler);
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}