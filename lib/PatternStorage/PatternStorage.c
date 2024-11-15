#include "PatternStorage.h"

#include "Storage.h"
#include "mini.h"
#include "stringHelper.h"

#define PATTERN_STORAGE_PATH "/pattern_storage"
#define PATTERN_STORAGE_PATH_FULL STORAGE_MOUNT_POINT PATTERN_STORAGE_PATH
#define PATTERN_FILE_EXTENSION ".bin"
#define PATTERN_FILE_PREFIX "pattern_"

static const char* TAG_PATTERN_STORAGE = "PatternStorage";

static bool patternStorageInitialized = false;

#define PATTERN_STORAGE_PATH_ACCESS_MODE 0777

char* patternFileName(int patternID) {
    char* idStr = intToString(patternID, BASE_DECIMAL);
    LOGD(TAG_PATTERN_STORAGE, "Pattern id: %s", idStr);
    char* fileName =
        concat3(PATTERN_FILE_PREFIX, idStr, PATTERN_FILE_EXTENSION);
    LOGD(TAG_PATTERN_STORAGE, "Pattern file name: %s", fileName);
    return fileName;
}

char* patternFilePath(int patternID) {
    char* fileName = patternFileName(patternID);
    char* path = concat(PATTERN_STORAGE_PATH_FULL "/", fileName);
    free(fileName);
    return path;
}

bool initPatternStorage() {
    if (patternStorageInitialized) {
        return true;
    }
    bool ret = true;

    LOGI(TAG_PATTERN_STORAGE, "Initializing pattern storage at %s",
         PATTERN_STORAGE_PATH_FULL);

    if (fileExists(PATTERN_STORAGE_PATH_FULL)) {
        ret &= true;
    } else {
        int retDir =
            mkdir(PATTERN_STORAGE_PATH_FULL, PATTERN_STORAGE_PATH_ACCESS_MODE);
        LOGD(TAG_PATTERN_STORAGE, "Directory created with return code %d",
             retDir);
        ret &= retDir == 0;
        if (!ret) {
            LOGE(TAG_PATTERN_STORAGE, "Failed to create directory");
            return ret;
        }
    }

    patternStorageInitialized = true;

    return ret;
}

int getNextPatternId(const PatternData* existingPatterns,
                     const size_t existingPatternsLen) {
    if (!patternStorageInitialized) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return -1;
    }
    int maxId = 0;
    LOGD(TAG_PATTERN_STORAGE, "Existing patterns length: %u",
         existingPatternsLen);
    for (size_t i = 0; i < existingPatternsLen; i++) {
        maxId = max(maxId, existingPatterns[i].id);
        LOGD(TAG_PATTERN_STORAGE, "Pattern id: %d", existingPatterns[i].id);
    }
    LOGD(TAG_PATTERN_STORAGE, "Max id: %d", maxId + 1);
    return maxId + 1;
}

bool storePattern(PatternData* pattern, PatternData* existingPatterns,
                  const size_t existingPatternsLen) {
    bool ret = true;
    // check if pattern storage is initialized
    if (!patternStorageInitialized) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return false;
    }
    // check if pattern is NULL
    if (pattern == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern is NULL");
        return false;
    }
    PatternData* ps = existingPatterns;
    size_t len = existingPatternsLen;
    // load patterns if no existing patterns are passed
    if (existingPatterns == NULL) {
        LOGD(TAG_PATTERN_STORAGE, "No existing patterns or no passed existing "
                                  "patterns, loading patterns");
        // ps = loadPatterns(&len);
    }

    LOGD(TAG_PATTERN_STORAGE, "Existing patterns length: %u", len);
    int nextId = getNextPatternId(ps, len);
    pattern->id = nextId;
    pattern->patternVersion = PATTERN_FILE_VERSION;

    char* path = patternFilePath(pattern->id);
    LOGD(TAG_PATTERN_STORAGE, "Pattern file path: %s", path);
    CHECK_NULL_GOTO(path, free_ps);
    FILE* file = fopen(path, "wbe");
    // check if file could be opened
    if (file == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to open file");
        ret = false;
        goto free_file;
    }

    size_t written =
        fwrite(&pattern->patternVersion, sizeof(pattern_ver_t), 1, file);
    written = fwrite(&pattern->id, sizeof(int), 1, file);
    written = fwrite(&pattern->totalDurationMillis, sizeof(delta_t), 1, file);
    written = fwrite(&pattern->lengthPattern, sizeof(size_t), 1, file);
    written = fwrite(pattern->deltaTimesMillis, sizeof(delta_t),
                     pattern->lengthPattern, file);

    // check if pattern was written to file
    if (written != 1) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to write pattern to file");
        ret = false;
        goto free_all;
    }

    LOGI(TAG_PATTERN_STORAGE, "Stored pattern with id %d", pattern->id);

free_all:
free_file:
    if (file != NULL)
        fclose(file);
    free(path);
free_ps:
    if (ps != existingPatterns) {
        free(ps);
    }
    return ret;
}

PatternData* loadPattern(const char* filename) {
    char* path = concat3(PATTERN_STORAGE_PATH_FULL "/", filename, "");
    LOGD(TAG_PATTERN_STORAGE, "Loading pattern from %s", path);
    FILE* file = fopen(path, "rbe");
    free(path);
    if (file == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to open file");
        return NULL;
    }

    // read pattern version to check if file is compatible with current struct
    // encoding
    uint8_t patternVersion = 0;
    size_t read = fread(&patternVersion, sizeof(pattern_ver_t), 1, file);
    if (patternVersion != PATTERN_FILE_VERSION || read != 1) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern version mismatch");
        fclose(file);
        return NULL;
    }

    PatternData* pattern = (PatternData*)calloc(sizeof(PatternData), 1);
    if (pattern == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to allocate memory for pattern");
        fclose(file);
        return NULL;
    }

    pattern->patternVersion = patternVersion;
    read = fread(&pattern->id, sizeof(int), 1, file);
    read = fread(&pattern->totalDurationMillis, sizeof(delta_t), 1, file);
    read = fread(&pattern->lengthPattern, sizeof(size_t), 1, file);
    pattern->deltaTimesMillis =
        (unsigned long*)calloc(sizeof(delta_t), pattern->lengthPattern);
    if (pattern->deltaTimesMillis) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to allocate memory for delta times");
        fclose(file);
        free(pattern);
        return NULL;
    }
    read = fread(pattern->deltaTimesMillis, sizeof(delta_t),
                 pattern->lengthPattern, file);

    LOGI(TAG_PATTERN_STORAGE, "Loaded pattern with id %d", pattern->id);

    fclose(file);
    return pattern;
}

PatternData** loadPatterns(size_t* len) {
    if (!patternStorageInitialized) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return NULL;
    }
    char** fileNames = lsDir(PATTERN_STORAGE_PATH_FULL, len);
    if (fileNames == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to list files in directory");
        return NULL;
    }
    if (*len == 0) {
        LOGI(TAG_PATTERN_STORAGE, "No patterns found");
        return NULL;
    }
    LOGD(TAG_PATTERN_STORAGE, "Number of patterns: %u", *len);
    PatternData** patternPtrs =
        (PatternData**)calloc(sizeof(PatternData*), (*len));
    CHECK_NULL_GOTO_LOG(
        patternPtrs, free_paths,
        LOGE(TAG_PATTERN_STORAGE, "Failed to allocate memory for patterns"));

    for (size_t i = 0; i < *len; i++) {
        patternPtrs[i] = loadPattern(fileNames[i]);
        CHECK_NULL_GOTO_LOG(
            patternPtrs[i], free_patterns,
            LOGE(TAG_PATTERN_STORAGE, "Failed to load pattern"));
    }
    goto free_paths; // on success, free paths and return patterns

free_patterns:
    for (size_t i = 0; i < *len; i++) {
        if (patternPtrs[i] != NULL) {
            free(patternPtrs[i]);
        }
    }
    free(patternPtrs);
free_paths:
    for (size_t i = 0; i < *len; i++) {
        if (fileNames[i] != NULL)
            free(fileNames[i]);
    }
    free(fileNames);
    return patternPtrs;
}

bool deletePattern(int id) {
    bool ret = true;
    if (!patternStorageInitialized) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return false;
    }

    char* path = patternFilePath(id);
    CHECK_NULL_GOTO_LOG(
        path, free_path,
        LOGE(TAG_PATTERN_STORAGE, "Failed to concatenate path"));

    ret = remove(path);
    if (ret != 0) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to delete file");
        ret = false;
        goto free_path;
    }

    LOGI(TAG_PATTERN_STORAGE, "Deleted pattern with id %d", id);
free_path:
    free(path);
    return ret == 0;
}