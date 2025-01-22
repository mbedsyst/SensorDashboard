#include "Driver/UART.h"

#define UART_BAUDRATE	115200
#define SYS_FREQ		16000000
#define APB2_CLK		SYS_FREQ

static uint16_t Compute_UART_Baud(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);
}

static void UART6_SetBaudRate(uint32_t periph_clk, uint32_t baudrate)
{
	USART6->BRR = Compute_UART_Baud(periph_clk,baudrate);
}

void UART6_Init(void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	/*Enable clock access to UART6*/
	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
	/*Set PA11 & PA12 to alternate function mode */
	GPIOA->MODER &=~((3U<<22) | (3U<<24));
	GPIOA->MODER |=((2U<<22) | (2U<<24));
	/*Set PA11 alternate function type to (AF08)*/
	GPIOA->AFR[1] &= ~((0xF << 12) | (0xF << 16));
	GPIOA->AFR[1] |= (8U << 12) | (8U << 16);
	/*Configure Baud Rate*/
	UART6_SetBaudRate(APB2_CLK,UART_BAUDRATE);
	/*Configure the Transfer directions*/
	USART6->CR1 |= (USART_CR1_TE);
	/*Enable UART module*/
	USART6->CR1 |= USART_CR1_UE;
}

void UART6_TxChar(char ch)
{
	/*Wait for Transmit Data Register to be empty*/
	while(!(USART6->SR & USART_SR_TXE));
	/*Write to the Transmit Data Register*/
	USART6->DR = (ch &0xFF);
}

void UART6_TxString(char *str)
{
	while(*str)
	{
		UART6_TxChar(*str++);
	}
}
