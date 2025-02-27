#include "WriteFlash.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Tasks/WriteFlash.h"

void WriteFlashTask(void *argument)
{
	SensorData_t localData;  // Local copy of the shared data
	uint8_t flashBuffer[64]; // Buffer to hold formatted data before writing
	uint32_t flashPage = 0;  // Start page in flash memory (modify as needed)

	while (1)
	{
		xSemaphoreTake(dataMutex, portMAX_DELAY);
		localData = sharedData;
		xSemaphoreGive(dataMutex);
		snprintf((char *)flashBuffer, sizeof(flashBuffer),
				 "T:%.1f P:%.1f L:%.1f %02d:%02d:%02d",
				 localData.temperature, localData.pressure, localData.lux,
				 localData.time.hours, localData.time.minutes, localData.time.seconds);
		xSemaphoreTake(spiMutex, portMAX_DELAY);
		W25Q_WriteData(flashPage, 0, sizeof(flashBuffer), flashBuffer);
		xSemaphoreGive(spiMutex);
		flashPage++;
		vTaskDelay(pdMS_TO_TICKS(30000));
	}
}

void WriteFlashTask_Init(void)
{
    xTaskCreate(WriteFlashTask, "WriteFlashTask", 256, NULL, 2, NULL);
}
