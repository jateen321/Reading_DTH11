#include "dht11.h"
#include "timer.h"
#include "stm32f4xx.h"
#include "uart.h"
#include <stdio.h>

/**
 * Initialize GPIO for DHT11 sensor communication.
 */
void DHT11_Init(DHT11_Dev* dev, GPIO_TypeDef* port, uint16_t pin) {
    dev->port = port;
    dev->pin = pin;
    
    
    if (dev->port == GPIOA) {
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		} else if (dev->port == GPIOB) {
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		} else if (dev->port == GPIOC) {
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		} else if (dev->port == GPIOD) {
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
		}
		Delay_us(2);
    // Set pin as output initially
    dev->port->MODER &= ~(0x3 << (pin * 2));
    dev->port->MODER |= (0x1 << (pin * 2));
    //dev->port->PUPDR |= (0x1 << (pin * 2));  // Enable pull-up
		dev->port->OTYPER |= (0x1 << (pin ));
		dev->port->ODR |= (1 << dev->pin);
}

int DHT11_start_handshake(DHT11_Dev* dev){
		
    UART3_SendString("Starting DHT11 read process...\r\n");

    // Send Start signal: Pull LOW for 18ms
    dev->port->ODR &= ~(1 << dev->pin);
    Delay_ms(20);
	
		//Pull the Data line high
    dev->port->ODR |= (1 << dev->pin);
    Delay_us(30);  

    // Switch pin to input mode
    dev->port->MODER &= ~(0x3 << (dev->pin * 2));
	
		dev->port->PUPDR &= ~(0x3 << (dev->pin * 2));
    dev->port->PUPDR |= (0x1 << (dev->pin * 2));
    UART3_SendString("GPIO mode switched to input.\r\n");
		
		// Wait for DHT11  Response (DTH11 pulls low 80 us and high for next 80 us
	
		uint32_t timeout = 1000; // timeout in us
		while(dev->port->IDR != 0){
			if(timeout == 0) return -1;
			Delay_us(1);
			timeout -- ;			
		}
		
		timeout = 1000; // timeout in us
		while(dev->port->IDR != 1){
			if(timeout == 0) return -1;
			Delay_us(1);
			timeout -- ;
		}
		
		timeout = 1000; // timeout in us
		while(dev->port->IDR != 0){
			if(timeout == 0) return -1;
			Delay_us(1);
			timeout -- ;
		}
		
		return 0;
		
}
/**
 * Read data from DHT11 sensor.
 */


int DHT11_Read(DHT11_Dev* dev) {
		int statusHand = DHT11_start_handshake(dev);
		if(statusHand == -1){
			UART3_SendString("Error During handshake\r\n");
		}
		else{
			UART3_SendString("Start correct.\r\n");
		}
		
		uint8_t i ,j ;
		uint8_t byte = 0;
		uint32_t timeout;
		uint32_t high_pulse_dur ;
		uint8_t raw_data[5];
		for(int i =0 ; i< 5 ; i++){
			byte = 0;
			for(int j=0 ; j< 8 ; j++){
				timeout = 100;
				while(dev->port->IDR != 1){
					if(timeout == 0) return -1;
					Delay_us(1);
					timeout--;
				}
				high_pulse_dur =0;
				timeout =100;
				while(dev->port->IDR  == 0 ){
					high_pulse_dur ++;
					if(timeout == 0) return -1;
					Delay_us(1);
					timeout -- ;
				}
				
				if(high_pulse_dur > 15  && high_pulse_dur < 45){
					byte <<= 1;
				} else if(high_pulse_dur > 45 && high_pulse_dur < 90) {
					byte <<= 1;
					byte |= 1;
				} else {
					return -1;
				}
			}
			raw_data[i] = byte;
		}
		
		uint8_t checksum =raw_data[0]+ raw_data[1] + raw_data[2] +raw_data[3];
		if(checksum == raw_data[4]){
			dev->humidity = raw_data[0];
			dev->temperature = raw_data[2];
			return 0;
		}
		else{
			return -2;
		}
			
    // Check sensor response
    
}
