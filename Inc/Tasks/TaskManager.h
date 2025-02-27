#ifndef TASKS_TASKMANAGER_H_
#define TASKS_TASKMANAGER_H_

#include "FreeRTOS.h"
#include "semphr.h"
#include "stdint.h"

// Sensor Data Structure
typedef struct
{
    float temperature;      // In °C
    float pressure;         // In hPa
    float light_intensity;  // In Lux

    struct
	{
        uint16_t year;      // Full Year (e.g., 2025)
        uint8_t month;      // 1-12
        uint8_t day;        // 1-31
        uint8_t hour;       // 0-23
        uint8_t minute;     // 0-59
        uint8_t second;     // 0-59
    } rtc_timestamp;        // RTC Timestamp
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
