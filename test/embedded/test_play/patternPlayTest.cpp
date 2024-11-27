#include <gtest/gtest.h>

#include "PatternTypes.h"
#include "basicDefs.h"
#include "pattern_play.h"

#define TEST_PATTERN_CREATE(idT, duration, length, ...)                        \
    delta_t deltaTimes##idT[] = {__VA_ARGS__};                                 \
    PatternData testPattern##idT = {.patternVersion = PATTERN_FILE_VERSION,    \
                                    .id = idT,                                 \
                                    .totalDurationMillis = duration,           \
                                    .lengthPattern = length,                   \
                                    .deltaTimesMillis = deltaTimes##idT}

#define TEST_PATTERN_DEINIT(id)

TEST(PatternPlayTest, playPattern1Test) {
    TEST_PATTERN_CREATE(1, 1000, 3, 100, 200, 300);
    EXPECT_TRUE(playPattern(&testPattern1));
    TEST_PATTERN_DEINIT(1);
}

TEST(PatternPlayTest, playPattern2Test) {
    TEST_PATTERN_CREATE(2, 2500, 5, 500, 500, 500, 500, 500);
    EXPECT_TRUE(playPattern(&testPattern2));
    TEST_PATTERN_DEINIT(2);
}

TEST(PatternPlayTest, playPattern3Test) {
    TEST_PATTERN_CREATE(3, 100, 3, 50, 20, 20, 10);
    EXPECT_TRUE(playPattern(&testPattern3));
    TEST_PATTERN_DEINIT(3);
}

TEST(PatternPlayTest, playNULLTest) {
    EXPECT_FALSE(playPattern(nullptr));
}

TEST(PatternPlayTest, playEmptyPatternTest) {
    TEST_PATTERN_CREATE(4, 0, 0);
    EXPECT_FALSE(playPattern(&testPattern4));
    TEST_PATTERN_DEINIT(4);
}

TEST(PatternPlayTest, playNULLMillisTest) {
    PatternData testPattern5 = {.patternVersion = PATTERN_FILE_VERSION,
                                .id = 5,
                                .totalDurationMillis = 1000,
                                .lengthPattern = 3,
                                .deltaTimesMillis = nullptr};
    EXPECT_FALSE(playPattern(&testPattern5));
    TEST_PATTERN_DEINIT(5);
}

CPP_BEGIN int app_main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}