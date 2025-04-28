#ifndef UART_H
#define UART_H

void UART3_Init(void);
void UART3_SendChar(char c);
void UART3_SendString(char *str);
char UART3_ReceiveChar(void);

#endif /* UART_H */
