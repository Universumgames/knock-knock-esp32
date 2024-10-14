#include "DigitalGPIO.h"

#include <driver/gpio.h>
#include <esp_log.h>

const char* TAG_DIGITAL_GPIO = "DigitalGPIO";

void setupDigitalGPIO(gpio_num_t pin, gpio_mode_t mode) {
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = mode;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pin_bit_mask = 1ULL << pin;
    gpio_config(&io_conf);
    ESP_LOGD(TAG_DIGITAL_GPIO, "GPIO %d setup", pin);
}

void writeDigitalGPIO(gpio_num_t pin, int value) {
    gpio_set_level(pin, value);
    ESP_LOGD(TAG_DIGITAL_GPIO, "GPIO %d set to %d", pin, value);
}

int readDigitalGPIO(gpio_num_t pin) {
    return gpio_get_level(pin);
}