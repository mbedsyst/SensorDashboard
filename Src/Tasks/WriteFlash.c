#include "WriteFlash.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#include "Tasks/WriteFlash.h"

void WriteFlashTask(void *argument)
{
    while (1)
    {
    	// Lock Data Mutex
    	// Copy Data Structure
    	// Unlock Data Mutex
    	// Prepare Data to Write
    	// Lock SPI Mutex
    	// Write Data to Flash
    	// Unlock SPI Mutex
    }
}

void WriteFlashTask_Init(void)
{
    xTaskCreate(WriteFlashTask, "WriteFlashTask", 256, NULL, 2, NULL);
}
