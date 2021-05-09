
#include "stm32f4xx.h"
#include "bouton.h"
#include "led.h"

int8_t debut_appui = 0;


int lire_bouton(void){
   
    static int etat_precedent = 1;
    int res = 0;

    volatile int i;
    int value;

    digitalRead(GPIOA,  0, &value);
    value = (value & 0x0001);

    if(value == 1){
        res = 1;
    }
    else
        res =0;

/*
    if((etat_precedent != value) && value){
      res = 1;
    }
    
    else{
        res = 0;
        
    }

    etat_precedent = value;*/

    return res;
}
