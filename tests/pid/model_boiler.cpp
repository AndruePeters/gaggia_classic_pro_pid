/// Andrue Peters
///
/// Simulate the boiler on the Gaggia Classic Pro in order to do a crude
/// tuning of PID parameters. The boiler is assumed to be a linear piecewise
/// function where it is always heating or cooling. I might fix it up slightly
/// to include some nature of duty-cycle

/// Project Includes
#include <pid.h>


/// C++ Includes
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <limits>
#include <thread>

using namespace std::chrono_literals;
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
    float tempRunningTotal = 0;


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
        tempRunningTotal += tempF;
        ++i;

        /// only evaluate every 1000 cycles
        if(i % 1000 == 0) {
            const float avg = runningTotal / i;
            const float avgTemp =  tempRunningTotal / i;
            printf("min: %f\tmax: %f\tavg: %f\ttemp:%f\tavgTemp:%f\n", outMin, outMax, avg, tempF, avgTemp);
            std::this_thread::sleep_for(2s);
        }

    }
}
