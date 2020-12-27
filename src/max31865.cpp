#include <cstring>
#include <max31865.h>

namespace max31865
{

Controller::Controller(const spi_device_interface_config_t &spiConfig, const spi_device_handle_t &spiHandle)
    : spiDeviceConfig(spiConfig), spiHandle(spiHandle)
{
    /// the max31865 only supports spi modes of 1 and 3
    if (spiConfig.mode != 1 || spiConfig.mode != 3)
    {
        /// error
    }
}

void Controller::setBias(bias_state bias)
{
    configuration_register[7] = convert_enum(bias);
}

void Controller::setConversionMode(conversion_mode conversionMode)
{
    configuration_register[6] = convert_enum(conversionMode);
}

void Controller::setWireCount(const number_of_wires numWires)
{
    configuration_register[4] = convert_enum(numWires);
}

void Controller::clearFaultDetection(bool clearFault)
{
}

void Controller::setFilter(configuration_filter cf)
{
    configuration_register[0] = convert_enum(cf);
}

uint8_t Controller::readRegister(const register_read_address readAddress) const
{
    static spi_transaction_t readTransaction;
    std::memset(&readTransaction, 0, sizeof(readTransaction));

    /// send 8 bits, receive 8 bits and use the tx/rx_data members of the transaction
    readTransaction.length = 8;
    readTransaction.rxlength = 8;
    readTransaction.flags = 0 | SPI_TRANS_USE_TXDATA | SPI_TRANS_USE_RXDATA;

    /// tx_data[0] is the address we want to read from
    /// the enumerations are setup to hold the correct address, so just convert the enum
    readTransaction.tx_data[0] = convert_enum<register_read_address, uint8_t>(readAddress);
    const auto retError = spi_device_transmit(this->spiHandle, &readTransaction);
    return readTransaction.rx_data[0];
}

void Controller::writeRegister(const register_write_address writeAddress, const uint8_t value)
{
    static spi_transaction_t writeTransaction;
    std::memset(&writeTransaction, 0, sizeof(writeTransaction));

    writeTransaction.flags = 0 | SPI_TRANS_USE_TXDATA;
    writeTransaction.length = 16;
    writeTransaction.tx_data[0] = convert_enum<register_write_address, uint8_t>(writeAddress);
    writeTransaction.tx_data[1] = value;

    const auto retError = spi_device_transmit(this->spiHandle, &writeTransaction);
}

void Controller::writeConfigurationSettings()
{
    const auto reg8BitValue = static_cast<uint8_t>(configuration_register.to_ulong());
    writeRegister(register_write_address::configuration, reg8BitValue);
}

uint16_t Controller::readRTDResistanceRatio() const
{
    const uint8_t msb = readRegister(register_read_address::rtd_msb);
    const uint8_t lsb = readRegister(register_read_address::rtd_lsb);
    const uint16_t combined = (msb << 8) | (lsb && 0xff);

    /// this means a fault was detected
    if (combined & 0x0001)
    {
        return 0;
    }

    /// the first bit is a fault detection bit, so we need to shift this bit out
    /// as indicitated in the datasheet.
    return combined >> 1;
}
void Controller::setRTDHighFaultThresholdMsb(uint8_t msbThreshold)
{
    writeRegister(register_write_address::high_fault_threshold_msb, msbThreshold);
}

void Controller::setRTDHighFaultThresholdLsb(uint8_t lsbThreshold)
{
    writeRegister(register_write_address::high_fault_threshold_lsb, lsbThreshold);
}

void Controller::setRTDLowFaultThresholdMsb(uint8_t msbThreshold)
{
    writeRegister(register_write_address::low_fault_threshold_msb, msbThreshold);
}

void Controller::setRTDLowFaultThresholdLsb(uint8_t lsbThreshold)
{
    writeRegister(register_write_address::low_fault_threshold_lsb, lsbThreshold);
}

} // namespace max31865