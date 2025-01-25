#include "Driver/UART.h"

void PrintBanner(void)
{
	//char buffer[256];
	UART6_TxString(" _  ______  ______  ______  ______  ______  _____  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  _\n\r");
	UART6_TxString("|_||______||______||______||______||______||_____||______||______||______||______||______||______||______||______||______||______||______||______||______||______||______||______||_|\n\r");
	UART6_TxString("|_|                                                                                                                                                                               |_|\n\r");
	UART6_TxString("|_|	███████ ███████ ██     ██ ███████  ██████  ██   ██      ██████   █████  ██    ██  ██████  ███████     ████████ ███████ ██████  ██      ██ ██ ██     ██  █████  ██             |_|\n\r");
	UART6_TxString("|_|	██      ██      ████   ██ ██      ██    ██ ██   ██     ██       ██   ██ ██    ██ ██       ██             ██    ██      ██   ██ ████  ████ ██ ████   ██ ██   ██ ██             |_|\n\r");
	UART6_TxString("|_|	███████ █████   ██ ██  ██ ███████ ██    ██ ██████      ██   ███ ███████ ██    ██ ██   ███ █████          ██    █████   ██████  ██ ████ ██ ██ ██ ██  ██ ███████ ██             |_|\n\r");
	UART6_TxString("|_|	     ██ ██      ██  ██ ██      ██ ██    ██ ██   ██     ██    ██ ██   ██ ██    ██ ██    ██ ██             ██    ██      ██   ██ ██  ██  ██ ██ ██  ██ ██ ██   ██ ██             |_|\n\r");
	UART6_TxString("|_|	███████ ███████ ██   ████ ███████  ██████  ██   ██      ██████  ██   ██  ██████   ██████  ███████        ██    ███████ ██   ██ ██      ██ ██ ██   ████ ██   ██ ███████        |_|\n\r");
	UART6_TxString("|_| ______  ______  ______  ______  ______  _____  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  ______  _\n\r");
	UART6_TxString("|_||______||______||______||______||______||_____||______||______||______||______||______||______||______||______||______||______||______||______||______||______||______||______||_|\n\r");
	UART6_TxString("\n\n\n\r");
/*
	snprintf(buffer, sizeof(buffer), "+-------------------------------------------+\r\n");					UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  📅 TIME:        %s                      |\r\n", time);				UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  🌡   TEMPERATURE: %.1f °C                  |\r\n", temperature);		UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  🧭  PRESSURE:    %.1f hPa                 |\r\n", pressure);		UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  💡  LIGHT LEVEL: %.1f lx                  |\r\n", light_intensity);	UART6_TxString(buffer);
	UART6_TxString("+-------------------------------------------+\r\n");

	// Footer
	UART6_TxString("\r\n    ~ SENSORS TRACKING IN PROGRESS ~\r\n\r\n");
	UART6_TxString("  Footer Notes:\r\n");
	UART6_TxString("  * Powered by FreeRTOS.\r\n");
	UART6_TxString("  * Real-time data updated every 1 second.\r\n");
	UART6_TxString("  * Units: Temperature (Celsius), Pressure (hPa), Light (Lux).\r\n");
	UART6_TxString("#############################################\r\n");*/
}





