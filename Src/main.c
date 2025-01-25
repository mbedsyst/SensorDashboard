#include "Driver/RTC.h"
#include "Driver/VCOM.h"
#include "Driver/SYSTICK.h"
#include <stdio.h>

int main()
{
	UART2_Init();

	RTC_Time X;
	X.am_pm = 1;
	X.hour = 6;
	X.min = 00;
	X.seconds = 0;

	RTC_Date Y;
	Y.day = 18;
	Y.month = 10;
	Y.year = 2021;
	Y.week_day = Monday;

	RTC_Init();
	RTC_Set_Date(&Y);
	RTC_Set_Time(&X, Time_Format_12Hour);
	RTC_Start();


	while(1)
	{
		RTC_Get_Date(&Y);
		RTC_Get_Time(&X);
		printf("Date: %d/%d/%d \r\n", Y.day, Y.month, Y.year);
		printf("Time: %d:%d:%d \r\n", X.hour, X.min, X.seconds);
		delay_ms(1000);
	}
}
