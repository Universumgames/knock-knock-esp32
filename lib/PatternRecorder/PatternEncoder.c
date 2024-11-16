#include "PatternEncoder.h"

#include "ring_buffer.h"

#include <Storage.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 10
#define FILE_WRITE_LEN 4096
#define PATTERN_MAX_DELTA_MS 2000

static FILE* fileRaw = NULL;
static size_t fileWriteCountRaw = 0;

void saveRawToFile(analog_v rawValue) {
    fwrite(&rawValue, sizeof(analog_v), 1, fileRaw);
    fileWriteCountRaw++;
    if (fileWriteCountRaw >= FILE_WRITE_LEN) {
        fclose(fileRaw);
        LOGI("PatternEncoder", "Wrote %d values to raw file",
             fileWriteCountRaw);
    }
}

static FILE* fileAVG = NULL;
static size_t fileWriteCountAVG = 0;

void saveAVGToFile(analog_v avgValue) {
    fwrite(&avgValue, sizeof(analog_v), 1, fileAVG);
    fileWriteCountAVG++;
    if (fileWriteCountAVG >= FILE_WRITE_LEN) {
        fclose(fileAVG);
        LOGI("PatternEncoder", "Wrote %d values to avg file",
             fileWriteCountAVG);
    }
}

static FILE* fileDeltaMs = NULL;
static size_t fileWriteCountDeltaMs = 0;

void saveDeltaMsToFile(uint64_t deltaMs) {
    fwrite(&deltaMs, sizeof(uint64_t), 1, fileDeltaMs);
    fileWriteCountDeltaMs++;
    if (fileWriteCountDeltaMs >= FILE_WRITE_LEN) {
        fclose(fileDeltaMs);
        LOGI("PatternEncoder", "Wrote %d values to delta ms file",
             fileWriteCountDeltaMs);
    }
}

static FILE* fileDelta = NULL;
static size_t fileWriteCountDelta = 0;

void saveDeltaToFile(int32_t delta) {
    fwrite(&delta, sizeof(int32_t), 1, fileDelta);
    fileWriteCountDelta++;
    if (fileWriteCountDelta >= FILE_WRITE_LEN) {
        fclose(fileDelta);
        LOGI("PatternEncoder", "Wrote %d values to delta file",
             fileWriteCountDelta);
    }
}

// how much higher the value has to be compared to the avg to trigger a "knock"
#define THRESHOLD_DELTA_MULTIPLIER (1.5)

// how many values have to be read before triggering again
#define THRESHOLD_TRIGGER_TIMEOUT_VALUES (20)
// how many ms have to pass before triggering again
#define THRESHOLD_TRIGGER_TIMEOUT_MS (200)

#define PATTERN_DELTA_MILLIS_MEM_INCREMENT(oldSize) ((oldSize) + 5)

analog_v bufferAVG(analog_v** buffer, const size_t len) {
    unsigned long sum = 0;
    size_t emptyCount = 0;
    for (int i = 0; i < len; i++) {
        if (buffer[i] == NULL) {
            emptyCount++;
            continue;
        }
        sum += *buffer[i];
    };
    return (sum / (len - emptyCount));
}

static PatternData patternData = {0};
static size_t patternDataBufLen = 0;
static bool patternStarted = false;
static RingBuffer lastValues = NULL;
static RingBuffer lastTimes = NULL;
static int lastTriggeredValuesAgo = THRESHOLD_TRIGGER_TIMEOUT_VALUES;
static unsigned long lastTriggeredTimeAgo = 0;

bool initPatternEncoder() {
    if (lastValues == NULL)
        lastValues = ringBufferCreate(BUFFER_LEN, sizeof(analog_v));
    if (lastTimes == NULL)
        ringBufferCreate(BUFFER_LEN, sizeof(delta_t));
    // fill with zeros
    for (int i = 0; i < BUFFER_LEN; i++) {
        ringBufferAdd(lastValues, storeAsPtr(analog_v, 0));
        ringBufferAdd(lastTimes, storeAsPtr(delta_t, 0));
    }

    if (fileRaw == NULL) {
        fileRaw = fopen(STORAGE_MOUNT_POINT "/encoded_raw.bin", "wbe");
    }
    if (fileDeltaMs == NULL) {
        fileDeltaMs = fopen(STORAGE_MOUNT_POINT "/encoded_delta_ms.bin", "wbe");
    }
    if (fileDelta == NULL) {
        fileDelta = fopen(STORAGE_MOUNT_POINT "/encoded_delta.bin", "wbe");
    }
    if (fileAVG == NULL) {
        fileAVG = fopen(STORAGE_MOUNT_POINT "/encoded_avg.bin", "wbe");
    }
    LOGI("PatternEncoder", "raw file: %p, delta file: %p, avg file: %p",
         fileRaw, fileDeltaMs, fileAVG);

    return lastValues != NULL && lastTimes != NULL;
}

void resetEncoder() {
    lastTriggeredValuesAgo = THRESHOLD_TRIGGER_TIMEOUT_VALUES;
    lastTriggeredTimeAgo = 0;
    patternDataBufLen = 0;
    patternStarted = false;
    free(patternData.deltaTimesMillis);
    memset(&patternData, 0, sizeof(PatternData));
}

PatternData* savePatternData() {
    PatternData* ret = calloc(sizeof(PatternData), 1);
    if (ret == NULL)
        return NULL;
    memcpy(ret, &patternData, sizeof(PatternData));
    ret->deltaTimesMillis = calloc(sizeof(delta_t), patternData.lengthPattern);
    if (ret->deltaTimesMillis == NULL) {
        free(ret);
        return NULL;
    }
    memcpy(ret->deltaTimesMillis, patternData.deltaTimesMillis,
           sizeof(uint64_t) * patternData.lengthPattern);
    return ret;
}

void addPatternDataToBuf(analog_v value, delta_t deltaMs) {
    ringBufferAdd(lastValues, storeAsPtr(analog_v, value));
    lastTriggeredValuesAgo++;
    lastTriggeredTimeAgo += deltaMs;
}

// increase delta millis array if exceeding max length
void checkPatternDeltaMillisMemory() {
    if (patternData.deltaTimesMillis == NULL) {
        patternDataBufLen = PATTERN_DELTA_MILLIS_MEM_INCREMENT(0);
        patternData.deltaTimesMillis =
            calloc(sizeof(delta_t), patternDataBufLen);
    } else if (patternData.lengthPattern - 2 >= patternDataBufLen) {
        size_t size =
            PATTERN_DELTA_MILLIS_MEM_INCREMENT(patternData.lengthPattern);
        unsigned long* newDeltaMillis =
            realloc(patternData.deltaTimesMillis, sizeof(delta_t) * size);
        if (newDeltaMillis != NULL) {
            patternData.deltaTimesMillis = newDeltaMillis;
            patternDataBufLen = size;
        }
    }
}

PatternData* encodeAnalogData(analog_v value, delta_t deltaMs) {
    addPatternDataToBuf(value, deltaMs);

    analog_v avg =
        bufferAVG((analog_v**)ringBufferGetAll(lastValues), BUFFER_LEN);
    // analog_v lastValue = *(analog_v*)ringBufferGetElement(lastValues, 0);
    // int32_t delta = value - lastValue;

    /*saveRawToFile(value);
    saveDeltaMsToFile(deltaMs);
    saveAVGToFile(avg);
    saveDeltaToFile(delta);*/

    // pattern finished
    if (patternStarted && lastTriggeredTimeAgo > PATTERN_MAX_DELTA_MS) {
        goto returnPattern;
    }

    // check "timeout" for triggering
    /*if (lastTriggeredValuesAgo < THRESHOLD_TRIGGER_TIMEOUT_VALUES) {
        return NULL;
    }*/
    if (lastTriggeredTimeAgo < THRESHOLD_TRIGGER_TIMEOUT_MS) {
        return NULL;
    }

    // basic check if value is above average
    if (value < avg * THRESHOLD_DELTA_MULTIPLIER) {
        return NULL;
    }

    checkPatternDeltaMillisMemory();

    if (patternStarted)
        patternData.deltaTimesMillis[patternData.lengthPattern++] =
            lastTriggeredTimeAgo;

    lastTriggeredTimeAgo = 0;
    lastTriggeredValuesAgo = 0;
    patternStarted = true;

returnPattern:
    PatternData* ret = savePatternData();

    // TODO(tom) remove debug save file
    // storePattern(ret, NULL, 0);

    if (ret != NULL)
        resetEncoder();
    return ret;
}