#include "Library/BMP280.h"
#include "Driver/SPI.h"

#define BMP280_SPI_CS_LOW()    SPI2_SelectSlave()
#define BMP280_SPI_CS_HIGH()   SPI2_DeselectSlave()

// Function to write to a BMP280 register
void BMP280_WriteRegister(uint8_t reg, uint8_t value)
{
    uint8_t data[2] = {reg & 0x7F, value}; // MSB must be 0 for write
    BMP280_SPI_CS_LOW();
    SPI2_TransmitReceive_MultiByte(data, NULL, 2);
    BMP280_SPI_CS_HIGH();
}

// Function to read from a BMP280 register
uint8_t BMP280_ReadRegister(uint8_t reg)
{
    uint8_t txData[2] = {reg | 0x80, 0xFF}; // MSB must be 1 for read
    uint8_t rxData[2] = {0};
    BMP280_SPI_CS_LOW();
    SPI2_TransmitReceive_MultiByte(txData, rxData, 2);
    BMP280_SPI_CS_HIGH();
    return rxData[1];
}

// Function to initialize BMP280
void BMP280_Init(void)
{
    SPI2_Init();
    BMP280_WriteRegister(BMP280_RESET_REG, BMP280_RESET_VALUE);
    BMP280_WriteRegister(BMP280_CTRL_MEAS_REG, 0x27); // Temp and Pressure oversampling x1, Normal mode
    BMP280_WriteRegister(BMP280_CONFIG_REG, 0xA0);    // Standby time 1000ms, filter off
}

// Function to read raw temperature and pressure data
void BMP280_ReadRawData(int32_t *temperature, int32_t *pressure)
{
    uint8_t rawData[6];
    uint8_t txData[6] = {BMP280_PRESS_MSB_REG | 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    BMP280_SPI_CS_LOW();
    SPI2_TransmitReceive_MultiByte(txData, rawData, 6);
    BMP280_SPI_CS_HIGH();

    int32_t rawPressure = ((int32_t)rawData[1] << 12) | ((int32_t)rawData[2] << 4) | ((int32_t)(rawData[3] >> 4));
    int32_t rawTemperature = ((int32_t)rawData[4] << 12) | ((int32_t)rawData[5] << 4) | ((int32_t)(rawData[6] >> 4));

    *temperature = rawTemperature;
    *pressure = rawPressure;
}
