#ifndef MAX31865_H
#define MMAX31865_H

/// esp32 includes
#include <driver/spi_master.h>

#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstring>

/// Driver for the max31865 on the esp32 using the esp-idf SDK.
/// Goal of this driver is to wrap only the max31865 functionality, temperature conversion will be a separate module
///
/// This class is designed only to control a SPI device, not configure it
namespace max31865
{

/// Converts Enum to a numerical type
template <class Enum, class Integer = int> Integer convert_enum(Enum e)
{
    return static_cast<Integer>(e);
}

/// Addresses for the MAX31865 read registers
enum struct register_read_address : uint8_t
{
    configuration = 0x00,
    rtd_msb = 0x01,
    rtd_lsb = 0x02,
    high_fault_threshold_msb = 0x03,
    high_fault_threshold_lsb = 0x04,
    low_fault_threshold_msb = 0x05,
    low_fault_threshold_lsb = 0x06,
    fault_status = 0x07
};

/// Addresses for the MAX31865 write registers
enum struct register_write_address : uint8_t
{
    configuration = 0x80,
    high_fault_threshold_msb = 0x83,
    high_fault_threshold_lsb = 0x84,
    low_fault_threshold_msb = 0x85,
    low_fault_threshold_lsb = 0x86,
};

/// Number of wires being used for the temperature sensor
enum struct number_of_wires
{
    two = 0,
    three = 1,
    four = 0
};

/// Fault type reported by MAX31865
enum struct fault
{
    none = 0,
    voltage,
    rtd_in_low,
    ref_low,
    ref_high,
    rtd_low,
    rtd_high
};

/// 50Hz or 60Hz filter
enum struct configuration_filter : uint8_t
{
    hz60 = 0x00,
    hz50 = 0x01
};

/// Conversion mode
enum struct conversion_mode : uint8_t
{
    one_shot = 0,
    automatic = 1
};

/// The state of the bias
enum struct bias_state : uint8_t
{
    off = 0,
    on = 1
};

/// Communication is done through eight 8-bit registers that contain data
/// Reads with 0xh
/// Writes with 8xh

/*
 * Configuration Register (00h)
 * D7 = BIAS - only really useful for one-shot
 * D6 = ConversionMode; 1 == automatic
 * D5 = 1-Shot; 1 then CS to do a single conversion
 * D4 = 3-wire; 1 == 3wire, 0 means 2/4 wire
 * D3+D2 = Fault Detection
 * D1 = Fault Status Clear
 * D0 = 50/60Hz filter; 1 == 50, 0 == 60
 */

///
class Controller
{
    const spi_device_interface_config_t &spiDeviceConfig;
    const spi_device_handle_t &spiHandle;

    /// Holds the configuration_register state
    std::bitset<8> configuration_register;

    /// Bits [15-8] are in register 0x01
    /// Bits [7-0] are in register 0x02
    uint16_t rtdRegister = 0;

  public:
    uint8_t readRegister(const register_read_address readAddress) const;
    void writeRegister(const register_write_address writeAddress, const uint8_t value);

  public:
    ///
    /// \param spiConfig Already configured spi interface object
    /// \param spiHandle Handle to spi device
    Controller(const spi_device_interface_config_t &spiConfig, const spi_device_handle_t &spiHandle);

    /// need to write config registers
    /// need to read rtd registers
    /// general read register method

    ///
    /// \param bias
    /// Sets the bias register on or off
    void setBias(bias_state bias = bias_state::on);

    ///
    /// \param automatic
    void setConversionMode(conversion_mode conversionMode = conversion_mode::automatic);

    ///
    /// \param numWires
    void setWireCount(number_of_wires numWires = number_of_wires::four);

    ///
    /// \param clearFault
    void clearFaultDetection(bool clearFault = true);

    ///
    /// \param cf
    void setFilter(configuration_filter cf = configuration_filter::hz60);

    ///
    void writeConfigurationSettings();

    /// returns 0 if fault detected
    uint16_t readRTDResistanceRatio() const;

    /// Set the lsb's and msb's for the low and high threshold registers
    void setRTDHighFaultThresholdMsb(uint8_t msbThreshold);
    void setRTDHighFaultThresholdLsb(uint8_t lsbThreshold);
    void setRTDLowFaultThresholdMsb(uint8_t msbThreshold);
    void setRTDLowFaultThresholdLsb(uint8_t lsbThreshold);
};

} // namespace max31865

#endif