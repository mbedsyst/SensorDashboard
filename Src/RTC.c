#include "RTC.h"
#include "UART.h"

void RTC_Init(void)
{
	PWR->CR |= PWR_CR_DBP;
	while (!(PWR->CR & PWR_CR_DBP));
	RCC->CFGR |= (16<<16);
	RCC->BDCR |= RCC_BDCR_RTCSEL;
	RCC->BDCR |= RCC_BDCR_RTCEN;
	RTC->WPR |= 0xCA;
	RTC->WPR |= 0x53;
	RTC->ISR |= RTC_ISR_INIT;
	while(!(RTC->ISR & RTC_ISR_INITF));
	RTC->PRER |= 0x00000000;
	RTC->PRER |= (0x7C<<16);
	RTC->PRER |= (0x1F3F<<0);
}

void RTC_Start(void)
{
	RTC->CR |= RTC_CR_FMT | RTC_CR_TSE;
	RTC->ISR &= ~RTC_ISR_INIT;
	RTC->WPR &= 0x55;
	PWR->CR &= ~PWR_CR_DBP;
}


void RTC_SetDate(RTC_Date *D)
{
	int yt, yu, wd, mt, mu, dt, du;
	uint32_t d;
	D->year = D->year - 2000;
	yt = D->year/10;
	yu = D->year%10;
	wd = D->week_day;
	mt = D->month/10;
	mu = D->month%10;
	dt = D->day/10;
	du = D->day%10;
	d = (uint32_t)((yt<<20) | (yu<<16) | (wd<<13) | (mt<<12) | (mu<<8) | (dt<<4) | (du<<0));
	RTC->DR = d;
}

void RTC_SetTime(RTC_Time *T, bool time_format)
{
	int ht, hu, mt, mu, st, su;
	bool format;
	uint32_t t;
	format = time_format;
	ht = T->hour/10;
	hu = T->hour%10;
	mt = T->min/10;
	mu = T->min%10;
	st = T->seconds/10;
	su = T->seconds%10;
	t = (uint32_t)((format<<22) | (ht<<20) | (hu<<16) | (mt<<12) | (mu<<8) | (st<<4) | (su<<0));
	RTC->TR = t;
}

void RTC_GetDate(RTC_Date *D)
{
	uint32_t d;
	int weekday, date_tens, date_units, month_tens, month_units, year_tens, year_units, date, month, year;

	d = RTC->DR;

	weekday     = (d & 0xE000)>>13;
	year_tens   = (d & 0xF00000)>>20;
	year_units  = (d & 0xF0000)>>16;
	month_tens  = (d & 0x1000)>>12;
	month_units = (d & 0xF00)>>8;
	date_tens   = (d & 0x30)>>4;
	date_units  = (d & 0xF)>>0;

	year = 2000 + (year_tens * 10) + year_units;
	month = (month_tens * 10) + month_units;
	date = (date_tens * 10) + date_units;

	D->year = year;
	D->month = month;
	D->day = date;
	D->week_day = weekday;
}

void RTC_GetTime(RTC_Time *T)
{
	uint32_t t;
	int format, hour_tens, hour_units, min_tens, min_units, sec_tens, sec_units, hour, min, sec;

	t = RTC->TR;

	format     = (t & 0xE000)>>22;
	hour_tens  = (t & 0x300000)>>20;
	hour_units = (t & 0xF0000)>>16;
	min_tens   = (t & 0x7000)>>12;
	min_units  = (t & 0xF00)>>8;
	sec_tens   = (t & 0x30)>>4;
	sec_units  = (t & 0xF)>>0;

	hour = (hour_tens * 10) + hour_units;
	min = (min_tens * 10) + min_units;
	sec = (sec_tens * 10) + sec_units;

	T->hour = hour;
	T->min = min;
	T->seconds = sec;
	T->am_pm = format;
}


