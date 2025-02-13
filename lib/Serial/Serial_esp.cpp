#include "Serial.h"
#include "_Serial.hpp"
#include <cstdio>
#include <cstring>
#include <list>
#include <CommandLine.h>
#include <driver/uart.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#define PATTERN_CHR_NUM                                                        \
    (2) /*!< Set the number of consecutive and identical characters received   \
    by receiver which defines a UART pattern*/

#define BUF_SIZE (1024)
#define RD_BUF_SIZE (BUF_SIZE)
static QueueHandle_t uart0_queue;

static std::queue<char> txQueue;

static const char* TAG_SERIAL = "uart_events";

[[noreturn]] static void uart_event_task(void* pvParameters) {
    uart_event_t event;
    size_t buffered_size = 0;
    auto* dtmp = static_cast<uint8_t*>(malloc(RD_BUF_SIZE));
    for (;;) {
        // Waiting for UART event.
        if (xQueueReceive(uart0_queue, &event, portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            LOGV(TAG_SERIAL, "uart[%d] event:", HW_UART_NUM);
            switch (event.type) {
                // Event of UART receiving data
                /*We'd better handler data event fast, there would be much more
                data events than other types of events. If we take too much time
                on data event, the queue might be full.*/
                case UART_DATA:
                    LOGV(TAG_SERIAL, "[UART DATA]: %d", event.size);
                    uart_read_bytes(HW_UART_NUM, dtmp, event.size,
                                    portMAX_DELAY);
                    LOGV(TAG_SERIAL, "[DATA EVT]:");
                    uart_write_bytes(HW_UART_NUM, dtmp, event.size);
                    for (int i = 0; i < event.size; i++) {
                        uartCharHandler(dtmp[i]);
                    }
                    break;
                // Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG_SERIAL, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding
                    // flow control for your application. The ISR has already
                    // reset the rx FIFO, As an example, we directly flush the
                    // rx buffer here in order to read more data.
                    uart_flush_input(HW_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                // Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG_SERIAL, "ring buffer full");
                    // If buffer full happened, you should consider increasing
                    // your buffer size As an example, we directly flush the rx
                    // buffer here in order to read more data.
                    uart_flush_input(HW_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                // Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG_SERIAL, "uart rx break");
                    break;
                // Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG_SERIAL, "uart parity error");
                    break;
                // Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG_SERIAL, "uart frame error");
                    break;
                // UART_PATTERN_DET
                case UART_PATTERN_DET: {
                    uart_get_buffered_data_len(HW_UART_NUM, &buffered_size);
                    int pos = uart_pattern_pop_pos(HW_UART_NUM);
                    ESP_LOGI(
                        TAG_SERIAL,
                        "[UART PATTERN DETECTED] pos: %d, buffered size: %d",
                        pos, buffered_size);
                    if (pos == -1) {
                        // There used to be a UART_PATTERN_DET event, but the
                        // pattern position queue is full so that it can not
                        // record the position. We should set a larger queue
                        // size. As an example, we directly flush the rx buffer
                        // here.
                        uart_flush_input(HW_UART_NUM);
                    } else {
                        uart_read_bytes(HW_UART_NUM, dtmp, pos,
                                        100 / portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_CHR_NUM + 1];
                        memset(pat, 0, sizeof(pat));
                        uart_read_bytes(HW_UART_NUM, pat, PATTERN_CHR_NUM,
                                        100 / portTICK_PERIOD_MS);
                        ESP_LOGI(TAG_SERIAL, "read data: %s", dtmp);
                        ESP_LOGI(TAG_SERIAL, "read pat : %s", pat);
                    }
                    break;
                }
                // Others
                default:
                    ESP_LOGI(TAG_SERIAL, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

void beginSerial(int baud) {
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t const uart_config = {
        .baud_rate = baud,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = {.backup_before_sleep = false},
    };
    // Install UART driver, and get the queue.
    uart_driver_install(HW_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20,
                        &uart0_queue, 0);
    uart_param_config(HW_UART_NUM, &uart_config);

    // Set UART log level
    esp_log_level_set(TAG_SERIAL, ESP_LOG_INFO);
    // Set UART pins (using UART0 default pins ie no changes.)
    uart_set_pin(HW_UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // Set uart pattern detect function.
    uart_enable_pattern_det_baud_intr(HW_UART_NUM, '/', PATTERN_CHR_NUM, 9, 0,
                                      0);
    // Reset the pattern queue length to record at most 20 pattern positions.
    uart_pattern_queue_reset(HW_UART_NUM, 20);

    serialFlush();

    // Create a task to handler UART event from ISR
    xTaskCreate(uart_event_task, "uart_event_task", 3072, NULL,
                THREAD_PRIO_SERIAL, NULL);
}