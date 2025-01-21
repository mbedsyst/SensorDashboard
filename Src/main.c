#include "VCOM.h"
#include <stdio.h>

int main(void)
{
    char input_char;
    UART2_Init();  // Initialize UART2

    printf("Enter a character: ");

    while (1)
    {
        printf("Enter a character: ");
        scanf(" %c", &input_char);  // The space before %c skips whitespace, including newline
        printf("\r\nYou entered: %c\r\n", input_char);
    }

    return 0;
}
