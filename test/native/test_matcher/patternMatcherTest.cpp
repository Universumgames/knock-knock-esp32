#include <gtest/gtest.h>

#include "../../fff.h"
DEFINE_FFF_GLOBALS;
#include "PatternMatcher.h"
#include "PatternTypes.h"
#include "basicDefs.h"
#include "linkedList.h"

extern "C" {
FAKE_VALUE_FUNC(LinkedList, getPatterns);
}

LinkedList patternList = NULL;

#define TEST_PATTERN_CREATE(idT, duration, length, ...)                        \
    delta_t deltaTimes##idT[] = {__VA_ARGS__};                                 \
    PatternData testPattern##idT = {.patternVersion = PATTERN_FILE_VERSION,    \
                                    .id = idT,                                 \
                                    .totalDurationMillis = duration,           \
                                    .lengthPattern = length,                   \
                                    .deltaTimesMillis = deltaTimes##idT}

#define TEST_PATTERN_DEINIT(id)

TEST_PATTERN_CREATE(0, 1000, 3, 500, 500, 500);
TEST_PATTERN_CREATE(5, 3800, 6, 1000, 300, 1000, 500, 1000);

TEST(TestPatternMatcher, matchPatternTest1) {
    TEST_PATTERN_CREATE(1, 1500, 3, 500, 500, 500);
    EXPECT_TRUE(matchPattern(&testPattern1, NULL));
    TEST_PATTERN_DEINIT(1);
}

TEST(TestPatternMatcher, matchPatternTest2) {
    TEST_PATTERN_CREATE(2, 1500, 3, 520, 480, 500);
    EXPECT_TRUE(matchPattern(&testPattern2, NULL));
    TEST_PATTERN_DEINIT(2);
}

TEST(TestPatternMatcher, matchPatternTest3) {
    TEST_PATTERN_CREATE(3, 1590, 3, 530, 530, 530);
    EXPECT_TRUE(matchPattern(&testPattern3, NULL));
    TEST_PATTERN_DEINIT(3);
}

TEST(TestPatternMatcher, matchPatternTest4) {
    TEST_PATTERN_CREATE(4, 1600, 3, 580, 420, 580);
    EXPECT_TRUE(matchPattern(&testPattern4, NULL));
    TEST_PATTERN_DEINIT(4);
}

TEST(TestPatternMatcher, matchPatternTest10) {
    TEST_PATTERN_CREATE(10, 1800, 3, 800, 800, 200);
    EXPECT_FALSE(matchPattern(&testPattern10, NULL));
    TEST_PATTERN_DEINIT(10);
}

TEST(TestPatternMatcher, matchPatternTest11) {
    TEST_PATTERN_CREATE(11, 2000, 4, 500, 500, 500, 500);
    EXPECT_FALSE(matchPattern(&testPattern11, NULL));
    TEST_PATTERN_DEINIT(11);
}

TEST(TestPatternMatcher, matchPatternTest12) {
    TEST_PATTERN_CREATE(12, 1500, 5, 300, 300, 300, 300, 300);
    EXPECT_FALSE(matchPattern(&testPattern12, NULL));
    TEST_PATTERN_DEINIT(12);
}

TEST(TestPatternMatcher, matchPatternTest13) {
    TEST_PATTERN_CREATE(13, 1500, 0);
    EXPECT_FALSE(matchPattern(&testPattern13, NULL));
    TEST_PATTERN_DEINIT(13);
}

TEST(TestPatternMatcher, matchPatternTest14) {
    TEST_PATTERN_CREATE(14, 500, 1, 500);
    EXPECT_FALSE(matchPattern(&testPattern14, NULL));
    TEST_PATTERN_DEINIT(14);
}

int main() {
    patternList = list_create();
    list_push_back(patternList, storeAsPtr(PatternData, testPattern0));
    list_push_back(patternList, storeAsPtr(PatternData, testPattern5));
    getPatterns_fake.return_val = patternList;

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}