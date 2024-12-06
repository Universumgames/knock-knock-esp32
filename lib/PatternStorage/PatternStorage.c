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

char* patternFileName(pattern_id_t patternID) {
    char* idStr = longToString(patternID, BASE_DECIMAL);
    LOGD(TAG_PATTERN_STORAGE, "Pattern id: %s", idStr);
    char* fileName =
        concat3(PATTERN_FILE_PREFIX, idStr, PATTERN_FILE_EXTENSION);
    LOGD(TAG_PATTERN_STORAGE, "Pattern file name: %s", fileName);
    return fileName;
}

char* patternFilePath(pattern_id_t patternID) {
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
        LOGI(TAG_PATTERN_STORAGE, "Directory already exists");
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

    patternStorageInitialized = true;

    return ret;
}

// #define PATTERN_NEXT_ID_USE_MAX
#define PATTERN_NEXT_ID_USE_ITERATIVE

void nextIdLoop(PatternData* it, uint32_t* useID) {
#ifdef PATTERN_NEXT_ID_USE_MAX
    *useID = max(*useID, it->id) + 1;
#elif defined(PATTERN_NEXT_ID_USE_ITERATIVE)
    if (it->id == *useID) {
        (*useID)++;
        list_reset(patternList);
    }
#endif
}

uint32_t getNextPatternId() {
    if (!patternStorageInitialized) {
        LOGE(TAG_PATTERN_STORAGE, "Pattern storage not initialized");
        return -1;
    }
    uint32_t useID = 0;
    LOGD(TAG_PATTERN_STORAGE, "Existing patterns length: %u",
         list_size(patternList));
    list_foreach_raw(patternList, PatternData, { nextIdLoop(it, &useID); });
    LOGD(TAG_PATTERN_STORAGE, "Next id: %lu", useID);
    return useID;
}

bool storePattern(PatternData* pattern) {
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

    uint32_t nextId = getNextPatternId();
    pattern->id = nextId;
    pattern->patternVersion = PATTERN_FILE_VERSION;

    char* path = patternFilePath(pattern->id);
    LOGI(TAG_PATTERN_STORAGE, "Pattern file path: %s", path);
    CHECK_NULL_DO(path, return NULL);
    FILE* file = fopen(path, "wbe");
    free(path);
    // check if file could be opened
    if (file == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to open file");
        return false;
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
        return false;
    }

    list_push_back(patternList, pattern);
    LOGI(TAG_PATTERN_STORAGE, "Stored pattern with id %lu", pattern->id);

    fclose(file);
    return true;
}

#define PATTER_LOAD_SINGLE_READ_CHECK                                          \
    if (feof(file) != 0 || ferror(file) != 0) {                                \
        LOGE(TAG_PATTERN_STORAGE, "Failed to read pattern from file");         \
        fclose(file);                                                          \
        free(pattern->deltaTimesMillis);                                       \
        free(pattern);                                                         \
        return NULL;                                                           \
    }

PatternData* loadPattern(const char* filename) {
    if (filename == NULL)
        return NULL;
    char* path = concat3(PATTERN_STORAGE_PATH_FULL "/", filename, "");
    LOGD(TAG_PATTERN_STORAGE, "Loading pattern from %s", path);
    FILE* file = fopen(path, "rbe");
    free(path);
    if (file == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to open file %s", filename);
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

    PATTER_LOAD_SINGLE_READ_CHECK;

    pattern->patternVersion = patternVersion;
    read += fread(&pattern->id, sizeof(int), 1, file);
    PATTER_LOAD_SINGLE_READ_CHECK;
    read += fread(&pattern->totalDurationMillis, sizeof(delta_t), 1, file);
    PATTER_LOAD_SINGLE_READ_CHECK;
    read += fread(&pattern->lengthPattern, sizeof(size_t), 1, file);
    PATTER_LOAD_SINGLE_READ_CHECK;
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

    PATTER_LOAD_SINGLE_READ_CHECK;

    if (read == 0) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to read pattern from file");
        fclose(file);
        free(pattern->deltaTimesMillis);
        free(pattern);
        return NULL;
    }

    LOGI(TAG_PATTERN_STORAGE, "Loaded pattern with id %lu", pattern->id);

    fclose(file);
    return pattern;
}

LinkedList loadPatternsFromDisk() {
    LOGI(TAG_PATTERN_STORAGE, "Loading patterns from disk");
    list_clear(patternList, true);
    LinkedList fileNames = lsDirLL(PATTERN_STORAGE_PATH_FULL);
    if (fileNames == NULL) {
        LOGE(TAG_PATTERN_STORAGE, "Failed to list files in directory");
        return NULL;
    }
    LOGD(TAG_PATTERN_STORAGE, "Number of patterns: %u", list_size(fileNames));
    list_foreach_raw(fileNames, char, {
        LOGI(TAG_PATTERN_STORAGE, "Loading pattern %s", it);
        PatternData* pattern = loadPattern(it);
        if (pattern != NULL) {
            list_push_back(patternList, pattern);
        }
    });
    list_clear(fileNames, true);
    list_destroy(fileNames);
    return patternList;
}

LinkedList getPatterns() {
    return patternList;
}

bool deletePattern(const pattern_id_t id) {
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

    LOGI(TAG_PATTERN_STORAGE, "Deleted pattern with id %lu", id);
free_path:
    free(path);
    return ret == 0;
}