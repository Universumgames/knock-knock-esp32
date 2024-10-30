#include <gtest/gtest.h>

#include "basicDefs.h"
#include "mini.h"

TEST(MiniTest, max) {
    EXPECT_EQ(2, max(1, 2));
    EXPECT_EQ(2, max(2, 1));
    EXPECT_EQ(1, max(1, 1));
}

CPP_BEGIN int app_main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}