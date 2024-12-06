#include <gtest/gtest.h>

#include "../../fff.h"
#include "PatternTypes.h"
#include "basicDefs.h"
#include "linkedList.h"
#include "lock_status_t.h"
DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(LinkedList, getPatterns)
FAKE_VOID_FUNC(playPattern, PatternData*)
FAKE_VOID_FUNC(deletePattern, pattern_id_t)
FAKE_VOID_FUNC(updateLEDStatus, SchlossStatus)

#include "../../TestPattern.h"
#include "PatternManagement.h"

extern "C" size_t selectedPatternIndex;

TEST(PatternManagementTest, playPressTest) {
    _handleButtonPress(PIN_BUTTON_PLAY);
    EXPECT_EQ(playPattern_fake.call_count, 1);
}

TEST(PatternManagementTest, upPressTest) {
    EXPECT_EQ(selectedPatternIndex, 0);
    _handleButtonPress(PIN_BUTTON_UP);
    EXPECT_EQ(selectedPatternIndex, list_size(getPatterns_fake.return_val) - 1);
    selectedPatternIndex = 0;
}

TEST(PatternManagementTest, downPressTest) {
    EXPECT_EQ(selectedPatternIndex, 0);
    _handleButtonPress(PIN_BUTTON_DOWN);
    EXPECT_EQ(selectedPatternIndex, 1);
    selectedPatternIndex = 0;
}

TEST(PatternManagementTest, recordPressTest) {
    _handleButtonPress(PIN_BUTTON_RECORD);
    EXPECT_EQ(updateLEDStatus_fake.call_count, 1);
}

TEST(PatternManagementTest, deletePressTest) {
    _handleButtonPress(PIN_BUTTON_DELETE);
    EXPECT_EQ(deletePattern_fake.call_count, 1);
}

int main() {
    ::testing::InitGoogleTest();

    LinkedList patterns = createTestPatternStorage();

    getPatterns_fake.return_val = patterns;
    return RUN_ALL_TESTS();
}