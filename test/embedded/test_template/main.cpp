#include <gtest/gtest.h>

#include "basicDefs.h"

TEST(TestTemplate, test1) {
    EXPECT_EQ(1, 1);
}

CPP_BEGIN int app_main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}