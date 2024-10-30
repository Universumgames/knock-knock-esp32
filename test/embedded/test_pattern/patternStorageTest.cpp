#include <gtest/gtest.h>

#include "PatternStorage.h"
#include "basicDefs.h"

PatternData s_pattern = {
    .patternVersion = PATTERN_FILE_VERSION,
    .id = 1,
    .totalDurationMillis = 1000,
    .lengthPattern = 3,
    .deltaTimesMillis = (unsigned long[]){100, 200, 300},
};

TEST(PatternStorageTests, storePatternTest) {
    printf("storePatternTest\n");

    bool ret = storePattern(&s_pattern, nullptr, 0);
    EXPECT_TRUE(true);
}

TEST(PatternStorageTests, loadPatternsTest) {
    size_t len = 0;
    PatternData** patterns = loadPatterns(&len);
    EXPECT_TRUE(patterns != NULL);
    EXPECT_EQ(1, len);
    EXPECT_EQ(s_pattern.patternVersion, patterns[0]->patternVersion);
    EXPECT_EQ(s_pattern.id, patterns[0]->id);
    EXPECT_EQ(s_pattern.totalDurationMillis, patterns[0]->totalDurationMillis);
    EXPECT_EQ(s_pattern.lengthPattern, patterns[0]->lengthPattern);
    for (size_t i = 0; i < s_pattern.lengthPattern; i++) {
        EXPECT_EQ(s_pattern.deltaTimesMillis[i], patterns[0]->deltaTimesMillis[i]);
    }
    free(patterns);
}

TEST(PatternStorageTests, deletePatternTest) {
    bool ret = deletePattern(s_pattern.id);
    EXPECT_TRUE(ret);
}

CPP_BEGIN int app_main() {
    initPatternStorage();
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}