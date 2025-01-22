#include "Library/BMP280.h"

static void BMP280_WriteRegister(uint8_t reg, uint8_t value) {
    SPI2_SelectSlave();
    SPI2_TransmitReceiveByte(reg & 0x7F); // Write bit (MSB = 0)
    SPI2_TransmitReceiveByte(value);
    SPI2_DeselectSlave();
}

static uint8_t BMP280_ReadRegister(uint8_t reg) {
    uint8_t value;
    SPI2_SelectSlave();
    SPI2_TransmitReceiveByte(reg | 0x80); // Read bit (MSB = 1)
    value = SPI2_TransmitReceiveByte(0xFF); // Dummy write
    SPI2_DeselectSlave();
    return value;
}

static void BMP280_ReadRegisters(uint8_t reg, uint8_t *buffer, uint16_t size) {
    SPI2_SelectSlave();
    SPI2_TransmitReceiveByte(reg | 0x80); // Read bit (MSB = 1)
    SPI2_TransmitReceive_MultiByte(NULL, buffer, size);
    SPI2_DeselectSlave();
}

void BMP280_Init(void) {
    SPI2_Init();
    uint8_t chipID = BMP280_ReadID();
    if (chipID != 0x58) {
        // Handle error: BMP280 not detected
        while (1);
    }
    BMP280_Reset();
}

void BMP280_Reset(void) {
    BMP280_WriteRegister(BMP280_REG_RESET, 0xB6); // Reset command
}

uint8_t BMP280_ReadID(void) {
    return BMP280_ReadRegister(BMP280_REG_ID);
}

void BMP280_ReadCalibrationData(BMP280_CalibData *calib) {
    uint8_t calibBuffer[BMP280_CALIB_SIZE];
    BMP280_ReadRegisters(BMP280_CALIB_START, calibBuffer, BMP280_CALIB_SIZE);

    calib->dig_T1 = (calibBuffer[1] << 8) | calibBuffer[0];
    calib->dig_T2 = (calibBuffer[3] << 8) | calibBuffer[2];
    calib->dig_T3 = (calibBuffer[5] << 8) | calibBuffer[4];
    calib->dig_P1 = (calibBuffer[7] << 8) | calibBuffer[6];
    calib->dig_P2 = (calibBuffer[9] << 8) | calibBuffer[8];
    calib->dig_P3 = (calibBuffer[11] << 8) | calibBuffer[10];
    calib->dig_P4 = (calibBuffer[13] << 8) | calibBuffer[12];
    calib->dig_P5 = (calibBuffer[15] << 8) | calibBuffer[14];
    calib->dig_P6 = (calibBuffer[17] << 8) | calibBuffer[16];
    calib->dig_P7 = (calibBuffer[19] << 8) | calibBuffer[18];
    calib->dig_P8 = (calibBuffer[21] << 8) | calibBuffer[20];
    calib->dig_P9 = (calibBuffer[23] << 8) | calibBuffer[22];
}

void BMP280_SetConfig(uint8_t config, uint8_t ctrl_meas) {
    BMP280_WriteRegister(BMP280_REG_CONFIG, config);
    BMP280_WriteRegister(BMP280_REG_CTRL_MEAS, ctrl_meas);
}

void BMP280_ReadRawData(int32_t *rawTemp, int32_t *rawPress) {
    uint8_t data[6];
    BMP280_ReadRegisters(BMP280_REG_PRESS_MSB, data, 6);

    *rawPress = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    *rawTemp = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
}

float BMP280_CalculateTemperature(int32_t rawTemp, BMP280_CalibData *calib) {
    int32_t var1, var2, T;
    var1 = ((((rawTemp >> 3) - ((int32_t)calib->dig_T1 << 1))) * ((int32_t)calib->dig_T2)) >> 11;
    var2 = (((((rawTemp >> 4) - ((int32_t)calib->dig_T1)) * ((rawTemp >> 4) - ((int32_t)calib->dig_T1))) >> 12) *
            ((int32_t)calib->dig_T3)) >> 14;
    T = var1 + var2;
    return (T * 5 + 128) >> 8;
}

float BMP280_CalculatePressure(int32_t rawPress, BMP280_CalibData *calib) {
    // Pressure calculation (use datasheet formulas)
    // Implement similar logic as temperature calculation
    return 0; // Placeholder
}
