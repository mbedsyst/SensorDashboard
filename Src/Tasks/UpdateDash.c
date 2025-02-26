#include "UpdateDash.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Dashboard.h"

#include "Tasks/UpdateDash.h"

void UpdateDashTask(void *argument)
{
    while (1)
    {
    	// Lock Data Mutex
    	// Copy Data Structure
    	// Unlock Mutex
    	// Call PrintBanner()
    }
}

void UpdateDashTask_Init(void)
{
    xTaskCreate(UpdateDashTask, "UpdateDashTask", 256, NULL, 2, NULL);
}
