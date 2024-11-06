#include "PatternEncoder.h"

#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 10
#define FILE_WRITE_LEN 4096
#define PATTERN_MAX_DELTA_MS 2000

void saveRawToFile(int rawValue) {
    static FILE* file = NULL;
    static size_t fileWriteCount = 0;

    if (file == NULL && fileWriteCount == 0) {
        file = fopen("encoded_raw.bin", "wb");
    }
    fwrite(&rawValue, sizeof(int), 1, file);
    fileWriteCount++;
    if (fileWriteCount >= FILE_WRITE_LEN) {
        fclose(file);
        LOGI("PatternEncoder", "Wrote %d values to raw file", fileWriteCount);
    }
}

void saveAVGToFile(int avgValue) {
    static FILE* file = NULL;
    static size_t fileWriteCount = 0;

    if (file == NULL && fileWriteCount == 0) {
        file = fopen("encoded_avg.bin", "wb");
    }
    fwrite(&avgValue, sizeof(int), 1, file);
    fileWriteCount++;
    if (fileWriteCount >= FILE_WRITE_LEN) {
        fclose(file);
        LOGI("PatternEncoder", "Wrote %d values to avg file", fileWriteCount);
    }
}

void saveDeltaToFile(uint64_t deltaMs) {
    static FILE* file = NULL;
    static size_t fileWriteCount = 0;

    if (file == NULL && fileWriteCount == 0) {
        file = fopen("encoded_delta.bin", "wb");
    }
    fwrite(&deltaMs, sizeof(uint64_t), 1, file);
    fileWriteCount++;
    if (fileWriteCount >= FILE_WRITE_LEN) {
        fclose(file);
        LOGI("PatternEncoder", "Wrote %d values to delta file", fileWriteCount);
    }
}

#define BUFFER_INDEX_INC bufferIndex = (bufferIndex + 1) % BUFFER_LEN;
#define BUFFER_LAST_VALUE (lastValues[bufferIndex])
#define BUFFER_AVG_VALUE                                                       \
    ({                                                                         \
        unsigned long sum = 0;                                                 \
        for (int i = 0; i < BUFFER_LEN; i++) {                                 \
            sum += lastValues[i];                                              \
        }                                                                      \
        sum / BUFFER_LEN;                                                      \
    })
#define BUFFER_DELTA_LAST_TIME (BUFFER_LAST_VALUE - value)

#define PATTERN_DELTA_MILLIS_MEM_INCREMENT(oldSize) (oldSize + 5)

PatternData* encodeAnalogData(int value, uint64_t deltaMs) {
    static PatternData patternData = {0};
    static size_t patternDataBufLen = 0;
    static int lastValues[BUFFER_LEN] = {0};     // ringbuffer
    static uint64_t lastTimes[BUFFER_LEN] = {0}; // ringbuffer
    static int bufferIndex = 0;                  // ringbuffer index

    // increase delta millis array if exceeding max length
    if (patternData.deltaTimesMillis == NULL) {
        patternDataBufLen = PATTERN_DELTA_MILLIS_MEM_INCREMENT(0);
        patternData.deltaTimesMillis =
            calloc(sizeof(uint64_t), patternDataBufLen);
    } else if (patternData.lengthPattern - 2 >= patternDataBufLen) {
        size_t size =
            PATTERN_DELTA_MILLIS_MEM_INCREMENT(patternData.lengthPattern);
        unsigned long* newDeltaMillis =
            realloc(patternData.deltaTimesMillis, sizeof(uint64_t) * size);
        if (newDeltaMillis != NULL) {
            patternData.deltaTimesMillis = newDeltaMillis;
            patternDataBufLen = size;
        }
    }

    saveRawToFile(value);
    saveDeltaToFile(BUFFER_DELTA_LAST_TIME);
    saveAVGToFile(BUFFER_AVG_VALUE);

    // TODO add value to patternData

    BUFFER_INDEX_INC;

    if (deltaMs > PATTERN_MAX_DELTA_MS) {
        goto returnPattern;
    }

    goto notFinished;

returnPattern:
    PatternData* ret = calloc(sizeof(PatternData), 1);
    memcpy(ret, &patternData, sizeof(PatternData));
    ret->deltaTimesMillis = calloc(sizeof(uint64_t), patternData.lengthPattern);
    memcpy(ret->deltaTimesMillis, patternData.deltaTimesMillis,
           sizeof(uint64_t) * patternData.lengthPattern);

    memset(lastValues, 0, sizeof(lastValues));
    memset(lastTimes, 0, sizeof(lastTimes));
    bufferIndex = 0;
    patternDataBufLen = 0;
    free(patternData.deltaTimesMillis);
    memset(&patternData, 0, sizeof(PatternData));
    return ret;

notFinished:
    return NULL;
}