#include "stm32f4xx.h"
#include "UART.h"
#include "RTC.h"
#include <stdio.h>

void clear_screen_UART6(void)
{
    UART6_TxString("\033[2J"); // ANSI escape code to clear the screen
    UART6_TxString("\033[H"); // ANSI escape code to move cursor to (0,0)
}

int main(void)
{
    RTC_Time currentTime;
    RTC_Date currentDate;

    // Initialize peripherals
    UART6_Init();
    RTC_Init();

    // Set the current time and date (modify this as per the current time/date)
    currentTime.hour = 10; // Example: 10:30:45 AM
    currentTime.min = 30;
    currentTime.seconds = 45;
    currentTime.am_pm = 0; // 0 for AM, 1 for PM

    currentDate.day = 21;  // Example: 21st of January, 2025 (Tuesday)
    currentDate.month = 1;
    currentDate.year = 2025;
    currentDate.week_day = 2; // 2 corresponds to Tuesday

    RTC_SetTime(&currentTime, true); // Set time in 24-hour format
    RTC_SetDate(&currentDate);      // Set date

    RTC_Start();

    while(1)
    {
		// Retrieve and display time on UART6
		RTC_GetTime(&currentTime);

		char buffer[50];
		snprintf(buffer, sizeof(buffer), "Time: %02d:%02d:%02d\r\n",
				 currentTime.hour, currentTime.min, currentTime.seconds);
		UART6_TxString(buffer);
    }
}
