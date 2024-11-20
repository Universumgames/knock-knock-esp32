#include <driver/gpio.h>
#include <esp_err.h>
#include <esp_system.h>

#include "Storage.h"

#define LOCAL_FS_LITTLEFS_PARTITION_NAME                                       \
    "littlefs" // view partition table in littlefs.csv

#define PIN_NUM_MISO GPIO_NUM_5
#define PIN_NUM_MOSI GPIO_NUM_6
#define PIN_NUM_CLK GPIO_NUM_4
#define PIN_NUM_CS GPIO_NUM_7

static const char* TAG_STORAGE = "Storage";

static bool storageInitialized = false;

#if CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_LITTLEFS
#include "esp_littlefs.h"

bool mountLocalFS() {
    LOGI(TAG_STORAGE, "Initializing LittleFS");
    esp_vfs_littlefs_conf_t conf = {
        .base_path = LOCAL_FS_MOUNT_POINT,
        .partition_label = LOCAL_FS_LITTLEFS_PARTITION_NAME,
        .format_if_mount_failed = true,
        .dont_mount = false,
    };

    esp_err_t ret = esp_vfs_littlefs_register(&conf);

    size_t total = 0, used = 0;
    ret = esp_littlefs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK) {
        LOGE(TAG_STORAGE, "Failed to get LittleFS partition information (%s)",
             esp_err_to_name(ret));
        esp_littlefs_format(conf.partition_label);
    } else {
        LOGI(TAG_STORAGE, "Partition size: total: %d, used: %d", total, used);
    }
    LOGI(TAG_STORAGE, "LittleFS initialized and mounted");
    return true;
}

#elif CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_SD
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

bool mountSDCard() {
    LOGI(TAG_STORAGE, "Initializing SD card");
    esp_err_t ret;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 10,
        .allocation_unit_size = 16 * 1024};

    sdmmc_card_t* card;

    LOGI(TAG_STORAGE, "Using SPI peripheral");

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    ret = spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK) {
        LOGE(TAG_STORAGE, "Failed to initialize bus.");
        return false;
    }

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    LOGI(TAG_STORAGE, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(SD_MOUNT_POINT, &host, &slot_config,
                                  &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            LOGE(TAG_STORAGE,
                 "Failed to mount filesystem. If you want the card to be "
                 "formatted, set format_if_mount_failed = true.");
        } else {
            LOGE(TAG_STORAGE, "Failed to initialize the card (%s)",
                 esp_err_to_name(ret));
        }
        return false;
    }

    LOGI(TAG_STORAGE, "SD Card Filesystem mounted");

    sdmmc_card_print_info(stdout, card);
    return true;
}

#endif

bool mountFS() {
    if (storageInitialized)
        return true;
    bool ret = false;
#if CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_LITTLEFS
    ret = mountLocalFS();
#elif CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_SD
    ret = mountSDCard();
#endif
    storageInitialized = ret;
    return ret;
}
