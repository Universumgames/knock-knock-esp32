#pragma once
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

void mountFS();
list_t* lsDir(const char* path);

#ifdef __cplusplus
}
#endif