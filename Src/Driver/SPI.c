#include "Driver/SPI.h"

/* SPI2 Pin Mapping
 *  SPI2_MOSI - PB15
 *  SPI2_MISO - PB14
 *  SPI2_SCK  - PB13
 *  SPI2_NSS  - PB12 (Default, can be reassigned)
 *
 *  BMP280_CS  - PB5
 *  W25Q64_CS  - PB6
 */

#define GPIO_PIN_5  (1U << 5)  // Pin 5
#define GPIO_PIN_6  (1U << 6)  // Pin 6

void SPI2_Init(void)
{
    // Enable clock for GPIO Port B
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    // Enable clock for SPI2 peripheral
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

    // Configure PB13, PB14, PB15 as Alternate Function for SPI2
    GPIOB->MODER &= ~(GPIO_MODER_MODE12 | GPIO_MODER_MODE13 | GPIO_MODER_MODE14 | GPIO_MODER_MODE15);
    GPIOB->MODER |= (GPIO_MODER_MODE12_0 | GPIO_MODER_MODE13_1 | GPIO_MODER_MODE14_1 | GPIO_MODER_MODE15_1);
    GPIOB->AFR[1] |= ((5 << 20) | (5 << 24) | (5 << 28));

    // Configure PB5 and PB6 as output for additional SS pins
    GPIOB->MODER |= (GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0);
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT5 | GPIO_OTYPER_OT6);
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6);

    // Pull all CS lines HIGH (Inactive)
    SPI2_DeselectSlave(GPIOB, GPIO_PIN_5);
    SPI2_DeselectSlave(GPIOB, GPIO_PIN_6);

    // Configure SPI2 in master mode, baud rate = fPCLK / 16, CPOL = 0, CPHA = 0, 8-bit data format
    SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSI | SPI_CR1_SSM;
    // Enable SPI2
    SPI2->CR1 |= SPI_CR1_SPE;
}

// Modified functions for multiple SS pins
void SPI2_SelectSlave(GPIO_TypeDef *CS_Port, uint16_t CS_Pin)
{
    CS_Port->BSRR = (1 << (CS_Pin + 16)); // Pull CS Low
}

void SPI2_DeselectSlave(GPIO_TypeDef *CS_Port, uint16_t CS_Pin)
{
    CS_Port->BSRR = (1 << CS_Pin); // Pull CS High
}

uint8_t SPI2_TransmitReceiveByte(uint8_t data)
{
    while (!(SPI2->SR & SPI_SR_TXE)); // Wait until TXE (Transmit buffer empty)
    SPI2->DR = data;
    while (!(SPI2->SR & SPI_SR_RXNE)); // Wait until RXNE (Receive buffer not empty)
    return (uint8_t)(SPI2->DR);
}

void SPI2_TransmitReceive_MultiByte(uint8_t *txData, uint8_t *rxData, uint16_t size)
{
    uint16_t i = 0;
    while (i < size)
    {
        while (!(SPI2->SR & SPI_SR_TXE)); // Wait until TXE (Transmit buffer empty)
        SPI2->DR = txData[i];
        while (!(SPI2->SR & SPI_SR_RXNE)); // Wait until RXNE (Receive buffer not empty)
        uint8_t receivedByte = (uint8_t)(SPI2->DR);
        if (rxData != NULL)
        {
            rxData[i] = receivedByte;
        }
        i++;
    }
}
