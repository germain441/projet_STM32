#include "led.h"
#include "stm32f4xx.h"

uint8_t tableau [4] = {LED_VERTE, LED_ORANGE, LED_ROUGE, LED_BLEUE};

void chenillard(uint8_t sens){
    static int index = 3;

    if(sens)
    {
        index ++;
    }
    else index --;
    if(index == 4) index = 0;
    if(index == -1) index = 3;

    digitalWrite(GPIOD, 12, tableau[index]);
}