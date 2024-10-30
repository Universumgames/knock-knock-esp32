#include <gtest/gtest.h>

#include "basicDefs.h"

TEST(TestTemplate, test1) {
    EXPECT_EQ(1, 1);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}