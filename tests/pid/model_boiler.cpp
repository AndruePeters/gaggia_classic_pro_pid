/// Andrue Peters
///
/// This file is taken from the main Espressif blink example
/// but has been adapted. Its current form has some test PID
/// code, but this will eventually be the main app pulling
/// all code together.

/// Project Includes
#include <pid.h>


/// C++ Includes
#include <algorithm>
#include <cstdio>
#include <limits>
#include <thread>

int main() {


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
            const float avg = runningTotal / static_cast<float>(i);
            printf("min: %f\tmax: %f\tavg: %f\n\t\ttemp:%f\n", outMin, outMax, avg, tempF);
        }

    }
}
