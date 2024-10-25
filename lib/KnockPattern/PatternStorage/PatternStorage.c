#include "PatternStorage.h"

#include "Storage.h"

#define PATTERN_STORAGE_PATH "/pattern_storage"
#define PATTERN_STORAGE_PATH_FULL STORAGE_MOUNT_POINT PATTERN_STORAGE_PATH

static const char* TAG_PATTERN_STORAGE = "PatternStorage";

bool initPatternStorage() {
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

    return ret;
}

bool storePattern(PatternData* pattern) {
    ESP_LOGE(TAG_PATTERN_STORAGE, "storePattern not implemented");
    return true;
}

PatternData* loadPatterns(size_t* len) {
    ESP_LOGE(TAG_PATTERN_STORAGE, "loadPatterns not implemented");
    return NULL;
}