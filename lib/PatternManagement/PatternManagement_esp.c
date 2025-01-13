#include "PatternManagement.h"
#include "PatternStorage.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

static void patternManagerThread(void* arg);

QueueHandle_t queue;

/**
 * fast interrupt handler
 */
static void IRAM_ATTR gpio_isr_handler(void* arg) {
    gpio_num_t pin = *(gpio_num_t*)arg;
    // send pin "press" (gpio_num_t) to queue
    xQueueSendFromISR(queue, &pin, (TickType_t)0);
}

/**
 * Configure button for input pin and configure interrupt
 */
void setupButton(gpio_num_t pin) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
    gpio_set_intr_type(pin, GPIO_INTR_POSEDGE);
    gpio_num_t* arg = malloc(sizeof(gpio_num_t));
    *arg = pin;
    gpio_isr_handler_add(pin, gpio_isr_handler, (void*)arg);
    gpio_intr_enable(pin);
}

void initPatternManagement() {
    queue = xQueueCreate(8, sizeof(gpio_num_t));
    xTaskCreate(patternManagerThread, "pattern_management_thread",
                THREAD_STACK_MANAGEMENT, NULL, THREAD_PRIO_MANAGEMENT, NULL);

    gpio_install_isr_service(0);
    // setupButton((gpio_num_t)PIN_BUTTON_PLAY);
    setupButton((gpio_num_t)PIN_BUTTON_UP);
    setupButton((gpio_num_t)PIN_BUTTON_DOWN);
    setupButton((gpio_num_t)PIN_BUTTON_RECORD);
    setupButton((gpio_num_t)PIN_BUTTON_DELETE);
}

[[noreturn]]
static void patternManagerThread(void* arg) {
    gpio_num_t pin = GPIO_NUM_0;
    while (true) {
        // check if queue contains item (stored automatically in pin), if not
        // wait
        if (!xQueueReceive(queue, &pin, (TickType_t)5))
            vTaskDelay(pdMS_TO_TICKS(50));
        else
            _handleButtonPress(pin);
    }
}
