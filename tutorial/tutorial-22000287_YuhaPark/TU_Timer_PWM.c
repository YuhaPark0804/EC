/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2024-10-04 by Yuha Park
* @brief   Embedded Controller:  Tutorial Timer_PWM
* 
******************************************************************************
*/
//#include "stm32f411xe.h"
//#include "ecGPIO2.h"
//#include "ecRCC2.h"
//#include "ecSysTick2.h"
#include "ecSTM32F4v2.h"

#define LED_PIN    PA_5

void setup(void);
	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	
	// TEMP: TIMER Register Initialiization --------------------------------------------------------		
	TIM_TypeDef *TIMx;
	TIMx = TIM2;
	
	// GPIO: ALTERNATIVE function setting
	GPIOA->AFR[0]	 = (0b0001)<<5*4;       // AF1 at PA5 = TIM2_CH1 (p.150)
	
	// TIMER: PWM setting
	RCC->APB1ENR |= 1<<0;            			// Enable TIMER clock
	
	TIMx->CR1 &= ~(1<<4);				         	// Direction Up-count
	
	TIMx->PSC = 840 - 1;					        // Set Timer CLK = 100kHz : (PSC + 1) = 84MHz/100kHz --> PSC = 839
	
	TIMx->ARR = 100 - 1;					        // Auto-reload: Upcounting (0...ARR). 
																				// Set Counter CLK = 1kHz : (ARR + 1) = 100kHz/1kHz --> ARR = 99
	
	TIMx->CCMR1 &= ~TIM_CCMR1_OC1M;  			// Clear ouput compare mode bits for channel 1
	TIMx->CCMR1 |= 0b0110<<4;             // OC1M = 110 for PWM Mode 1 output on ch1
	TIMx->CCMR1	|= TIM_CCMR1_OC1PE;    		// Output 1 preload enable (make CCR1 value changable)
	
	TIMx->CCR1 = 50;                      // Output Compare Register for channel 1 	
																				// Set CCR value for 50% duty ratio: (ARR+1)/2
	
	TIMx->CCER &= ~TIM_CCER_CC1P;    			// select output polarity: active high	
	TIMx->CCER |= 1<<0;										// Enable output for ch1
	
	TIMx->CR1  |= TIM_CR1_CEN;      			// Enable counter
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
			//Create the code to change the brightness of LED as 1kHZ (use "delay(1000)")
	   //GPIO_write(LED_PIN, HIGH);
		
		for(int i = 0; i < 3; i++){
			TIMx->CCR1 = (50 * i);      // Duty = CCR/(ARR+1) = 50*i/100
			delay_ms(1000);
		}
	}
}
// Initialiization 
void setup(void){	
	
	RCC_PLL_init();                         // System Clock = 84MHz
	SysTick_init();                         // for delay_ms()
	
	GPIO_init(LED_PIN, AF);             // GPIOA 5 ALTERNATE function
	GPIO_ospeed(LED_PIN, HIGH_SPEED);       // GPIOA 5 HIGH SPEED
	GPIO_pupd(LED_PIN, NO_PUPD);            // GPIOA 5 No-pullup pulldown
	GPIO_otype(LED_PIN, PUSH_PULL);					// GPIOA 5 Push-Pull
	
	
}


