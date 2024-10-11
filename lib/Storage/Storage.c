#include "Storage.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_system.h"

#define LOCAL_FS_LITTLEFS_PARTITION_NAME "littlefs"  // view partition table in littlefs.csv

#define PIN_NUM_MISO GPIO_NUM_12
#define PIN_NUM_MOSI GPIO_NUM_13
#define PIN_NUM_CLK GPIO_NUM_14
#define PIN_NUM_CS GPIO_NUM_15

static const char* TAG_STORAGE = "Storage";

#if CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_LITTLEFS
#include "esp_littlefs.h"

void mountLocalFS() {
    ESP_LOGI(TAG_STORAGE, "Initializing LittleFS");
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
        ESP_LOGE(TAG_STORAGE, "Failed to get LittleFS partition information (%s)", esp_err_to_name(ret));
        esp_littlefs_format(conf.partition_label);
    } else {
        ESP_LOGI(TAG_STORAGE, "Partition size: total: %d, used: %d", total, used);
    }
    ESP_LOGI(TAG_STORAGE, "LittleFS initialized and mounted");
}

#elif CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_SD
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

void mountSDCard() {
    ESP_LOGI(TAG_STORAGE, "Initializing SD card");
    esp_err_t ret;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};

    sdmmc_card_t* card;

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

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = PIN_NUM_CS;
    slot_config.host_id = host.slot;

    ESP_LOGI(TAG_STORAGE, "Mounting filesystem");
    ret = esp_vfs_fat_sdspi_mount(SD_MOUNT_POINT, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG_STORAGE, "Failed to mount filesystem. If you want the card to be formatted, set format_if_mount_failed = true.");
        } else {
            ESP_LOGE(TAG_STORAGE, "Failed to initialize the card (%s)", esp_err_to_name(ret));
        }
        return;
    }

    ESP_LOGI(TAG_STORAGE, "SD Card Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_t* card;
    ret = sdmmc_card_get_info(&host, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_STORAGE, "Failed to get SD card information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG_STORAGE, "SD Card info:");
        ESP_LOGI(TAG_STORAGE, "Name: %s", card->cid.name);
        ESP_LOGI(TAG_STORAGE, "Speed: %s", (card->csd.tr_speed > 25000000) ? "High Speed" : "Default Speed");
        ESP_LOGI(TAG_STORAGE, "Size: %d MB", card->csd.capacity / (1024 * 1024));
    }
}

#endif

void mountFS() {
#if CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_LITTLEFS
    mountLocalFS();
#elif CONFIG_STORAGE_FS_TYPE == CONFIG_REFERENCE_STORAGE_FS_SD
    mountSDCard();
#endif
}