#include "stm32f4xx.h"
#include "dht11.h"
#include "uart.h"
#include <stdio.h>
#include "timer.h"

int main(void) {
    DHT11_Dev dht11;
    dht11.port = GPIOB;
    dht11.pin = 6;

    UART3_Init();
    Timer2_Init();
    DHT11_Init(&dht11, GPIOB, 6);
	/*
		 while (1) {
        UART3_SendString("Hello, STM32F4 UART working!\r\n");
			Delay_us(2000);// Delay 1 second
    }
	*/
    while (1) {
				UART3_SendString("Hello, STM32F4 UART working!\r\n");
				//Delay_ms(1000);// Delay 1 second
				
        int status = DHT11_Read(&dht11);
				
				//UART3_SendString(" Sensor no error\r\n");
        if (status == DHT11_SUCCESS) {
            char buf[50];
            sprintf(buf, "Temp: %dC, Hum: %d%%\r\n", dht11.temperature, dht11.humidity);
            UART3_SendString(buf);
        } else {
            UART3_SendString("Sensor error\r\n");
        }

        Delay_us(2000);  // Replace HAL_Delay

    }
}
