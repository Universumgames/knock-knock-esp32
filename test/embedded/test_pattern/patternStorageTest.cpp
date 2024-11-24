#include <gtest/gtest.h>

#include "PatternStorage.h"
#include "basicDefs.h"

static PatternData s_pattern = {
    .patternVersion = PATTERN_FILE_VERSION,
    .id = 1,
    .totalDurationMillis = 1000,
    .lengthPattern = 3,
    .deltaTimesMillis = (delta_t[]){100, 200, 300},
};

TEST(PatternStorageTests, storePatternTest) {
    printf("storePatternTest\n");

    bool ret = storePattern(NULL);
    EXPECT_TRUE(true);
}

TEST(PatternStorageTests, loadPatternsTest) {
    LinkedList patterns = loadPatternsFromDisk();
    size_t len = list_size(patterns);
    PatternData* firstPattern = list_get(patterns, 0);
    EXPECT_TRUE(patterns != NULL);
    EXPECT_EQ(1, len);
    EXPECT_EQ(s_pattern.patternVersion, firstPattern->patternVersion);
    EXPECT_EQ(s_pattern.id, firstPattern->id);
    EXPECT_EQ(s_pattern.totalDurationMillis, firstPattern->totalDurationMillis);
    EXPECT_EQ(s_pattern.lengthPattern, firstPattern->lengthPattern);
    for (size_t i = 0; i < s_pattern.lengthPattern; i++) {
        EXPECT_EQ(s_pattern.deltaTimesMillis[i],
                  firstPattern->deltaTimesMillis[i]);
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