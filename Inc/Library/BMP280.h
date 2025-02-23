#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>

// BMP280 Register Addresses
#define BMP280_CHIP_ID_REG     0xD0
#define BMP280_RESET_REG       0xE0
#define BMP280_CTRL_MEAS_REG   0xF4
#define BMP280_CONFIG_REG      0xF5
#define BMP280_PRESS_MSB_REG   0xF7
#define BMP280_TEMP_MSB_REG    0xFA
#define BMP280_RESET_VALUE     0xB6

// Function Prototypes
void BMP280_Init(void);
void BMP280_WriteRegister(uint8_t reg, uint8_t value);
uint8_t BMP280_ReadRegister(uint8_t reg);
void BMP280_ReadRawData(int32_t *temperature, int32_t *pressure);

#endif // BMP280_H
