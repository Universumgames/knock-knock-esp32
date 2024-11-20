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

static LinkedList patternList = NULL;

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

    ret = mountFS();

    if (!ret) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to mount file system");
        return false;
    }

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

    patternList = list_create();

    loadPatternsFromDisk();

    LOGI(TAG_PATTERN_STORAGE, "Listing files in pattern storage directory");
    size_t len = 0;
    char** list = lsDir(PATTERN_STORAGE_PATH_FULL, &len);
    for (int i = 0; i < len; i++) {
        char* path = list[i];
        LOGI(TAG_PATTERN_STORAGE, "File: %s", path);
        free(path);
    };
    free(list);

    patternStorageInitialized = true;

    return ret;
}

int getNextPatternId() {
    if (!patternStorageInitialized) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return -1;
    }
    int maxId = 0;
    LOGD(TAG_PATTERN_STORAGE, "Existing patterns length: %u",
         list_size(patternList));
    list_foreach_raw(patternList, PatternData, {
        maxId = max(maxId, it->id);
        LOGD(TAG_PATTERN_STORAGE, "Pattern id: %d", it->id);
    });
    LOGD(TAG_PATTERN_STORAGE, "Max id: %d", maxId + 1);
    return maxId + 1;
}

bool storePattern(PatternData* pattern) {
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

    LOGD(TAG_PATTERN_STORAGE, "Existing patterns length: %u",
         list_size(patternList));
    int nextId = getNextPatternId();
    pattern->id = nextId;
    pattern->patternVersion = PATTERN_FILE_VERSION;

    char* path = patternFilePath(pattern->id);
    LOGI(TAG_PATTERN_STORAGE, "Pattern file path: %s", path);
    CHECK_NULL_DO(path, return NULL);
    FILE* file = fopen(path, "wbe");
    // check if file could be opened
    if (file == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to open file");
        ret = false;
        goto free_file;
    }

    size_t written =
        fwrite(&pattern->patternVersion, sizeof(pattern_ver_t), 1, file);
    written += fwrite(&pattern->id, sizeof(int), 1, file);
    written += fwrite(&pattern->totalDurationMillis, sizeof(delta_t), 1, file);
    written += fwrite(&pattern->lengthPattern, sizeof(size_t), 1, file);
    written += fwrite(pattern->deltaTimesMillis, sizeof(delta_t),
                      pattern->lengthPattern, file);

    // check if pattern was written to file
    if (written == 0) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to write pattern to file");
        ret = false;
        goto free_all;
    }

    list_push_back(patternList, pattern);
    LOGI(TAG_PATTERN_STORAGE, "Stored pattern with id %d", pattern->id);

free_all:
free_file:
    if (file != NULL)
        fclose(file);
    free(path);
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
    read += fread(&pattern->id, sizeof(int), 1, file);
    read += fread(&pattern->totalDurationMillis, sizeof(delta_t), 1, file);
    read += fread(&pattern->lengthPattern, sizeof(size_t), 1, file);
    pattern->deltaTimesMillis =
        (delta_t*)calloc(sizeof(delta_t), pattern->lengthPattern);
    if (pattern->deltaTimesMillis == NULL) {
        LOGE(TAG_PATTERN_STORAGE,
             "Failed to allocate memory for delta times (length: %u)",
             pattern->lengthPattern);
        fclose(file);
        free(pattern);
        return NULL;
    }
    read += fread(pattern->deltaTimesMillis, sizeof(delta_t),
                  pattern->lengthPattern, file);

    if (read == 0) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to read pattern from file");
        fclose(file);
        free(pattern->deltaTimesMillis);
        free(pattern);
        return NULL;
    }

    LOGI(TAG_PATTERN_STORAGE, "Loaded pattern with id %d", pattern->id);

    fclose(file);
    return pattern;
}

LinkedList loadPatternsFromDisk() {
    if (!patternStorageInitialized) {
        return patternList;
    }
    list_clear(patternList, true);
    size_t len = 0;
    char** fileNames = lsDir(PATTERN_STORAGE_PATH_FULL, &len);
    if (fileNames == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to list files in directory");
        return NULL;
    }
    if (len == 0) {
        LOGI(TAG_PATTERN_STORAGE, "No patterns found");
        return NULL;
    }
    LOGD(TAG_PATTERN_STORAGE, "Number of patterns: %u", len);
    for (size_t i = 0; i < len; i++) {
        PatternData* pattern = loadPattern(fileNames[i]);
        if (pattern != NULL) {
            list_push_back(patternList, pattern);
        }
    }
    for (size_t i = 0; i < len; i++) {
        if (fileNames[i] != NULL)
            free(fileNames[i]);
    }
    free(fileNames);
    return patternList;
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