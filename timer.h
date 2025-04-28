#ifndef TIMER_H
#define TIMER_H

#include "stm32f4xx.h"

void Timer2_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
#endif /* TIMER_H */
