#include "Tasks/ReadSensor.h"
#include "Tasks/TaskManager.h"

#include "Driver/RTC.h"
#include "Library/BH1750.h"
#include "Library/BMP280.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <stdio.h>

extern SemaphoreHandle_t spiMutex;
extern SemaphoreHandle_t dataMutex;

extern SensorData_t shared_sensor_data;

void ReadSensorTask(void *argument)
{
    SensorData_t sensor_data;
    RTC_Time rtc_time;
    int32_t rawTemperature, rawPressure;

    while (1)
    {
        sensor_data.light_intensity = BH1750_ReadLightLevel();

        xSemaphoreTake(spiMutex, portMAX_DELAY);
        taskENTER_CRITICAL();
        BMP280_ReadRawData(&rawTemperature, &rawPressure);
        taskEXIT_CRITICAL();
        xSemaphoreGive(spiMutex);

        sensor_data.temperature = rawTemperature;
        sensor_data.pressure = rawPressure;

        // Read RTC time and update the struct correctly
        RTC_Get_Time(&rtc_time);
        sensor_data.rtc_timestamp.hour = rtc_time.hour;
        sensor_data.rtc_timestamp.minute = rtc_time.min;
        sensor_data.rtc_timestamp.second = rtc_time.seconds;

        xSemaphoreTake(dataMutex, portMAX_DELAY);
        shared_sensor_data = sensor_data;
        xSemaphoreGive(dataMutex);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void ReadSensorTask_Init(void)
{
    BaseType_t result;
    result = xTaskCreate(ReadSensorTask, "ReadSensorTask", 512, NULL, 2, NULL);
    if (result != pdPASS)
    {
        printf("ReadSensorTask creation failed!\n\r");
    }
}
