#ifndef MAX31865_H
#define MMAX31865_H
/*
#include <cstdint>
#include <cmath>
namespace max31865 {
/// Lets use VSPI just for kicks
/// DRDY is connected to GPIO22

/// Addresses for the read registers
enum struct register_read_address : uint8_t {
    configuration = 0x00,
    rtd_msb = 0x01,
    rtd_lsb = 0x02,
    high_fault_threshold_msb = 0x03,
    high_fault_threshold_lsb = 0x04,
    low_fault_threshold_msb = 0x05,
    low_fault_threshold_lsb = 0x06,
    fault_status            = 0x07
};

/// Addresses for the write registers
enum struct register_write_address : uint8_t {
    configuration = 0x80,
    high_fault_threshold_msb = 0x83,
    high_fault_threshold_lsb = 0x84,
    low_fault_threshold_msb = 0x85,
    low_fault_threshold_lsb = 0x86,
};

 enum struct number_of_wires {
    two = 0,
    three = 1,
    four = 0
};

 enum struct error {
    none = 0,
    voltage,
    rtd_in_low,
    ref_low,
    ref_high,
    rtd_low,
    rtd_high
 };

/// Values for D0 of the Configuration register
enum struct configuration_filter : uint8_t {
    hz60 = 0x00,
    hz50 = 0x01
};

/// Communication is done through eight 8-bit registers that contain data
/// Reads with 0xh
/// Writes with 8xh


 * Configuration Register (00h)
 * D7 = BIAS - only really useful for one-shot
 * D6 = ConversionMode; 1 == automatic
 * D5 = 1-Shot; 1 then CS to do a single conversion
 * D4 = 3-wire; 1 == 3wire, 0 means 2/4 wire
 * D3+D2 = Fault Detection
 * D1 = Fault Status Clear
 * D0 = 50/60Hz filter; 1 == 50, 0 == 60



 * RTD Resistance Registers

/// RREF for this resistor is 430 ohms
///
template <class TemperatureType>
class MAX31865Controller {
    void setBias(bool biasState = true);
    void setConversionMode(bool automatic = true);
    void setOneShot(bool oneShotStatus = true);
    void setThreeWire(bool threeWireStatus = true);
    void clearFaultDetection(bool clearFault = true);
    void setFilter(configuration_filter = configuration_filter::hz60);

    /// this equation is currently only valid for temperatures > 0*C
    /// break this out later into its own class and test different methods for a wider range of temperatures
    /// and performance from https://www.analog.com/media/en/technical-documentation/application-notes/AN709_0.pdf
    TemperatureType toC()
    {
        const float a = 3.90830 * std::pow(10, -3);
        const float b = -5.77500 * std::pow(10, -7);
        const float c = 0; // only 0 for 0 <= T <= 850 [C]
        const float Rt = 0; // call readRTD()
        float z1 = -a;
        float z2 = (a*a) - (4*b);
        float z3 = (4*b) / R0;
        float z4 = 2 * b;

        float radicand = z2 + z3 * r;
        return (z1 + radicand) / z4;
    }
};
/*
}
#endif