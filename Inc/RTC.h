#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>
#include "stm32f4xx.h"

// Function Prototypes
void RTC_Init(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year);
void RTC_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second);
void RTC_GetDate(uint8_t *day, uint8_t *month, uint8_t *year);

#endif
