#include "Library/BMP280.h"
#include "Driver/I2C.h"

static BMP280_CalibData bmp280_calib;
static int32_t t_fine;

// Function to read multiple bytes from BMP280
static void BMP280_ReadRegister(uint8_t reg, uint8_t* data, uint8_t length)
{
    I2C1_Start();
    I2C1_SendAddress(BMP280_I2C_ADDR, false);
    I2C1_SendData(reg);
    I2C1_Start(); // Repeated Start
    I2C1_SendAddress(BMP280_I2C_ADDR, true);

    for (uint8_t i = 0; i < length - 1; i++) {
        I2C1_EnableACK();
        data[i] = I2C1_ReadData();
    }

    I2C1_DisableACK();
    data[length - 1] = I2C1_ReadData();
    I2C1_Stop();
}

// Function to write a byte to BMP280
static void BMP280_WriteRegister(uint8_t reg, uint8_t value)
{
    I2C1_Start();
    I2C1_SendAddress(BMP280_I2C_ADDR, false);
    I2C1_SendData(reg);
    I2C1_SendData(value);
    I2C1_Stop();
}

// Function to read the BMP280 calibration data
static void BMP280_ReadCalibrationData(void)
{
    uint8_t calib[24];
    BMP280_ReadRegister(BMP280_REG_CALIB, calib, 24);

    bmp280_calib.dig_T1 = (calib[1] << 8) | calib[0];
    bmp280_calib.dig_T2 = (calib[3] << 8) | calib[2];
    bmp280_calib.dig_T3 = (calib[5] << 8) | calib[4];
    bmp280_calib.dig_P1 = (calib[7] << 8) | calib[6];
    bmp280_calib.dig_P2 = (calib[9] << 8) | calib[8];
    bmp280_calib.dig_P3 = (calib[11] << 8) | calib[10];
    bmp280_calib.dig_P4 = (calib[13] << 8) | calib[12];
    bmp280_calib.dig_P5 = (calib[15] << 8) | calib[14];
    bmp280_calib.dig_P6 = (calib[17] << 8) | calib[16];
    bmp280_calib.dig_P7 = (calib[19] << 8) | calib[18];
    bmp280_calib.dig_P8 = (calib[21] << 8) | calib[20];
    bmp280_calib.dig_P9 = (calib[23] << 8) | calib[22];
}

// Function to initialize BMP280
bool BMP280_Init(void)
{
    uint8_t id;
    BMP280_ReadRegister(BMP280_REG_ID, &id, 1);

    if (id != 0x58) { // BMP280 should return ID = 0x58
        return false;
    }

    BMP280_ReadCalibrationData();

    // Set mode to Normal, Temperature oversampling x1, Pressure oversampling x1
    BMP280_WriteRegister(BMP280_REG_CTRL_MEAS, 0x27);

    // Set standby time to 0.5ms, IIR filter off
    BMP280_WriteRegister(BMP280_REG_CONFIG, 0x00);

    return true;
}

// Function to read raw temperature data
static int32_t BMP280_ReadRawTemperature(void)
{
    uint8_t data[3];
    BMP280_ReadRegister(BMP280_REG_TEMP_MSB, data, 3);
    return (int32_t)((data[0] << 16) | (data[1] << 8) | data[2]) >> 4;
}

// Function to read raw pressure data
static int32_t BMP280_ReadRawPressure(void)
{
    uint8_t data[3];
    BMP280_ReadRegister(BMP280_REG_PRESS_MSB, data, 3);
    return (int32_t)((data[0] << 16) | (data[1] << 8) | data[2]) >> 4;
}

// Function to compensate temperature
static float BMP280_CompensateTemperature(int32_t raw_temp)
{
    int32_t var1, var2;
    var1 = ((((raw_temp >> 3) - ((int32_t)bmp280_calib.dig_T1 << 1))) * ((int32_t)bmp280_calib.dig_T2)) >> 11;
    var2 = (((((raw_temp >> 4) - ((int32_t)bmp280_calib.dig_T1)) * ((raw_temp >> 4) - ((int32_t)bmp280_calib.dig_T1))) >> 12) * ((int32_t)bmp280_calib.dig_T3)) >> 14;
    t_fine = var1 + var2;
    return (float)((t_fine * 5 + 128) >> 8) / 100.0f;
}

// Function to compensate pressure
static float BMP280_CompensatePressure(int32_t raw_pressure)
{
    int64_t var1, var2, p;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)bmp280_calib.dig_P6;
    var2 += ((var1 * (int64_t)bmp280_calib.dig_P5) << 17);
    var2 += (((int64_t)bmp280_calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)bmp280_calib.dig_P3) >> 8) + ((var1 * (int64_t)bmp280_calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)bmp280_calib.dig_P1) >> 33;

    if (var1 == 0) return 0; // Avoid division by zero

    p = 1048576 - raw_pressure;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)bmp280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)bmp280_calib.dig_P8) * p) >> 19;
    return ((p + var1 + var2) >> 8) / 256.0f;
}

// Public functions to get temperature and pressure
bool BMP280_ReadTemperature(float* temperature)
{
    *temperature = BMP280_CompensateTemperature(BMP280_ReadRawTemperature());
    return true;
}

bool BMP280_ReadPressure(float* pressure)
{
    *pressure = BMP280_CompensatePressure(BMP280_ReadRawPressure());
    return true;
}

bool BMP280_ReadTemperatureAndPressure(float* temperature, float* pressure)
{
    *temperature = BMP280_CompensateTemperature(BMP280_ReadRawTemperature());
    *pressure = BMP280_CompensatePressure(BMP280_ReadRawPressure());
    return true;
}
