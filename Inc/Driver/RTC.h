#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"

typedef struct
{
	int day;
	int month;
	int year;
	int week_day;
} RTC_Date;

typedef struct
{
	int am_pm;
	int hour;
	int min;
	int seconds;
} RTC_Time;

// Function Prototypes
void RTC_Init(void);
void RTC_SetTime(RTC_Time *T, bool time_format);
void RTC_SetDate(RTC_Date *D);
void RTC_GetTime(RTC_Time *T);
void RTC_GetDate(RTC_Date *D);
void RTC_Start(void);


#endif
