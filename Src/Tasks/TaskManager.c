#include "Tasks/TaskManager.h"

SemaphoreHandle_t data_mutex;
SemaphoreHandle_t spi_mutex;

SensorData_t shared_sensor_data = {0};

void data_manager_init(void)
{
    data_mutex = xSemaphoreCreateMutex();
    spi_mutex = xSemaphoreCreateMutex();
}

void data_manager_update(SensorData_t new_data)
{
    if (xSemaphoreTake(data_mutex, portMAX_DELAY) == pdTRUE)
    {
        shared_sensor_data = new_data;
        xSemaphoreGive(data_mutex);
    }
}

void data_manager_get(SensorData_t *data)
{
    if (xSemaphoreTake(data_mutex, portMAX_DELAY) == pdTRUE)
    {
        *data = shared_sensor_data;
        xSemaphoreGive(data_mutex);
    }
}
