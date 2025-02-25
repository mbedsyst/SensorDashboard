#include "WriteFlash.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

void WriteFlashTask(void *argument)
{
    while (1)
    {

    }
}

void WriteFlashTask_Init(void)
{
    xTaskCreate(WriteFlashTask, "WriteFlashTask", 256, NULL, 2, NULL);
}
