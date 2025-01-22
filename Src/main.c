#include "Driver/UART.h"
#include "Driver/SYSTICK.h"
int main(void)
{
	char *msg = "Hello World\n\r";
	UART6_Init();

	while(1)
	{
		UART6_TxString(msg);
		delay_ms(1000);

	}
}
