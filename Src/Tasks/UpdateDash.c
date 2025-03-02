#include "Tasks/UpdateDash.h"
#include "Tasks/TaskManager.h"

#include "Driver/UART.h"
#include "Driver/RTC.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdio.h>
#include <string.h>

extern SemaphoreHandle_t dataMutex;
extern SensorData_t shared_sensor_data;

static void PrintBanner(float temp, float pressure, float lux, char *time)
{
	char buffer[256];

	UART6_TxString("                                                                                                                                                                       \n\r");
	UART6_TxString("███████ ███████ ██     ██ ███████  ██████  ██████       ██████   █████  ██    ██  ██████  ███████     ████████ ███████ ██████  ██      ██ ██ ██     ██  █████  ██      \n\r");
	UART6_TxString("██      ██      ████   ██ ██      ██    ██ ██   ██     ██       ██   ██ ██    ██ ██       ██             ██    ██      ██   ██ ████  ████ ██ ████   ██ ██   ██ ██      \n\r");
	UART6_TxString("███████ █████   ██ ██  ██ ███████ ██    ██ ██████      ██   ███ ███████ ██    ██ ██   ███ █████          ██    █████   ██████  ██ ████ ██ ██ ██ ██  ██ ███████ ██      \n\r");
	UART6_TxString("     ██ ██      ██  ██ ██      ██ ██    ██ ██   ██     ██    ██ ██   ██ ██    ██ ██    ██ ██             ██    ██      ██   ██ ██  ██  ██ ██ ██  ██ ██ ██   ██ ██      \n\r");
	UART6_TxString("███████ ███████ ██   ████ ███████  ██████  ██   ██      ██████  ██   ██  ██████   ██████  ███████        ██    ███████ ██   ██ ██      ██ ██ ██   ████ ██   ██ ███████ \n\r");

	UART6_TxString("\n\n\n\r");

	snprintf(buffer, sizeof(buffer), "+-------------------------------------------+\r\n");					UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  TIME:        %s                          |\r\n", time);	UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  TEMPERATURE: %.1f °C                     |\r\n", temp);			UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  PRESSURE:    %.1f hPa                    |\r\n", pressure);		UART6_TxString(buffer);
	snprintf(buffer, sizeof(buffer), "|  LIGHT LEVEL: %.1f lx                     |\r\n", lux);	    		UART6_TxString(buffer);
	UART6_TxString("+-------------------------------------------+\r\n");
	UART6_TxString(" ~ SENSORS TRACKING IN PROGRESS ~\r\n\r\n");
	UART6_TxString("     < Powered by FreeRTOS >\r\n");
	UART6_TxString("#############################################\r\n");
}


void UpdateDashTask(void *argument)
{
    SensorData_t sensor_data;
    char time_str[16];

    while (1)
    {
        xSemaphoreTake(dataMutex, portMAX_DELAY);
        sensor_data = shared_sensor_data;
        xSemaphoreGive(dataMutex);

        // Directly access the struct members
        int hours   = sensor_data.rtc_timestamp.hour;
        int minutes = sensor_data.rtc_timestamp.minute;
        int seconds = sensor_data.rtc_timestamp.second;

        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", hours, minutes, seconds);

        PrintBanner(sensor_data.temperature, sensor_data.pressure, sensor_data.light_intensity, time_str);

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}


void UpdateDashTask_Init(void)
{
    BaseType_t result;
    result = xTaskCreate(UpdateDashTask, "UpdateDashTask", 256, NULL, 2, NULL);
    if (result != pdPASS)
    {
        printf("Error: Failed to create UpdateDashTask!\n\r");
    }
}
