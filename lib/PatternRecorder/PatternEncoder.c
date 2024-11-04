#include "PatternEncoder.h"

#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 10
#define FILE_WRITE_LEN 4096

static FILE* file = NULL;
static size_t fileWriteCount = 0;

void saveEncodingToFile(int value) {
    if (file == NULL && fileWriteCount == 0) {
        file = fopen("encoded.bin", "wb");
    }
    fwrite(&value, sizeof(int), 1, file);
    fileWriteCount++;
    if (fileWriteCount >= FILE_WRITE_LEN) {
        fclose(file);
    }
}

PatternData* encodeAnalogData(int value, uint64_t deltaMs) {
    static PatternData patternData = {0};
    static int lastValues[BUFFER_LEN] = {0};
    static uint64_t lastTimes[BUFFER_LEN] = {0};

returnPattern:
    PatternData* ret = calloc(sizeof(PatternData), 1);
    memcpy(ret, &patternData, sizeof(PatternData));

resetCache:
    patternData = {0};
    lastValues = {0};
    lastTimes = {0};

notFinished:
    return NULL;
}