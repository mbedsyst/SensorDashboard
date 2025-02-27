#include "ReadSensor.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Tasks/ReadSensor.h"

void ReadSensorTask(void *argument)
{
    SensorData_t sensor_data;
    RTC_Time rtc_time;

    while (1)
    {
        sensor_data.light_intensity = Read_Light_Sensor();
        xSemaphoreTake(spiMutex, portMAX_DELAY);
        sensor_data.temperature = BMP280_Read_Temperature();
        sensor_data.pressure = BMP280_Read_Pressure();
        xSemaphoreGive(spiMutex);
        RTC_Get_Time(&rtc_time);
        sensor_data.rtc_timestamp = (rtc_time.hour * 3600) + (rtc_time.min * 60) + rtc_time.seconds;
        xSemaphoreTake(dataMutex, portMAX_DELAY);
        shared_sensor_data = sensor_data;
        xSemaphoreGive(dataMutex);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void ReadSensorTask_Init(void)
{
    xTaskCreate(ReadSensorTask, "ReadSensorTask", 256, NULL, 2, NULL);
}
