#include "PatternEncoder.h"

#include "ring_buffer.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 10
#define FILE_WRITE_LEN 4096
#define PATTERN_MAX_DELTA_MS 2000

void saveRawToFile(int rawValue) {
    static FILE* file = NULL;
    static size_t fileWriteCount = 0;

    if (file == NULL && fileWriteCount == 0) {
        file = fopen("encoded_raw.bin", "wbe");
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
        file = fopen("encoded_avg.bin", "wbe");
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
        file = fopen("encoded_delta.bin", "wbe");
    }
    fwrite(&deltaMs, sizeof(uint64_t), 1, file);
    fileWriteCount++;
    if (fileWriteCount >= FILE_WRITE_LEN) {
        fclose(file);
        LOGI("PatternEncoder", "Wrote %d values to delta file", fileWriteCount);
    }
}

#define THRESHOLD_DELTA_MULTIPLIER                                             \
    (1.5) // how much higher the value has to be compared to the avg to trigger
          // a "knock"
#define THRESHOLD_TRIGGER_TIMEOUT_VALUES                                       \
    (20) // how many values have to be read before triggering again

#define PATTERN_DELTA_MILLIS_MEM_INCREMENT(oldSize) (oldSize + 5)

int bufferAVG(int** buffer, const size_t len) {
    unsigned long sum = 0;
    for (int i = 0; i < len; i++) {
        sum += *buffer[i];
    }
    return (sum / len);
}

PatternData* encodeAnalogData(int value, uint64_t deltaMs) {
    static PatternData patternData = {0};
    static size_t patternDataBufLen = 0;
    static RingBuffer lastValues = NULL;
    if (lastValues == NULL)
        lastValues = ringBufferCreate(BUFFER_LEN, sizeof(int));
    static RingBuffer lastTimes = NULL;
    if (lastTimes == NULL)
        ringBufferCreate(BUFFER_LEN, sizeof(uint64_t));
    static int lastTriggeredValuesAgo = THRESHOLD_TRIGGER_TIMEOUT_VALUES;

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

    int avg = bufferAVG((int**)ringBufferGetAll(lastValues), BUFFER_LEN);
    int delta = *(int*)ringBufferGetElement(lastValues, -1);

    saveRawToFile(value);
    saveDeltaToFile(delta);
    saveAVGToFile(avg);

    if (value > avg * THRESHOLD_DELTA_MULTIPLIER &&
        lastTriggeredValuesAgo > THRESHOLD_TRIGGER_TIMEOUT_VALUES) {
        // TODO add value to patternData

    } else {
        if (lastTriggeredValuesAgo < THRESHOLD_TRIGGER_TIMEOUT_VALUES * 2) {
            lastTriggeredValuesAgo++;
        }
    }

    ringBufferAdd(lastValues, storeAsPtr(int, value));

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

    patternDataBufLen = 0;
    free(patternData.deltaTimesMillis);
    memset(&patternData, 0, sizeof(PatternData));
    return ret;

notFinished:
    return NULL;
}