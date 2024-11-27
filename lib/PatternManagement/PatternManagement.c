#include "PatternManagement.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static void IRAM_ATTR gpio_isr_handler(void* arg);

void setupButton(gpio_num_t pin) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
    gpio_set_intr_type(pin, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(pin, gpio_isr_handler, (void*)&pin);
    gpio_intr_enable(pin);
}

void initPatternManagement() {
    setupButton((gpio_num_t)PIN_BUTTON_PLAY);
    //...
}

static void IRAM_ATTR gpio_isr_handler(void* arg) {
    gpio_num_t pin = *(gpio_num_t*)arg;
    // Do something, keep it short, work with queues and a separate while(true)
    // task if needed or create a new task here
}