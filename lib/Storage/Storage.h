#pragma once
#include <esp_vfs_fat.h>
#include <stdio.h>
#include <sys/stat.h>

#include "basicDefs.h"
#include "linkedList.h"
#include "sdkconfig.h"

#define CONFIG_REFERENCE_STORAGE_FS_SD 1
#define CONFIG_REFERENCE_STORAGE_FS_LITTLEFS 0

HEADER_BEGIN

#if CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_LITTLEFS
#define LOCAL_FS_MOUNT_POINT "/littlefs"
#define STORAGE_MOUNT_POINT LOCAL_FS_MOUNT_POINT
bool mountLocalFS();
#elif CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_SD
#define SD_MOUNT_POINT "/sdcard"
#define STORAGE_MOUNT_POINT SD_MOUNT_POINT
bool mountSDCard();
#endif

/**
 * @brief Mount the filesystem according to the configuration
 * @return true if the filesystem was mounted successfully
 */
bool mountFS();

/**
 * @brief List the filenames in a directory
 * WARNING: This function allocates memory for the filenames, make sure to free it after usage
 *
 * @param path the path to the directory
 * @param len the length of the returned array
 * @return char** the filenames in the directory
 */
char** lsDir(const char* path, size_t* len);

bool fileExists(const char* path);

// fopen(path, mode)
// fclose(file)
// fprintf(file, content)
// fgets(buffer, size, file) // read line until \n, NULL if EOF
// rename(oldpath, newpath) // rename file, returns 0 on success
// unlink(path) // delete file, returns 0 on success

HEADER_END