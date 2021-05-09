#include "stm32f4xx.h"
#include "bouton.h"
#include "led.h"
#include "driver.h"



static uint8_t sens = 0;

static uint32_t tableau_freq[5] = {10500000, 21000000, 42000000, 63000000, 84000000};
static uint8_t index = 0;

void inititalisation(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 
     
    pinMode(GPIOD, 12, OUTPUT);
    pinMode(GPIOD, 13, OUTPUT);
    pinMode(GPIOD, 14, OUTPUT);
    pinMode(GPIOD, 15, OUTPUT);

    pinMode(GPIOA, 1, INPUT_PULLUP);


    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // enable the clock to GPIOD
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enable TIM2 clock
      
    NVIC->ISER[0] |= 1<< (TIM2_IRQn); // enable the TIM2 IRQ
     
    TIM2->PSC = 0x0; // no prescaler, timer counts up in sync with the peripheral clock
    TIM2->DIER |= TIM_DIER_UIE; // enable update interrupt
    TIM2->ARR = 2100000; // count to 1 (autoreload value 1)
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
    TIM2->EGR = 1; // trigger update event to reload timer registers


    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // enable TIM5 clock
    TIM5->DIER |= TIM_DIER_UIE; // enable update interrupt
    TIM5->PSC = 0x0; // no prescaler, timer counts up in sync with the peripheral clock
    TIM5->ARR = tableau_freq[0]; // count to 1 (autoreload value 1)
    TIM5->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
    TIM5->EGR = 1; // trigger update event to reload timer registers
}   


int main(void)
{
    
    inititalisation();
    while (1){
        if(TIM5->SR & TIM_SR_UIF){
            chenillard(sens);
            TIM5->SR = 0x0; 
        }
       
    }
          
}
void TIM2_IRQHandler(void) {
    // flash on update event
    // On passe ici toutes les 50ms
    static uint8_t compteur_seconde = 0;
    static uint8_t apres_appui =0;

    if(lire_bouton()){
        compteur_seconde++;
        apres_appui = 1;
    }
    else if(apres_appui){
        if(compteur_seconde <= 20)
            sens=!sens;
        else{
            index++;
            if(index == 5)
                index =0;
            TIM5->ARR = tableau_freq[index];
            TIM5->PSC = 0x0; // no prescaler, timer counts up in sync with the peripheral clock
            TIM5->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
            TIM5->EGR = 1; // trigger update event to reload timer registers
            TIM5->SR = 0x0; 
        }
        apres_appui=0;
        compteur_seconde =0;
    }
    
    
    TIM2->SR = 0x0; // reset the status register
}