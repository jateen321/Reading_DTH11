#ifndef DHT11_H
#define DHT11_H

#include "stm32f4xx.h"

// Status codes
#define DHT11_ERROR_HANDSHAKE -1
#define DHT11_SUCCESS         1
#define DHT11_ERROR_CHECKSUM  2
#define DHT11_ERROR_TIMEOUT   3

typedef struct {
    uint8_t temperature;
    uint8_t humidity;
    GPIO_TypeDef* port;
    uint16_t pin;
} DHT11_Dev;

// Function prototypes
void DHT11_Init(DHT11_Dev* dev, GPIO_TypeDef* port, uint16_t pin);
int DHT11_Read(DHT11_Dev* dev);
int DHT11_start_handshake(DHT11_Dev* dev);
#endif /* DHT11_H */
