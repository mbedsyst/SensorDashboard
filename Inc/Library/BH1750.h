// BH1750.h
#ifndef BH1750_H
#define BH1750_H

#include <stdint.h>

// BH1750 I2C address
#define BH1750_ADDRESS 0x23

// BH1750 operating modes
#define BH1750_MODE_CONT_H_RES 0x10 // Continuous high-resolution mode

// Function prototypes
void BH1750_Init(void);
uint16_t BH1750_ReadLightLevel(void);

#endif // BH1750_H
