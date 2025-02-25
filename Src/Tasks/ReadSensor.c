#include "ReadSensor.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void ReadSensorTask(void *argument)
{
    while (1)
    {

    }
}

void SensorTask_Init(void)
{
    xTaskCreate(ReadSensorTask, "ReadSensorTask", 256, NULL, 2, NULL);
}
