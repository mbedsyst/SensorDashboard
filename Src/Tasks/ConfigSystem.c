#include "Tasks/ConfigSystem.h"

#include "Driver/UART.h"
#include "Driver/VCOM.h"
#include "Driver/SPI.h"
#include "Driver/I2C.h"
#include "Driver/RTC.h"
#include "Library/BH1750.h"
#include "Library/BMP280.h"
#include "Library/W25Qxx.h"

void ConfigSystemTask(void *argument)
{
	UART2_Init();
	UART6_Init();
	SPI2_Init();
	I2C1_Init();
	RTC_Init();
	BH1750_Init();
	BMP280_Init();
	W25Q_Init();
	// ToDo Print VCOM Terminal messages
}

void ConfigSystemTask_Init(void)
{
    xTaskCreate(ConfigSystemTask, "ConfigSystemTask", 256, NULL, 2, NULL);
}


