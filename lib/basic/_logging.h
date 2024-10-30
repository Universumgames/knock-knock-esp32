#pragma once
#include "_env.h"

#if ENV_IS_ESP32
#include <esp_log.h>
#define LOGE(tag, format, ...) ESP_LOGE(tag, format, ##__VA_ARGS__)
#define LOGW(tag, format, ...) ESP_LOGW(tag, format, ##__VA_ARGS__)
#define LOGI(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#define LOGD(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)
#define LOGV(tag, format, ...) ESP_LOGV(tag, format, ##__VA_ARGS__)
#elif ENV_IS_NATIVE
#include <stdio.h>
#define LOGE(tag, format, ...) printf("[Error] %s: " format "\n", tag, ##__VA_ARGS__)
#define LOGW(tag, format, ...) printf("[Warn] %s: " format "\n", tag, ##__VA_ARGS__)
#define LOGI(tag, format, ...) printf("[Info] %s: " format "\n", tag, ##__VA_ARGS__)
#define LOGD(tag, format, ...) printf("[Debug] %s: " format "\n", tag, ##__VA_ARGS__)
#define LOGV(tag, format, ...) printf("[Verbose] %s: " format "\n", tag, ##__VA_ARGS__)
#endif