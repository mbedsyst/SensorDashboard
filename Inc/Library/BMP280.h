#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>
#include "Driver/SPI.h"

// BMP280 default SPI address
#define BMP280_SPI_ADDRESS 0x76

// BMP280 Registers
#define BMP280_REG_ID          0xD0
#define BMP280_REG_RESET       0xE0
#define BMP280_REG_CTRL_MEAS   0xF4
#define BMP280_REG_CONFIG      0xF5
#define BMP280_REG_PRESS_MSB   0xF7
#define BMP280_REG_PRESS_LSB   0xF8
#define BMP280_REG_PRESS_XLSB  0xF9
#define BMP280_REG_TEMP_MSB    0xFA
#define BMP280_REG_TEMP_LSB    0xFB
#define BMP280_REG_TEMP_XLSB   0xFC

// BMP280 calibration registers
#define BMP280_CALIB_START 0x88
#define BMP280_CALIB_SIZE  24

// BMP280 modes
#define BMP280_MODE_SLEEP   0x00
#define BMP280_MODE_FORCED  0x01
#define BMP280_MODE_NORMAL  0x03

// BMP280 oversampling settings
#define BMP280_OVERSAMPLING_NONE  0x00
#define BMP280_OVERSAMPLING_X1    0x01
#define BMP280_OVERSAMPLING_X2    0x02
#define BMP280_OVERSAMPLING_X4    0x03
#define BMP280_OVERSAMPLING_X8    0x04
#define BMP280_OVERSAMPLING_X16   0x05

// BMP280 filtering settings
#define BMP280_FILTER_OFF    0x00
#define BMP280_FILTER_X2     0x01
#define BMP280_FILTER_X4     0x02
#define BMP280_FILTER_X8     0x03
#define BMP280_FILTER_X16    0x04

typedef struct {
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
} BMP280_CalibData;

void BMP280_Init(void);
void BMP280_Reset(void);
uint8_t BMP280_ReadID(void);
void BMP280_ReadCalibrationData(BMP280_CalibData *calib);
void BMP280_SetConfig(uint8_t config, uint8_t ctrl_meas);
void BMP280_ReadRawData(int32_t *rawTemp, int32_t *rawPress);
float BMP280_CalculateTemperature(int32_t rawTemp, BMP280_CalibData *calib);
float BMP280_CalculatePressure(int32_t rawPress, BMP280_CalibData *calib);

#endif // BMP280_H
