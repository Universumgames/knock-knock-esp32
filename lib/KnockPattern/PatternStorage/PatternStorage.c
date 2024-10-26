#include "PatternStorage.h"

#include "Storage.h"
#include "stringHelper.h"

#define PATTERN_STORAGE_PATH "/pattern_storage"
#define PATTERN_STORAGE_PATH_FULL STORAGE_MOUNT_POINT PATTERN_STORAGE_PATH
#define PATTERN_FILE_EXTENSION ".bin"
#define PATTERN_FILE_PREFIX "pattern_"

static const char* TAG_PATTERN_STORAGE = "PatternStorage";

static bool patternStorageInitialized = false;

bool initPatternStorage() {
    if (patternStorageInitialized) {
        return true;
    }
    bool ret = true;

    ret &= mountFS();
    if (!ret) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to mount filesystem");
        return ret;
    }

    if (fileExists(PATTERN_STORAGE_PATH)) {
        ret &= true;
    } else {
        int retDir = mkdir(PATTERN_STORAGE_PATH_FULL, 0777);
        ret &= (retDir == 0);
        if (!ret) {
            ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to create directory");
            return ret;
        }
    }

    patternStorageInitialized = true;

    return ret;
}

int getNextPatternId(PatternData* existingPatterns, size_t existingPatternsLen) {
    if (!patternStorageInitialized) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return -1;
    }
    if (existingPatterns == NULL) {
        ESP_LOGD(TAG_PATTERN_STORAGE, "No existing patterns, loading patterns");
        existingPatterns = loadPatterns(&existingPatternsLen);
    }
    int maxId = 0;
    for (size_t i = 0; i < existingPatternsLen; i++) {
        maxId = max(maxId, existingPatterns[i].id);
    }
    return maxId + 1;
}

bool storePattern(PatternData* pattern, PatternData* existingPatterns, size_t existingPatternsLen) {
    bool ret = true;
    // check if pattern storage is initialized
    if (!patternStorageInitialized) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return false;
    }
    // check if pattern is NULL
    if (pattern == NULL) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Pattern is NULL");
        return false;
    }
    PatternData* ps = existingPatterns;
    size_t len = existingPatternsLen;
    // load patterns if no existing patterns are passed
    if (existingPatterns == NULL) {
        ESP_LOGD(TAG_PATTERN_STORAGE, "No existing patterns or no passed existing patterns, loading patterns");
        ps = loadPatterns(&len);
    }

    int nextId = getNextPatternId(ps, len);
    pattern->id = nextId;
    pattern->patternVersion = PATTERN_FILE_VERSION;
    char* idStr = intToString(nextId, 10);
    CHECK_NULL_GOTO(idStr, free_IDstr);

    char* path = concat3(PATTERN_STORAGE_PATH_FULL PATTERN_FILE_PREFIX, idStr, PATTERN_FILE_EXTENSION);
    CHECK_NULL_GOTO(path, free_IDstr);
    FILE* file = fopen(path, "wb");
    // check if file could be opened
    if (file == NULL) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to open file");
        ret = false;
        goto free_file;
    }

    size_t written = fwrite(pattern, sizeof(PatternData), 1, file);

    // check if pattern was written to file
    if (written != 1) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to write pattern to file");
        ret = false;
        goto free_all;
    }

    ESP_LOGI(TAG_PATTERN_STORAGE, "Stored pattern with id %d", nextId);

free_all:
free_file:
    if (file != NULL)
        fclose(file);
free_path:
    free(path);
free_IDstr:
    free(idStr);
free_ps:
    if (ps != existingPatterns) {
        free(ps);
    }
    return ret;
}

PatternData* loadPattern(char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to open file");
        return NULL;
    }
    PatternData* pattern = (PatternData*)calloc(sizeof(PatternData), 1);
    CHECK_NULL_GOTO_LOG(pattern, free_file, ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to allocate memory for pattern"));

    // read pattern version to check if file is compatible with current struct encoding
    uint8_t patternVersion;
    size_t read = fread(&patternVersion, sizeof(uint8_t), 1, file);
    CHECK_NULL_GOTO_LOG_DO(pattern, free_file, ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to read pattern version from file"), pattern = NULL);
    CHECK_DO(patternVersion != PATTERN_FILE_VERSION, ESP_LOGE(TAG_PATTERN_STORAGE, "Pattern version mismatch"); goto free_file);
    rewind(file);

    size_t read = fread(pattern, sizeof(PatternData), 1, file);
    CHECK_NULL_GOTO_LOG_DO(pattern, free_file, ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to read pattern from file"), pattern = NULL);

free_file:
    fclose(file);
    return pattern;
}

PatternData* loadPatterns(size_t* len) {
    PatternData* patterns = NULL;
    if (!patternStorageInitialized) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return NULL;
    }
    char** paths = lsDir(PATTERN_STORAGE_PATH_FULL, len);
    if (paths == NULL) {
        ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to list files in directory");
        return NULL;
    }
    PatternData** patternPtrs = (PatternData**)calloc(sizeof(PatternData*), *len);
    CHECK_NULL_GOTO_LOG(patterns, free_paths, ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to allocate memory for patterns"));

    for (size_t i = 0; i < *len; i++) {
        patternPtrs[i] = loadPattern(paths[i]);
        CHECK_DO(patternPtrs[i] == NULL, ESP_LOGE(TAG_PATTERN_STORAGE, "Failed to load pattern"));
    }
    goto free_paths;  // on success, free paths and return patterns

free_patterns:
    for (size_t i = 0; i < *len; i++) {
        if (patternPtrs[i] != NULL) {
            free(patternPtrs[i]);
        }
    }
    free(patternPtrs);
free_paths:
    for (size_t i = 0; i < *len; i++) {
        free(paths[i]);
    }
    free(paths);

    return patterns;
}