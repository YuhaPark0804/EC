/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2024-10-04 by Yuha Park	
* @brief   Embedded Controller:  Tutorial Timer Interrupt
* 
******************************************************************************
*/
#include "stm32f411xe.h"
#include "ecGPIO2.h"
#include "ecRCC2.h"


PinName_t LED_pin = PA_5;
uint32_t count = 1;


void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	TIM_TypeDef* timerx;
	timerx = TIM2;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	timerx->PSC = 840 - 1;				        // Timer counter clock: 100KHz(1us)  84M/840 = 100K
	timerx->ARR = 100 - 1;		          // Set auto reload register to maximum (count up to 65535);   100K/100 = 1KHz (period: 1ms)
	timerx->DIER |= 1<<0;                	// Enable Interrupt
	timerx->CR1 |= 1<<0;                 	// Enable counter
	
	NVIC_SetPriority(TIM2_IRQn, 2);       // TIM2_IRQHandler Set priority as 2
	NVIC_EnableIRQ(TIM2_IRQn);			      // TIM2_IRQHandler Enable
	
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){}
}

// Initialiization 
void setup(void)
{	
	RCC_PLL_init();                       // System Clock = 84MHz
	GPIO_init(LED_pin, OUTPUT);           // calls RCC_GPIOA_enable()	
}

void TIM2_IRQHandler(void){
	if((TIM2->SR & TIM_SR_UIF) ==  1){    // update interrupt flag (1<<0)
		//Create the code to toggle LED by 1000ms
		
		if(count > 500){
			LED_toggle();
			count = 0;
		}
		count++;
		TIM2->SR &= ~(1<<0);                 // clear by writing 0
		
		}
}