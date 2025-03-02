#include "Tasks/ConfigSystem.h"

#include "Driver/UART.h"
#include "Driver/VCOM.h"
#include "Driver/SPI.h"
#include "Driver/I2C.h"
#include "Driver/RTC.h"
#include "Library/BH1750.h"
#include "Library/BMP280.h"
#include "Library/W25Qxx.h"

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

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

    printf("System Initialized Successfully\n\r");

    printf("Deleting ConfigSystem Task\n\r");
    vTaskDelete(NULL);
}

void ConfigSystemTask_Init(void)
{
    BaseType_t result;
    result = xTaskCreate(ConfigSystemTask, "ConfigSystemTask", 256, NULL, configMAX_PRIORITIES - 1, NULL);
    if (result != pdPASS)
    {
        printf("Error: Failed to create ConfigSystemTask!\n\r");
    }
}
