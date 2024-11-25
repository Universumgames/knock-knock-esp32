#include "PatternMatcher.h"
#include "PatternStorage.h"
#include "PatternTypes.h"

const static char* TAG_PATTERN_MATCHER = "PatternMatcher";

#define IN_RANGE(value, min, max) ((value) >= (min) && (value) <= (max))
#define IN_RANGE_DELTA(value, target, delta)                                   \
    IN_RANGE(value, target - delta, target + delta)

#define DELTA_TIME_VARIANCE_MS 100

bool matchPattern(const PatternData* pattern, PatternData* matchedPattern) {
    if (pattern == NULL)
        return false;

    LinkedList patterns = getPatterns();

    list_foreach_raw(patterns, PatternData, {
        if (it->lengthPattern != pattern->lengthPattern)
            continue;

        if (IN_RANGE_DELTA(it->lengthPattern, pattern->lengthPattern,
                           DELTA_TIME_VARIANCE_MS *
                               (pattern->lengthPattern / 2)))
            continue;

        for (size_t i = 0; i < it->lengthPattern; i++) {
            if (!IN_RANGE_DELTA(it->deltaTimesMillis[i],
                                pattern->deltaTimesMillis[i],
                                DELTA_TIME_VARIANCE_MS))
                continue;
        }

        return true;
    });

    return false;
}
