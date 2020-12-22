/// Andrue Peters
///
/// This file is taken from the main Espressif blink example
/// but has been adapted. Its current form has some test PID
/// code, but this will eventually be the main app pulling
/// all code together.

/// Project Includes
#include <pid.h>


/// Espressif Includes
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/spi_common.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

/// C++ Includes
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <limits>
#include <thread>


using namespace std::chrono_literals;

/// Use GPIO pin 2 to blink the LED
gpio_num_t BLINK_GPIO = static_cast<gpio_num_t>(2);

/// app_main requires C bindings
extern "C" {
void app_main(void);
}


void app_main(void) {

    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(GPIO_NUM_15);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_15, 1);

    spi_bus_config_t buscfg ={
            .mosi_io_num = 13,
            .miso_io_num = 12,
            .sclk_io_num = 14,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = 32,
    };


    // Initialize the SPI bus
    auto ret = spi_bus_initialize(HSPI_HOST, &buscfg, 0);
    ESP_ERROR_CHECK(ret);

    auto devcfg = spi_device_interface_config_t {
        .command_bits = 0,
        .address_bits = 0,
        .dummy_bits = 0,
        .mode = 1,
        .duty_cycle_pos = 0,
        .cs_ena_pretrans = 0,
        .cs_ena_posttrans = 0,
        .clock_speed_hz = 30'000,
        .input_delay_ns = 0,
        .spics_io_num = -1,
        .flags = SPI_DEVICE_HALFDUPLEX,
        .queue_size = 1,
        .pre_cb = nullptr,
        .post_cb = nullptr
    };


    auto trans = spi_transaction_t {
        .flags = 0 | SPI_TRANS_USE_TXDATA,
        .length = 16,
        .user = nullptr,
    };

    trans.tx_data[0] = 0x80;
    trans.tx_data[1] = 0b11010000;


    spi_device_handle_t spi;
    ret = spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

    gpio_set_level(GPIO_NUM_15, 0);
    std::this_thread::sleep_for(1ms);
    ret = spi_device_transmit(spi, &trans);
    ESP_ERROR_CHECK(ret);
    gpio_set_level(GPIO_NUM_15, 1);
    std::this_thread::sleep_for(1ms);

    trans.tx_data[0] = 0x00;
    trans.length = 8;
    trans.flags |= SPI_TRANS_USE_RXDATA;
    trans.rxlength = 8;

    gpio_set_level(GPIO_NUM_15, 0);
    std::this_thread::sleep_for(1ms);
    ret = spi_device_transmit(spi, &trans);

    printf("\n\nOriginal: %d\n\n", 0b11010000);
    printf("\n\nResult: %d\n\n", trans.rx_data[0]);




    /// Main while loop
    while (true) {

        std::this_thread::sleep_for(1s);
    }
}
