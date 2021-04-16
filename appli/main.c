/*#include "stm32f4xx.h"
#include "bouton.h"
#include "led.h"
#include "driver.h"


void inititalisation(){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 
     
    pinMode(GPIOD, 12, OUTPUT);
    pinMode(GPIOD, 13, OUTPUT);
    pinMode(GPIOD, 14, OUTPUT);
    pinMode(GPIOD, 15, OUTPUT);

    pinMode(GPIOA, 1, INPUT_PULLUP);

}

int main(void)
{

    uint8_t sens = 0;
    static int nb_appui =0;
    volatile int i;
    inititalisation();
    while (1)
    {
        if(lire_bouton())
            sens = !sens;

        chenillard(sens);  
        for(i = 0; i<5000000; i++);

        
    }
    
}
*/

//T timer = 1/THorloge * (PSC+1)* (ARR+1)
    //f horloge = 21MHz

#include "stm32f4xx.h"

 
void TIM2_IRQHandler(void) {
  // flash on update event
    if (TIM2->SR & TIM_SR_UIF) GPIOD->ODR ^= (1 << 13);
   
    TIM2->SR = 0x0; // reset the status register
}
 
int main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // enable the clock to GPIOD
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // enable TIM2 clock
     
    GPIOD->MODER = (1 << 26); // set pin 13 to be general purpose output
     
    NVIC->ISER[0] |= 1<< (TIM2_IRQn); // enable the TIM2 IRQ
     
    TIM2->PSC = 0x0; // no prescaler, timer counts up in sync with the peripheral clock
    TIM2->DIER |= TIM_DIER_UIE; // enable update interrupt
    TIM2->ARR = 5000000; // count to 1 (autoreload value 1)
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // autoreload on, counter enabled
    TIM2->EGR = 1; // trigger update event to reload timer registers
     
    while (1);
          
}
    
    