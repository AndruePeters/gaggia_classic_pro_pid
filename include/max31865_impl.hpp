template<class TemperatureType>
Controller<TemperatureType>::Controller(const spi_device_interface_config_t &spiConfig, const spi_device_handle_t &spiHandle):
    spiDeviceConfig(spiConfig), spiHandle(spiHandle)
{

}



template<class TemperatureType>
void Controller<TemperatureType>::setBias(const bool biasState)
{
    configuration_register[7] = biasState;
}


template<class TemperatureType>
void Controller<TemperatureType>::setConversionMode(bool automatic)
{
    configuration_register[6] = automatic;
}


template<class TemperatureType>
void Controller<TemperatureType>::setWireCount(const number_of_wires numWires)
{
    configuration_register[4] = convert_enum(numWires);
}

template<class TemperatureType>
void Controller<TemperatureType>::clearFaultDetection(bool clearFault)
{

}

template<class TemperatureType>
void Controller<TemperatureType>::setFilter(configuration_filter cf)
{
    configuration_register[0] = convert_enum(cf);
}

template<class TemperatureType>
uint8_t Controller<TemperatureType>::readRegister(const register_read_address readAddress)
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

template<class TemperatureType>
void Controller<TemperatureType>::writeRegister(const register_write_address writeAddress, const uint8_t value)
{
    static spi_transaction_t writeTransaction;
    std::memset(&writeTransaction, 0, sizeof(writeTransaction));

    writeTransaction.flags = 0 | SPI_TRANS_USE_TXDATA;
    writeTransaction.length = 16;
    writeTransaction.tx_data[0] = convert_enum<register_write_address, uint8_t>(writeAddress);
    writeTransaction.tx_data[1] = value;

    const auto retError = spi_device_transmit(this->spiHandle, &writeTransaction);
}
