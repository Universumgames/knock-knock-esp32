#include "PatternEncoder.h"

#include "PatternStorage.h"
#include "Storage.h"
#include "ring_buffer.h"

#include <mini.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RING_BUFFER_LEN 10
#define PATTERN_MAX_DELTA_MS 2000

/// feature flags
// #define PATTERN_STORE_RAW_RECORDING
#define PATTERN_STORE_PATTERN_RECORDING

#ifdef PATTERN_STORE_RAW_RECORDING
#define FILE_WRITE_LEN 4096

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
#endif

// how many ms have to pass before triggering again
#define THRESHOLD_TRIGGER_TIMEOUT_MS (200)
#define THRESHOLD_DELTA_MILLIS_WARNING (40)

// how much higher the value has to be compared to the avg to trigger a "knock"
#define THRESHOLD_TRIGGER_VALUE ((avg * 2) + 200)

#define PATTERN_DELTA_MILLIS_MEM_INCREMENT(oldSize) ((oldSize) + 10)

const static char* TAG_PATTERN_ENCODER = "PatternEncoder";

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
static delta_t lastTriggeredTimeAgo = 0;

bool initPatternEncoder() {
    if (lastValues == NULL)
        lastValues = ringBufferCreate(RING_BUFFER_LEN, sizeof(analog_v));
    if (lastTimes == NULL)
        lastTimes = ringBufferCreate(RING_BUFFER_LEN, sizeof(delta_t));
    // fill with zeros
    for (int i = 0; i < RING_BUFFER_LEN; i++) {
        ringBufferAdd(lastValues, storeAsPtr(analog_v, 0));
        ringBufferAdd(lastTimes, storeAsPtr(delta_t, 0));
    }

#ifdef PATTERN_STORE_RAW_RECORDING
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
#endif

    return lastValues != NULL && lastTimes != NULL;
}

void resetPatternEncoder() {
    lastTriggeredTimeAgo = 0;
    patternDataBufLen = 0;
    patternStarted = false;
    if (patternData.deltaTimesMillis != NULL)
        free(patternData.deltaTimesMillis);
    patternData.id = 0;
    patternData.lengthPattern = 0;
    patternData.totalDurationMillis = 0;
    patternData.deltaTimesMillis = NULL;
}

PatternData* savePatternData() {
    PatternData* ret = calloc(sizeof(PatternData), 1);
    if (ret == NULL) {
        return NULL;
    }
    memcpy(ret, &patternData, sizeof(PatternData));
    ret->deltaTimesMillis = calloc(sizeof(delta_t), patternData.lengthPattern);
    if (ret->deltaTimesMillis == NULL) {
        free(ret);
        return NULL;
    }
    memcpy(ret->deltaTimesMillis, patternData.deltaTimesMillis,
           sizeof(delta_t) * patternData.lengthPattern);
    return ret;
}

void addPatternDataToBuf(analog_v value, delta_t deltaMs) {
    ringBufferAdd(lastValues, storeAsPtr(analog_v, value));
    lastTriggeredTimeAgo += deltaMs;
    if (deltaMs >= THRESHOLD_DELTA_MILLIS_WARNING) {
        LOGW(TAG_PATTERN_ENCODER,
             "Delta time warning: %u ms (should be less than %u)", deltaMs,
             THRESHOLD_DELTA_MILLIS_WARNING);
    }
}

// increase delta millis array if exceeding max length
void checkPatternDeltaMillisMemory() {
    if (patternDataBufLen == 0 ||
        patternData.lengthPattern + 2 >= patternDataBufLen) {
        LOGI(TAG_PATTERN_ENCODER, "size of pattern %u",
             patternData.lengthPattern);
        size_t newSize =
            PATTERN_DELTA_MILLIS_MEM_INCREMENT(patternData.lengthPattern);
        delta_t* newDeltaMillis = patternData.deltaTimesMillis == NULL
                                      ? calloc(sizeof(delta_t), newSize)
                                      : realloc(patternData.deltaTimesMillis,
                                                sizeof(delta_t) * newSize);
        if (newDeltaMillis != NULL) {
            patternData.deltaTimesMillis = newDeltaMillis;
            patternDataBufLen = newSize;
        } else {
            LOGE("encoder", "Failed to allocate memory for delta millis");
        }
    }
}

PatternData* encodeAnalogData(analog_v value, delta_t deltaMs) {
    addPatternDataToBuf(value, deltaMs);

    analog_v avg =
        bufferAVG((analog_v**)ringBufferGetAll(lastValues), RING_BUFFER_LEN);
#ifdef PATTERN_STORE_RAW_RECORDING
    analog_v lastValue = *(analog_v*)ringBufferGetElement(lastValues, 0);
    int32_t delta = value - lastValue;

    saveRawToFile(value);
    saveDeltaMsToFile(deltaMs);
    saveAVGToFile(avg);
    saveDeltaToFile(delta);
#endif

    // pattern finished
    if (patternStarted && lastTriggeredTimeAgo > PATTERN_MAX_DELTA_MS) {
        if (dflag_pattern_encoder_printf_if_branches)
            printf(".");
        if (patternData.lengthPattern == 0) {
            resetPatternEncoder();
            lastTriggeredTimeAgo = THRESHOLD_TRIGGER_TIMEOUT_MS;
            return NULL;
        }
        goto returnPattern;
    }

    // check "timeout" for triggering
    if (lastTriggeredTimeAgo < THRESHOLD_TRIGGER_TIMEOUT_MS) {
        if (dflag_pattern_encoder_printf_if_branches)
            printf(",");
        return NULL;
    }

    // basic check if value is above average
    if (value < THRESHOLD_TRIGGER_VALUE) {
        if (dflag_pattern_encoder_printf_if_branches)
            printf("*");
        return NULL;
    }

    if (dflag_pattern_encoder_printf_if_branches)
        printf("!");

    checkPatternDeltaMillisMemory();

    if (patternStarted) {
        patternData.deltaTimesMillis[patternData.lengthPattern++] =
            lastTriggeredTimeAgo;
        patternData.totalDurationMillis += lastTriggeredTimeAgo;
    }

    lastTriggeredTimeAgo = 0;
    patternStarted = true;
    return NULL;

returnPattern:
    LOGI(TAG_PATTERN_ENCODER, "Pattern finished, saving pattern in buffer");
    PatternData* ret = savePatternData();
    LOGI(TAG_PATTERN_ENCODER, "Pattern data");
    if (dflag_pattern_encoder_log_all)
        logPatternDataConcise(ret);

    if (dflag_pattern_store_recorded_pattern) {
        LOGI(TAG_PATTERN_ENCODER, "Pattern finished, saving pattern in file");
        bool saved = storePattern(savePatternData());
        if (!saved) {
            LOGE(TAG_PATTERN_ENCODER, "Failed to save pattern");
            logPatternData(ret);
        }
    }

    resetPatternEncoder();
    return ret;
}