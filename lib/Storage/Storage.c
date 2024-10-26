#include "Storage.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>

static const char* TAG_STORAGE = "Storage";

char** lsDir(const char* path, size_t* len) {
    struct stat st;
    if (stat(path, &st) != 0) {
        LOGE(TAG_STORAGE, "Failed to stat %s", path);
        return NULL;
    }

    if (S_ISDIR(st.st_mode)) {
        LOGI(TAG_STORAGE, "Listing directory %s", path);
        struct dirent* de;
        DIR* dir = opendir(path);
        if (dir == NULL) {
            LOGE(TAG_STORAGE, "Failed to open directory %s", path);
            return NULL;
        }

        size_t storage_len = 10;
        char** files = (char**)calloc(sizeof(char*), storage_len);
        int index = 0;
        *len = 0;

        while ((de = readdir(dir)) != NULL) {
            files[index++] = strdup(de->d_name);
            if (index >= storage_len) {
                storage_len *= 2;
                files = (char**)realloc(files, sizeof(char*) * storage_len);
            }
        }
        closedir(dir);
        *len = index;
        return files;
    } else {
        LOGE(TAG_STORAGE, "%s is not a directory", path);
        return NULL;
    }
}

bool fileExists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}