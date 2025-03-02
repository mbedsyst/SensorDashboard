#include "Tasks/TaskManager.h"

SemaphoreHandle_t data_mutex;
SemaphoreHandle_t spi_mutex;

SensorData_t shared_sensor_data = {0};

void data_manager_init(void)
{
    data_mutex = xSemaphoreCreateMutex();
    spi_mutex = xSemaphoreCreateMutex();
}
