#ifndef DRIVER_H
#define DRIVER_H
#include "stm32f4xx.h"

#define DISABLE         0
#define INPUT           1
#define OUTPUT          2 
#define INPUT_PULLUP    3
#define INPUT_PULLDOWN  4

#define ERREUR_NUM_BIT      5
#define ERREUR_MODE_PORT    6
#define ERREUR_CHOIX_MODE   7
#define ERREUR_VALUE_WRITE  8
#define SUCCES              9

int pinMode(GPIO_TypeDef *port, uint8_t numBit, uint8_t mode);
int digitalWrite(GPIO_TypeDef *port, uint8_t numBit, uint8_t value);
int digitalToggle(GPIO_TypeDef *port, uint8_t numBit);
int digitalRead(GPIO_TypeDef *port, uint8_t numBit, uint8_t *value);

#endif