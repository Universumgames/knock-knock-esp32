#include "PatternTypes.h"
#include "basicDefs.h"

#include <stdio.h>

void logPatternData(PatternData* ret) {
    printf("ID: %d\n", ret->id);
    printf("Total duration: %d\n", ret->totalDurationMillis);
    printf("length: %d\n", ret->lengthPattern);
    printf("delta times: ");
    if (ret->deltaTimesMillis == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < ret->lengthPattern; i++) {
        printf("%d ", ret->deltaTimesMillis[i]);
    }
    printf("\n");
}