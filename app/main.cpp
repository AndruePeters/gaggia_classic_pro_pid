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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

/// C++ Includes
#include <algorithm>
#include <cstdio>
#include <limits>



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

    /// In house room temperature
    float tempF = 70.0;

    /// Treat the boiler has a piecewise-linear function with two different slopes
    const float boilerHeat = 0.2;
    const float boilerCool = -0.08;

    /// Basic heatWater model
    auto heatWater = [&](bool on, float dutyCycle = 1.0) {
        if (on) {
            tempF = tempF + boilerHeat * tempF * dutyCycle;
        } else {
            tempF = tempF + boilerCool * tempF;
        }
    };


    /// Keep track of some statistics
    float outMin = std::numeric_limits<float>::max();
    float outMax = std::numeric_limits<float>::min();
    float runningTotal = 0;
    float avg = 0;

    /// Main while loop
    while (true) {
        /// count the number of samples
        static int i = 0;

        /// get the PID output value
        float out = pid.getOutput(tempF);

        /// a negative out means we need to heat water and positive cool it
        if (out < 0) {
            heatWater(true);
        } else if (out > 0) {
            heatWater(false);
        }

        /// update the stats
        outMin = std::min(outMin, out);
        outMax = std::max(outMax, out);
        runningTotal += out;
        ++i;

        /// only evaluate every 1000 cycles
        if(i % 1000 == 0) {
            gpio_set_level(BLINK_GPIO, 0);
            const float avg = runningTotal / static_cast<float>(i);
            printf("min: %f\tmax: %f\tavg: %f\n\t\ttemp:%f\n", outMin, outMax, avg, tempF);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_set_level(BLINK_GPIO, 1);
        }

    }
}
