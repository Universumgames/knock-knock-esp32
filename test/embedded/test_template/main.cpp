#include <gtest/gtest.h>

TEST(TestTemplate, test1) {
    EXPECT_EQ(1, 1);
}

#ifdef __cplusplus
extern "C"
#endif
    int
    app_main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}