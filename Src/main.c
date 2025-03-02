#include "main.h"

int main(void)
{
	TaskManager_Init();
	ConfigSystemTask_Init();
	ReadSensorTask_Init();
	UpdateDashTask_Init();
	WriteFlashTask_Init();

	vTaskStartScheduler();

	while (1);
}
