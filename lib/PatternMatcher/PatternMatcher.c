#include "PatternMatcher.h"
#include "PatternStorage.h"
#include "PatternTypes.h"

const static char* TAG_PATTERN_MATCHER = "PatternMatcher";

#define IN_RANGE(value, min, max) ((value) >= (min) && (value) <= (max))
#define IN_RANGE_DELTA(value, target, delta)                                   \
    IN_RANGE(value, (target) - (delta), (target) + (delta))

#define DELTA_TIME_VARIANCE_MS 100

bool matchPattern(const PatternData* pattern, PatternData* matchedPattern) {
    if (pattern == NULL)
        return false;

    LinkedList patterns = getPatterns();

    list_foreach_raw(patterns, PatternData, {
        LOGD(TAG_PATTERN_MATCHER, "Checking pattern with id %lu", it->id);
        if (it->lengthPattern != pattern->lengthPattern) {
            LOGD(TAG_PATTERN_MATCHER,
                 "Pattern length did not match (pattern length iterator: %u, "
                 "pattern length matching: %u)",
                 it->lengthPattern, pattern->lengthPattern);
            goto next;
        }

        if (IN_RANGE_DELTA(it->lengthPattern, pattern->lengthPattern,
                           DELTA_TIME_VARIANCE_MS *
                               (pattern->lengthPattern / 2))) {
            LOGD(TAG_PATTERN_MATCHER,
                 "Pattern total duration did not match (pattern total duration "
                 "iterator: %d, pattern total duration matching: %d)",
                 it->totalDurationMillis, pattern->totalDurationMillis);
            goto next;
        }

        for (size_t i = 0; i < it->lengthPattern; i++) {
            if (!IN_RANGE_DELTA(it->deltaTimesMillis[i],
                                pattern->deltaTimesMillis[i],
                                DELTA_TIME_VARIANCE_MS)) {
                LOGD(TAG_PATTERN_MATCHER,
                     "Pattern delta time did not match (pattern delta time "
                     "iterator: %d, pattern delta time matching: %d)",
                     it->deltaTimesMillis[i], pattern->deltaTimesMillis[i]);
                goto next;
            }
        }

        LOGI(TAG_PATTERN_MATCHER, "Pattern matched with id %lu", it->id);

        if (matchedPattern != NULL)
            *matchedPattern = *it;
        return true;
next:
        LOGD(TAG_PATTERN_MATCHER, "Pattern did not match");
    });

    LOGD(TAG_PATTERN_MATCHER, "No pattern matched");

    return false;
}
