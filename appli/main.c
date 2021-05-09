#include "stm32f4xx.h"
#include "bouton.h"
#include "led.h"
#include "driver.h"



static uint8_t sens = 0;

static uint32_t tableau_freq[5] = {1050000, 2100000, 4200000, 6300000, 8400000};
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
    TIM2->ARR = 210000; // count to 1 (autoreload value 1)
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
    TIM2->EGR = 1; // trigger update event to reload timer registers


    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // enable TIM3 clock
    NVIC->ISER[0] |= 1<< (TIM3_IRQn); // enable the TIM2 IRQ
     
    TIM3->PSC = 0x0; // no prescaler, timer counts up in sync with the peripheral clock
    TIM3->DIER |= TIM_DIER_UIE; // enable update interrupt
    TIM3->ARR = 50000000; // count to 1 (autoreload value 1)
    TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
    TIM3->EGR = 1; // trigger update event to reload timer registers
}   


int main(void)
{
    
    inititalisation();
    while (1){}
          
}
void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF){
        digitalWrite(GPIOD, 12, LED_VERTE);
       // chenillard(sens);
    }
}
    
void TIM2_IRQHandler(void) {
    // flash on update event
    // On passe ici toutes les 50ms
    static uint8_t compteur_seconde = 8;
    if (TIM2->SR & TIM_SR_UIF){
        if(lire_bouton()){
            compteur_seconde++;
        }
        else{
            if(compteur_seconde <= 20)
                sens=!sens;
            else{
                index++;
                if(index == 5)
                    index =0;
                TIM3->ARR = tableau_freq[index];
            }
        }
        compteur_seconde =0;
    }
    TIM2->SR = 0x0; // reset the status register
}