#include <gtest/gtest.h>

#include "basicDefs.h"
#include "mini.h"

TEST(MiniTest, maxTest) {
    EXPECT_EQ(2, max(1, 2));
    EXPECT_EQ(2, max(2, 1));
    EXPECT_EQ(1, max(1, 1));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}