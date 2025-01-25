#include "Driver/UART.h"
#include "Driver/SYSTICK.h"
#include "Dashboard.h"
#include <stdio.h>

int main()
{
	UART6_Init();

	PrintBanner();

	while(1)
	{
		UART6_TxString("Hello World\n\r");
		delay_ms(1000);
	}
}
