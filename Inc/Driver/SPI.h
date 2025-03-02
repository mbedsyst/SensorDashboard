#ifndef SPI_H_
#define SPI_H_

#include <stddef.h>
#include "stm32f4xx.h"

void SPI2_Init(void);
void SPI2_SelectSlave(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SPI2_DeselectSlave(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t SPI2_TransmitReceiveByte(uint8_t data);
void SPI2_TransmitReceive_MultiByte(uint8_t *txData, uint8_t *rxData, uint16_t size);

#endif
