#include <driver/gpio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#include "AnalogRead.h"
#include "HardwareLED.h"
#include "Serial.h"
#include "Storage.h"
#include "lock_open.h"
#include "stringHelper.h"

#define ECHO_TASK_STACK_SIZE 2048

#define LED_BRIGHTNESS 10  // 0-255
#define LED_FADE_DELAY 10

static void fade(void* pvParameters) {
    while (1) {
        for (int g = 0; g < LED_BRIGHTNESS; g++) {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int g = LED_BRIGHTNESS; g > 0; g--) {
            writeHWLED(0, g, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int r = 0; r < LED_BRIGHTNESS; r++) {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int r = LED_BRIGHTNESS; r > 0; r--) {
            writeHWLED(r, 0, 0);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int b = 0; b < LED_BRIGHTNESS; b++) {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
        for (int b = LED_BRIGHTNESS; b > 0; b--) {
            writeHWLED(0, 0, b);
            showHWLED();
            vTaskDelay(LED_FADE_DELAY / portTICK_PERIOD_MS);
        }
    }
}

static TaskHandle_t s_task_handle;

static bool IRAM_ATTR s_conv_done_cb(adc_continuous_handle_t handle, const adc_continuous_evt_data_t* edata, void* user_data) {
    BaseType_t mustYield = pdFALSE;
    // Notify that ADC continuous driver has done enough number of conversions
    vTaskNotifyGiveFromISR(s_task_handle, &mustYield);

    return (mustYield == pdTRUE);
}

static void analogReadTask(void* pvParameters) {
    uint8_t value[256] = {0};
    adc_continuous_handle_t handle;
    adc_channel_t channels[] = {ADC_CHANNEL_0};
    bool ret = continuous_init(channels, 1, ADC_ATTEN_DB_0, &handle);
    if (!ret) {
        ESP_LOGE("main", "Failed to initialize continuous ADC");
        vTaskDelete(NULL);
    }

    s_task_handle = xTaskGetCurrentTaskHandle();

    adc_continuous_evt_cbs_t cbs = {
        //.on_conv_done = s_conv_done_cb,
    };
    ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(handle, &cbs, NULL));

    ESP_ERROR_CHECK(adc_continuous_start(handle));
    vTaskDelete(NULL);
    ESP_LOGI("main", "ADC continuous started");

    while (1) {
        read_continuous(handle, value, 256);
        ESP_LOGI("main", "Analog value: %d", value[0]);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

#ifdef __cplusplus
extern "C"
#endif

    void
    app_main() {
    esp_log_level_set("*", ESP_LOG_VERBOSE);
    esp_log_level_set("main", ESP_LOG_VERBOSE);
    beginSerial(115200);
    initHardwareLED();

    ESP_LOGV("main", "Log test verbose");
    ESP_LOGD("main", "Log test debug");
    ESP_LOGI("main", "Log test info");
    ESP_LOGW("main", "Log test warn");
    ESP_LOGE("main", "Log test error");

    xTaskCreate(fade, "lsd_led_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);
    xTaskCreate(analogReadTask, "analog_read_task", ECHO_TASK_STACK_SIZE * 2, NULL, 5, NULL);

    mountFS();
    size_t len;
    char** list = lsDir(STORAGE_MOUNT_POINT, &len);
    for (int i = 0; i < len; i++) {
        char* path = list[i];
        ESP_LOGI("main", "File: %s", path);
        free(path);
    };
    free(list);

    openLock();
}
