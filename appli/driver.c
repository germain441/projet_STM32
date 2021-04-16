#include "driver.h"
#include "led.h"


int mode_port(GPIO_TypeDef *port, uint8_t numBit){
    
    if(port->OTYPER & ((0x1) << numBit) && (port->PUPDR & ((0x3) << numBit*2) == 0)){
        return DISABLE;
    }
 

    if(!(port->MODER & ((0x1) << numBit*2))){
        if(port->PUPDR & ((0x1) << numBit*2))
            return INPUT_PULLUP;
        else if(port->PUPDR & ((0x2) << numBit*2))
            return INPUT_PULLDOWN;
        else 
            return INPUT;
        
    }
    else
        return OUTPUT;

}


int pinMode(GPIO_TypeDef *port, uint8_t numBit, uint8_t mode){

    if(numBit <0 || numBit >15)
        return ERREUR_NUM_BIT;


    switch(mode){

        case DISABLE:
            port->OTYPER |= ((0x1) << numBit);
            port->PUPDR &= ~((0x3) << numBit*2);
            return SUCCES;
        break;

        case INPUT:
            port->MODER &= ~((0x1) << (numBit *2));
            port->OTYPER &= ~((0x1) << numBit);
            return SUCCES;

        break;

        case OUTPUT:
            port->MODER |= ((0x1) << (numBit *2));
            port->OTYPER &= ~((0x1) << numBit);
            port->PUPDR &= ~((0x3) << numBit*2);
            return SUCCES;
        break;

        case INPUT_PULLDOWN:
            port->MODER &= ~((0x1) << (numBit *2));
            port->OTYPER &= ~((0x1) << numBit);
            port->PUPDR |= ((0x2) << (numBit *2));
            port->PUPDR &= ~((0x1) << (numBit *2));
            return SUCCES;
        break;

        case INPUT_PULLUP:
            port->MODER &= ~((0x1) << (numBit *2));
            port->OTYPER &= ~((0x1) << numBit);
            port->PUPDR |= ((0x1) << (numBit *2));
            port->PUPDR &= ~((0x2) << (numBit *2));
            return SUCCES;
        break;

        default:
            return ERREUR_CHOIX_MODE;
        break;
    }
    
}

int digitalWrite(GPIO_TypeDef *port, uint8_t numBit, uint8_t value){

    if(numBit <0 || numBit >15){
        return ERREUR_NUM_BIT;
    }

    if(mode_port(port, numBit) == OUTPUT){
        port->ODR |= value << numBit;
        port->ODR &= value << numBit;
        return SUCCES;
    }
    else{
        return ERREUR_MODE_PORT;
    }
}
            

int digitalRead(GPIO_TypeDef *port, uint8_t numBit, uint8_t *value){
    static int etat_precedent =0;
    if((numBit <0) || (numBit >15)){
        return ERREUR_NUM_BIT;
    }

    if(mode_port(port, numBit) == OUTPUT){
        return ERREUR_MODE_PORT;
    }
    else{
       
        //port->IDR &= (0x01 << numBit);
        *value = (port->IDR >> numBit);
        
        return SUCCES;
    }
}

int digitalToggle(GPIO_TypeDef *port, uint8_t numBit){
   
    if((numBit <0) || (numBit >15))
        return ERREUR_NUM_BIT;

    

    if(mode_port(port, numBit) != OUTPUT){
        return ERREUR_MODE_PORT;
    }
    else{
        int value;
        port->ODR &= (0x1 << numBit);
        value = port->ODR >> numBit;

        digitalWrite(port, numBit, !value);

        return SUCCES;
    }
}
