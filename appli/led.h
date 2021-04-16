#ifndef LED_H
#define LED_H

#include "stm32f4xx.h"

#define LED_ORANGE  2
#define LED_VERTE   1
#define LED_ROUGE   4
#define LED_BLEUE   8


//#define LED_ORANGE  0x0C
//#define LED_VERTE   0x0D
//#define LED_ROUGE   0x0E
//#define LED_BLEUE   0x0F

void chenillard(uint8_t mode);

#endif