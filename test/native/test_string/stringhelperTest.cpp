#include <gtest/gtest.h>
#include <stringHelper.h>

TEST(String, intToStringTest) {
    EXPECT_STREQ("123", intToString(123, 10));
    EXPECT_STREQ("0", intToString(0, 10));
    EXPECT_STREQ("-123", intToString(-123, 10));
    EXPECT_STREQ("7b", intToString(123, 16));
}

TEST(String, stringToIntTest) {
    EXPECT_EQ(123, stringToInt("123", 10));
    EXPECT_EQ(0, stringToInt("0", 10));
    EXPECT_EQ(-123, stringToInt("-123", 10));
    EXPECT_EQ(123, stringToInt("7b", 16));
}

TEST(String, splitStringTest) {
    int len;
    int* indices = splitString("Hello, World!", ", ", &len);
    EXPECT_EQ(2, len);
    EXPECT_EQ(0, indices[0]);
    EXPECT_EQ(5, indices[1]);
    free(indices);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}