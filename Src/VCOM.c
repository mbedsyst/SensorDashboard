#include <VCOM.h>

#define UART_BAUDRATE	115200
#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ

void UART2_Init(void)
{
    /* Enable clock access to GPIOA and UART2 */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* Set PA2 and PA3 to alternate function mode */
    GPIOA->MODER &= ~((3U << 4) | (3U << 6));
    GPIOA->MODER |= (2U << 4) | (2U << 6);

    /* Set alternate function type to UART (AF7) */
    GPIOA->AFR[0] |= (7U << 8) | (7U << 12);

    /* Configure Baud Rate */
    USART2->BRR = 0x008B; // For 16 MHz and 115200 baud

    /* Enable TX, RX, and UART */
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UART2_TxChar(char ch)
{
	/*Wait for Transmit Data Register to be empty*/
	while(!(USART2->SR & USART_SR_TXE));
	/*Write to the Transmit Data Register*/
	USART2->DR = (ch & 0xFF);
}

void UART2_TxString(char *str)
{
	while(*str)
	{
		UART2_TxChar(*str++);
	}
}

uint8_t UART2_RxChar(void)
{
    while(!(USART2->SR & USART_SR_RXNE)); // Wait for RXNE flag (data received)
    return (uint8_t)(USART2->DR & 0xFF); // Return the received data
}

int _write(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        UART2_TxChar(ptr[i]);  // Transmit each character via UART2
    }
    return len;  // Return the number of characters written
}

int _read(int file, char *ptr, int len)
{
    for (int i = 0; i < len; i++)
    {
        ptr[i] = UART2_RxChar();  // Read each character via UART2
        if (ptr[i] == '\r')      // Handle Enter key as a newline
        {
            ptr[i] = '\n';       // Convert '\r' to '\n' for standard behavior
            return i + 1;        // Return number of characters read
        }
    }
    return len;  // Return number of characters read
}
