#pragma once
#include <stdio.h>

#include "basicDefs.h"
#include "linkedList.h"
#include "sdkconfig.h"

#define CONFIG_REFERENCE_STORAGE_FS_SD 1
#define CONFIG_REFERENCE_STORAGE_FS_LITTLEFS 0

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_LITTLEFS
#define LOCAL_FS_MOUNT_POINT "/littlefs"
#define STORAGE_MOUNT_POINT LOCAL_FS_MOUNT_POINT
void mountLocalFS();
#elif CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_SD
#define SD_MOUNT_POINT "/sdcard"
#define STORAGE_MOUNT_POINT SD_MOUNT_POINT
void mountSDCard();
#endif

/**
 * @brief Mount the filesystem according to the configuration
 *
 */
void mountFS();

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

#ifdef __cplusplus
}
#endif