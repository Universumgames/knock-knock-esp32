#include "FastLed.h"

#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <hal/spi_hal.h>
#include <string.h>

const char* TAG_FAST_LED = "FastLED";

#define WS2812_SPI_SPEED_HZ (2400 * 1000)
#define WS2812_LED_BUF (9)
#define WS2812_LED_BUF_BIT (WS2812_LED_BUF * 8)

/**
 * @brief write data to spi
 *
 * @param spi_handle the spi handle
 * @param buf the buffer to write
 * @param size the size of the buffer
 * @return esp_err_t error code
 */
esp_err_t _write(spi_device_handle_t spi_handle, uint8_t* buf, size_t size) {
    spi_transaction_t t = {0};

    t.length = size;
    t.tx_buffer = buf;
    t.rx_buffer = NULL;

    return spi_device_transmit(spi_handle, &t);
}

/**
 * @brief Clever way to encode the WS2812 protocol into SPI bits
 * (for example calculation see documentation/assets/ws2812_spi_bit_encode.jpeg)
 *
 * @param data the byte to encode
 * @param buf the buffer to write the encoded data to
 */
void set_data_bit(uint8_t data, uint8_t* buf) {
    *(buf + 2) |= data & BIT(0) ? BIT(2) | BIT(1) : BIT(2);
    *(buf + 2) |= data & BIT(1) ? BIT(5) | BIT(4) : BIT(5);
    *(buf + 2) |= data & BIT(2) ? BIT(7) : 0x00;
    *(buf + 1) |= data & BIT(2) ? BIT(0) : BIT(0);
    *(buf + 1) |= data & BIT(3) ? BIT(3) | BIT(2) : BIT(3);
    *(buf + 1) |= data & BIT(4) ? BIT(6) | BIT(5) : BIT(6);
    *(buf + 0) |= data & BIT(5) ? BIT(1) | BIT(0) : BIT(1);
    *(buf + 0) |= data & BIT(6) ? BIT(4) | BIT(3) : BIT(4);
    *(buf + 0) |= data & BIT(7) ? BIT(7) | BIT(6) : BIT(7);
}

/**
 * @brief Generate the data for a single LED
 *
 * @param index the index of the LED
 * @param red the red value
 * @param green the green value
 * @param blue the blue value
 * @param buf the buffer to write the data to
 */
void generate_data(uint32_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t* buf) {
    memset(buf + (index)*WS2812_LED_BUF, 0, WS2812_LED_BUF);
    set_data_bit(green, buf + (index)*WS2812_LED_BUF);
    set_data_bit(red, buf + (index)*WS2812_LED_BUF + 3);
    set_data_bit(blue, buf + (index)*WS2812_LED_BUF + 6);
}

struct __FastLED_Config_internal {
    gpio_num_t pin_number;
    spi_device_handle_t spi_handle;
    uint8_t* led_strip_pixels;
    int lengthRGB;
    int lengthPixels;
};

FastLEDConfig* initFastLED(int length, gpio_num_t pin_number) {
    FastLEDConfig* config = (FastLEDConfig*)calloc(sizeof(FastLEDConfig), 1);
    *config = (FastLEDConfig){
        .pin_number = pin_number,
        .led_strip_pixels = heap_caps_calloc(length, WS2812_LED_BUF, MALLOC_CAP_8BIT),
        .lengthRGB = length,
        .lengthPixels = length * WS2812_LED_BUF,
    };

    gpio_set_drive_capability(config->pin_number, GPIO_DRIVE_CAP_3);

    spi_bus_config_t bus_config = {
        .mosi_io_num = config->pin_number,
        .miso_io_num = -1,
        .sclk_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = config->lengthRGB * WS2812_LED_BUF_BIT,
    };

    spi_device_interface_config_t dev_config = {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .clock_speed_hz = WS2812_SPI_SPEED_HZ,
        .duty_cycle_pos = 128,
        .mode = 0,
        .spics_io_num = -1,
        .queue_size = 1,
    };

    spi_bus_initialize(SPI2_HOST, &bus_config, SPI_DMA_CH_AUTO);

    spi_bus_add_device(SPI2_HOST, &dev_config, &config->spi_handle);

    _write(config->spi_handle, config->led_strip_pixels, config->lengthPixels);

    return config;
}

void writeLED(FastLEDConfig* config, int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index >= config->lengthRGB) {
        ESP_LOGE(TAG_FAST_LED, "Index out of range: %d", index);
        return;
    }
    generate_data(index, red, green, blue, config->led_strip_pixels);
}

void showLED(FastLEDConfig* config) {
    _write(config->spi_handle, config->led_strip_pixels, config->lengthRGB * WS2812_LED_BUF_BIT);
}