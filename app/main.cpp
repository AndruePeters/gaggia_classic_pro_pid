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

#include <Max31865.h>

using namespace std::chrono_literals;

/// Use GPIO pin 2 to blink the LED
gpio_num_t BLINK_GPIO = static_cast<gpio_num_t>(2);

/// app_main requires C bindings
extern "C" {
void app_main(void);
}


void app_main(void) {
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    /// Set up the PIDController object
    PIDController<float> pid(203);
    pid.setDerivativeCoefficient(15);
    pid.setIntegralCoefficient(60);
    pid.setProcessVariableCoefficient(4);

    auto tempSensor = Max31865(12, 13, 14, 15);
    max31865_config_t tempConfig = {};
    tempConfig.autoConversion = true;
    tempConfig.vbias = true;
    tempConfig.filter = Max31865Filter::Hz60;
    tempConfig.nWires = Max31865NWires::Three;
    max31865_rtd_config_t rtdConfig = {};
    rtdConfig.nominal = 100.0f;
    rtdConfig.ref = 430.0f;
    ESP_ERROR_CHECK(tempSensor.begin(tempConfig));
    ESP_ERROR_CHECK(tempSensor.setRTDThresholds(0x2000, 0x2500));

    /// Main while loop
    while (true) {
        uint16_t rtd;
        Max31865Error fault = Max31865Error::NoError;
        tempSensor.getRTD(&rtd, &fault);

        if (fault != Max31865Error::NoError ) {
            printf("Fault detected: %s\nClearing fault now.", tempSensor.errorToString(fault));
            tempSensor.clearFault();
        }
        const float temp = Max31865::RTDtoTemperature(rtd, rtdConfig);
        printf("Temperature: %.2f C\n", temp);
        std::this_thread::sleep_for(1s);
    }
}
