// BH1750.c
#include "Library/BH1750.h"
#include "Driver/I2C.h"

void BH1750_Init(void)
{
    I2C1_Start();
    I2C1_SendAddress(BH1750_ADDRESS, 0); // Write mode
    I2C1_SendData(BH1750_MODE_CONT_H_RES);
    I2C1_Stop();
}

uint16_t BH1750_ReadLightLevel(void)
{
    uint16_t lightLevel = 0;

    I2C1_Start();
    I2C1_SendAddress(BH1750_ADDRESS, 1); // Read mode

    I2C1_EnableACK();
    lightLevel = (I2C1_ReadData() << 8); // MSB

    I2C1_DisableACK();
    lightLevel |= I2C1_ReadData();       // LSB

    I2C1_Stop();

    return lightLevel / 1.2; // Convert to lux
}
