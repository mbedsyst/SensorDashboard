#include "stm32f4xx.h"
#include "UART.h" // Header file for UART6 driver

int main(void)
{
    /* Initialize UART6 */
    UART6_Init();

    /* Print Hello World using UART6 */
    UART6_TxString("Hello World!\r\n");

    /* Infinite loop */
    while (1)
    {
        // Your application code (if any)
    }

    return 0;
}
