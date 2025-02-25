#include "UpdateDash.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

void UpdateDashTask(void *argument)
{
    while (1)
    {

    }
}

void UpdateDashTask_Init(void)
{
    xTaskCreate(UpdateDashTask, "UpdateDashTask", 256, NULL, 2, NULL);
}
