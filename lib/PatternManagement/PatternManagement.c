#include "PatternManagement.h"
#include "PatternStorage.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "lock_status.h"
#include "pattern_play.h"

static void IRAM_ATTR gpio_isr_handler(void* arg);
static void patternManagerThread(void* arg);

QueueHandle_t queue;

/**
 * Configure button for input pin and configure interrupt
 */
void setupButton(gpio_num_t pin) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
    gpio_set_intr_type(pin, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(pin, gpio_isr_handler, (void*)&pin);
    gpio_intr_enable(pin);
}

void initPatternManagement() {
    queue = xQueueCreate(8, sizeof(gpio_num_t));
    xTaskCreate(patternManagerThread, "pattern_management_thread",
                THREAD_STACK_MANAGEMENT, NULL, THREAD_PRIO_MANAGEMENT, NULL);

    gpio_install_isr_service(0);
    setupButton((gpio_num_t)PIN_BUTTON_PLAY);
    setupButton((gpio_num_t)PIN_BUTTON_UP);
    setupButton((gpio_num_t)PIN_BUTTON_DOWN);
    setupButton((gpio_num_t)PIN_BUTTON_RECORD);
    setupButton((gpio_num_t)PIN_BUTTON_DELETE);
}

/**
 * fast interrupt handler
 */
static void IRAM_ATTR gpio_isr_handler(void* arg) {
    gpio_num_t pin = *(gpio_num_t*)arg;
    // send pin "press" (gpio_num_t) to queue
    xQueueSend(queue, (void*)pin, (TickType_t)0);
}

static size_t selectedPatternIndex = 0;

[[noreturn]]
static void patternManagerThread(void* arg) {
    gpio_num_t pin = GPIO_NUM_0;
    while (true) {
        // check if queue contains item (stored automatically in pin), if not
        // wait
        if (!xQueueReceive(queue, &pin, (TickType_t)5))
            vTaskDelay(pdMS_TO_TICKS(50));

        LinkedList patterns = getPatterns();
        size_t patternLength = list_size(patterns);

        if (pin == PIN_BUTTON_PLAY) {
            // play button was pressed
            PatternData* toPlay =
                (PatternData*)list_get(patterns, selectedPatternIndex);
            playPattern(toPlay);
        } else if (pin == PIN_BUTTON_UP) {
            // up button was pressed
            selectedPatternIndex =
                (selectedPatternIndex + patternLength - 1) % patternLength;
        } else if (pin == PIN_BUTTON_DOWN) {
            // down button was pressed
            selectedPatternIndex = (selectedPatternIndex + 1) % patternLength;
        } else if (pin == PIN_BUTTON_RECORD) {
            // record button was pressed
            updateLEDStatus(MUSTER_AUFNAHME);
        } else if (pin == PIN_BUTTON_DELETE) {
            // delete button was pressed
            PatternData* toDelete =
                (PatternData*)list_get(patterns, selectedPatternIndex);
            deletePattern(toDelete->id);
        }
    }
}
