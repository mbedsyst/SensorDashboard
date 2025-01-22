#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

void UART6_Init(void);
void UART6_TxChar(char ch);
void UART6_TxString(char *str);

#endif

