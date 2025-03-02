#include "Tasks/WriteFlash.h"
#include "Tasks/TaskManager.h"
#include "Library/W25Qxx.h"

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include <stdio.h>

void WriteFlashTask(void *argument)
{
    SensorData_t local_data;   // Local copy of the shared data
    uint8_t flash_buffer[64];  // Buffer to hold formatted data before writing
    static uint32_t flash_page = 0;  // Start page in flash memory

    while (1)
    {
        // Take mutex to access shared data
        xSemaphoreTake(data_mutex, portMAX_DELAY);
        local_data = shared_sensor_data;
        xSemaphoreGive(data_mutex);

        // Format data into buffer
        snprintf((char *)flash_buffer, sizeof(flash_buffer),
                 "T:%.1f P:%.1f L:%d %02d:%02d:%02d",
                 local_data.temperature,
                 local_data.pressure,
                 local_data.light_intensity,  // Fixed field name
                 local_data.rtc_timestamp.hour,   // Fixed field name
                 local_data.rtc_timestamp.minute,
                 local_data.rtc_timestamp.second);

        // Take SPI mutex before writing to flash
        xSemaphoreTake(spi_mutex, portMAX_DELAY);
        taskENTER_CRITICAL();
        W25Q_WriteData(flash_page, 0, sizeof(flash_buffer), flash_buffer);
        taskEXIT_CRITICAL();
        xSemaphoreGive(spi_mutex);

        // Increment flash page
        flash_page++;

        // Delay before next write
        vTaskDelay(pdMS_TO_TICKS(30000));
    }
}

void WriteFlashTask_Init(void)
{
    BaseType_t result;
    result = xTaskCreate(WriteFlashTask, "WriteFlashTask", 256, NULL, 2, NULL);
    if (result != pdPASS)
    {
    	printf("Error: Failed to create UpdateDashTask!\n\r");
    }
}
