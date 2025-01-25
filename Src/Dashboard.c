#include "Driver/UART.h"
#include <stdio.h>

void PrintBanner(void)
{
	char buffer[256];

	UART6_TxString("                                                                                                                                                                       \n\r");
	UART6_TxString("███████ ███████ ██     ██ ███████  ██████  ██████       ██████   █████  ██    ██  ██████  ███████     ████████ ███████ ██████  ██      ██ ██ ██     ██  █████  ██      \n\r");
	UART6_TxString("██      ██      ████   ██ ██      ██    ██ ██   ██     ██       ██   ██ ██    ██ ██       ██             ██    ██      ██   ██ ████  ████ ██ ████   ██ ██   ██ ██      \n\r");
	UART6_TxString("███████ █████   ██ ██  ██ ███████ ██    ██ ██████      ██   ███ ███████ ██    ██ ██   ███ █████          ██    █████   ██████  ██ ████ ██ ██ ██ ██  ██ ███████ ██      \n\r");
	UART6_TxString("     ██ ██      ██  ██ ██      ██ ██    ██ ██   ██     ██    ██ ██   ██ ██    ██ ██    ██ ██             ██    ██      ██   ██ ██  ██  ██ ██ ██  ██ ██ ██   ██ ██      \n\r");
	UART6_TxString("███████ ███████ ██   ████ ███████  ██████  ██   ██      ██████  ██   ██  ██████   ██████  ███████        ██    ███████ ██   ██ ██      ██ ██ ██   ████ ██   ██ ███████ \n\r");

	UART6_TxString("\n\n\n\r");

	snprintf(buffer, sizeof(buffer), "+-------------------------------------------+\r\n");					UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  TIME:        %s                          |\r\n", "12:32:47\0");	UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  TEMPERATURE: %.1f °C                     |\r\n", 32.78);			UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  PRESSURE:    %.1f hPa                    |\r\n", 76.587);			UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  LIGHT LEVEL: %.1f lx                     |\r\n", 789.25);	    	UART6_TxString(buffer);
	UART6_TxString("+-------------------------------------------+\r\n");
	UART6_TxString(" ~ SENSORS TRACKING IN PROGRESS ~\r\n\r\n");
	UART6_TxString("     < Powered by FreeRTOS >\r\n");
	UART6_TxString("#############################################\r\n");
}





