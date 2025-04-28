#include "stm32f4xx.h"
#include "uart.h"

void UART3_Init(void) {
    RCC->APB1ENR |= (1 << 18);
    RCC->AHB1ENR |= (1 << 3);
    
    GPIOD->MODER &= ~(0x3 << 16);
    GPIOD->MODER |= (0x2 << 16);  // PD8 AF
    GPIOD->MODER &= ~(0x3 << 18);
    GPIOD->MODER |= (0x2 << 18);  // PD9 AFs
    
    GPIOD->AFR[1] |= (0x7 << 0) | (0x7 << 4);
    USART3->BRR = 0x683;
    USART3->CR1 = (1 << 13) | (1 << 2) | (1 << 3);
	  
}

void UART3_SendChar(char c) {
    while (!(USART3->SR & (1 << 7)));
    USART3->DR = c;
}

void UART3_SendString(char *str) {
    while (*str) {
        UART3_SendChar(*str++);
    }
}

char UART3_ReceiveChar(void) {
    while (!(USART3->SR & (1 << 5)));
    return USART3->DR;
}
