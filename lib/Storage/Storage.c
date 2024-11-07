#include "Storage.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>

static const char* TAG_STORAGE = "Storage";

#define DIR_LS_START_SIZE 10

char** lsDir(const char* path, size_t* len) {
    struct stat entryStat;
    if (stat(path, &entryStat) != 0) {
        LOGE(TAG_STORAGE, "Failed to stat %s", path);
        return NULL;
    }

    if (S_ISDIR(entryStat.st_mode)) {
        LOGI(TAG_STORAGE, "Listing directory %s", path);
        struct dirent* dirEntry = NULL;
        DIR* dir = opendir(path);
        if (dir == NULL) {
            LOGE(TAG_STORAGE, "Failed to open directory %s", path);
            return NULL;
        }

        size_t storage_len = DIR_LS_START_SIZE;
        char** files = (char**)calloc(sizeof(char*), storage_len);
        int index = 0;
        *len = 0;

        while ((dirEntry = readdir(dir)) != NULL) {
            if (strcmp(dirEntry->d_name, ".") == 0 ||
                strcmp(dirEntry->d_name, "..") == 0) {
                continue;
            }
            files[index++] = strdup(dirEntry->d_name);
            if (index >= storage_len) {
                size_t new_len = storage_len + DIR_LS_START_SIZE;
                char** new_files =
                    (char**)realloc((void*)files, sizeof(char*) * storage_len);
                if (new_files != NULL) {
                    files = new_files;
                    storage_len = new_len;
                }
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