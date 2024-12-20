#include <gtest/gtest.h>
#include <stringHelper.h>

TEST(String, intToStringTest) {
    EXPECT_STREQ("123", intToString(123, BASE_DECIMAL));
    EXPECT_STREQ("0", intToString(0, BASE_DECIMAL));
    EXPECT_STREQ("-123", intToString(-123, BASE_DECIMAL));
    EXPECT_STREQ("7b", intToString(123, BASE_HEXADECIMAL));
}

TEST(String, stringToIntTest) {
    EXPECT_EQ(123, stringToInt("123", BASE_DECIMAL));
    EXPECT_EQ(0, stringToInt("0", BASE_DECIMAL));
    EXPECT_EQ(-123, stringToInt("-123", BASE_DECIMAL));
    EXPECT_EQ(123, stringToInt("7b", BASE_HEXADECIMAL));
}

TEST(String, splitStringTest) {
    size_t len;
    char str[] = "Hello, World!";
    size_t* indices = splitString(str, ", ", &len);
    EXPECT_EQ(2, len);
    EXPECT_EQ(0, indices[0]);
    EXPECT_EQ(5, indices[1]);
    free(indices);
    indices = splitString(str, "?", &len);
    EXPECT_EQ(1, len);
    EXPECT_EQ(strlen(str), indices[0]);
}

TEST(String, substringTest) {
    EXPECT_STREQ("Hello", substring("Hello, World!", 0, 4));
    EXPECT_STREQ("World", substring("Hello, World!", 7, 11));
}

TEST(String, concatTest) {
    EXPECT_STREQ("Hello, World!", concat("Hello, ", "World!"));
}

TEST(String, concat3Test) {
    EXPECT_STREQ("Hello, World!", concat3("Hello, ", "World", "!"));
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}