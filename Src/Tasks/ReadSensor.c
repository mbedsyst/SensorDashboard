#include "ReadSensor.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Tasks/ReadSensor.h"

void ReadSensorTask(void *argument)
{
    while (1)
    {
		// Read Light Intensity
    	// Lock SPI Mutex
    	// Temperature and Pressure
    	// Unlock SPI Mutex
		// Read RTC Value
		// Lock Data Mutex
		// Update the Data Structure
    	// Unlock Data Mutex
    }
}

void ReadSensorTask_Init(void)
{
    xTaskCreate(ReadSensorTask, "ReadSensorTask", 256, NULL, 2, NULL);
}
