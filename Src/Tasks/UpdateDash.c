#include "UpdateDash.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Dashboard.h"

#include "Tasks/UpdateDash.h"

void UpdateDashTask(void *argument)
{
    SensorData_t sensor_data;
    char time_str[16];
    while (1)
    {
        xSemaphoreTake(dataMutex, portMAX_DELAY);
        sensor_data = shared_sensor_data;
        xSemaphoreGive(dataMutex);
        int hours = sensor_data.rtc_timestamp / 3600;
        int minutes = (sensor_data.rtc_timestamp % 3600) / 60;
        int seconds = sensor_data.rtc_timestamp % 60;
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", hours, minutes, seconds);
        PrintBanner(sensor_data.temperature, sensor_data.pressure, sensor_data.light_intensity, time_str);
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void UpdateDashTask_Init(void)
{
    xTaskCreate(UpdateDashTask, "UpdateDashTask", 256, NULL, 2, NULL);
}
