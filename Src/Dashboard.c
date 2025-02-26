#include "Driver/UART.h"
#include <stdio.h>

void PrintBanner(float temp, float pressure, float lux, char *time)
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
	snprintf(buffer, sizeof(buffer), "|  TEMPERATURE: %.1f °C                     |\r\n", temp);			UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  PRESSURE:    %.1f hPa                    |\r\n", pressure);		UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  LIGHT LEVEL: %.1f lx                     |\r\n", lux);	    		UART6_TxString(buffer);
	UART6_TxString("+-------------------------------------------+\r\n");
	UART6_TxString(" ~ SENSORS TRACKING IN PROGRESS ~\r\n\r\n");
	UART6_TxString("     < Powered by FreeRTOS >\r\n");
	UART6_TxString("#############################################\r\n");
}





