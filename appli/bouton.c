
#include "stm32f4xx.h"
#include "bouton.h"
#include "led.h"


int lire_bouton(void){
   
    static int etat_precedent = 1;
    int res = 0;

    volatile int i;
    int value;

    digitalRead(GPIOA,  0, &value);
    value = (value & 0x0001);

    if((etat_precedent != value) && value){
        res = 1;
    }
    
    else{
        res = 0;
        
    }

    if(1 && (etat_precedent != value)) for(i = 0; i<1000000; i++);
    etat_precedent = value;

    return res;
}
