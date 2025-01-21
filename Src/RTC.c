#include "RTC.h"

void RTC_Init(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year)
{
    /* Enable clock access to Power and RTC */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    /* Enable access to backup domain */
    PWR->CR |= PWR_CR_DBP;

    /* Configure LSE as the RTC clock source */
    RCC->BDCR |= RCC_BDCR_RTCEN;        // Enable RTC
    RCC->BDCR &= ~RCC_BDCR_RTCSEL_Msk;  // Clear RTCSEL bits
    RCC->BDCR |= (0x01 << RCC_BDCR_RTCSEL_Pos);  // Select LSE as RTC clock source

    /* Reset RTC domain */
    RCC->BDCR |= RCC_BDCR_BDRST;
    RCC->BDCR &= ~RCC_BDCR_BDRST;

    /* Enter RTC Initialization Mode */
    RTC->ISR |= RTC_ISR_INIT;
    while (!(RTC->ISR & RTC_ISR_INITF));

    /* Configure prescalers */
    RTC->PRER = (127U << 16) | 255U;  // 1 Hz clock (LSE = 32.768 kHz)

    /* Set time */
    RTC->TR = ((hour / 10) << 20) | ((hour % 10) << 16) |
              ((minute / 10) << 12) | ((minute % 10) << 8) |
              ((second / 10) << 4) | (second % 10);

    /* Set date */
    RTC->DR = ((year / 10) << 20) | ((year % 10) << 16) |
              ((month / 10) << 12) | ((month % 10) << 8) |
              ((day / 10) << 4) | (day % 10);

    /* Exit Initialization Mode */
    RTC->ISR &= ~RTC_ISR_INIT;

    /* Enable write protection */
    RTC->WPR = 0xFF;
}


void RTC_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
    uint32_t tr = RTC->TR;

    *hour = ((tr >> 20) & 0x3) * 10 + ((tr >> 16) & 0xF);
    *minute = ((tr >> 12) & 0x7) * 10 + ((tr >> 8) & 0xF);
    *second = ((tr >> 4) & 0x7) * 10 + (tr & 0xF);
}

void RTC_GetDate(uint8_t *day, uint8_t *month, uint8_t *year)
{
    uint32_t dr = RTC->DR;

    *year = ((dr >> 20) & 0xF) * 10 + ((dr >> 16) & 0xF);
    *month = ((dr >> 12) & 0x1) * 10 + ((dr >> 8) & 0xF);
    *day = ((dr >> 4) & 0x3) * 10 + (dr & 0xF);
}
