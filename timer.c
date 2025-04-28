#include "timer.h"
void Timer2_Init(void) {
    RCC->APB1ENR |= (1 << 0);  // Enable TIM2 clock
    TIM2->PSC = 16 -1 ;        // Prescaler (adjust for STM32F4)
	// CK_CNT = 1 MHz
    TIM2->ARR = 0xFFFFFFFF;        // Max count value
    TIM2->CR1 |= TIM_CR1_CEN;  // Enable TIM2

}

void Delay_us(uint32_t us) {
    TIM2->CNT = 0;
    while (TIM2->CNT < us);  // Let timer count directly
	
}
void Delay_ms(uint32_t ms) {
    TIM2->CNT = 0;
    while (TIM2->CNT < 1000*ms);  // Let timer count directly
}
