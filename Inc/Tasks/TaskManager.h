#ifndef TASKS_TASKMANAGER_H_
#define TASKS_TASKMANAGER_H_

#include "FreeRTOS.h"
#include "semphr.h"
#include "stdint.h"

// Sensor Data Structure
typedef struct {
    float temperature;
    float pressure;
    float light_intensity;
    uint32_t rtc_timestamp;
} SensorData_t;

// Mutex for Sensor Data and SPI Bus
extern SemaphoreHandle_t data_mutex;
extern SemaphoreHandle_t spi_mutex;

// Shared Data Object
extern SensorData_t shared_sensor_data;

// Function Prototypes
void data_manager_init(void);
void data_manager_update(SensorData_t new_data);
void data_manager_get(SensorData_t *data);

#endif
