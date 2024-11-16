/**
******************************************************************************
* @author  SSSLAB
* @Created 2024-10-06 by Yuha Park
* @Mod		 2024-10-06 by Yuha Park
* @brief   Embedded Controller:  [LAB Timer & PWM ]Problem 1: RC servo motor
* 
******************************************************************************
*/
#include "stm32f411xe.h"
//#include "ecGPIO2.h"
//#include "ecRCC2.h"
//#include "ecSysTick2.h"

#include "ecSTM32F4v2.h"

#define PWM_PIN PA_1




int i = 0;
int direction = 1;
int count = 0;

void setup(void);

	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){}
	
}
/*
void TIM2_IRQHandler(void){
	if(is_UIF(TIM1)){                  // update interrupt flag (1<<0)
		clear_UIF(TIM1);                 // clear by writing 0
	}
}*/


void TIM3_IRQHandler(void){

	if(is_UIF(TIM3)){    // update interrupt flag (1<<0)
		
		sevensegment_display(i);
		
	  PWM_pulsewidth_us(PWM_PIN, 500 + 222*i);
	  i += direction;
		if(i > 9){ // i=10
			direction = -1;
			i += direction; //i=9
			i += direction;  //i=8
		}
		if(i < 0){ // i=-1
			direction = 1;
			i += direction; //i=0
			i += direction;  //i=1
		}
		
		clear_UIF(TIM3);                 // clear by writing 0
	}
}

void EXTI15_10_IRQHandler(void) {
	
	if (is_pending_EXTI(BUTTON_PIN)) {
		//i = 0;
		direction *= -1;
		clear_pending_EXTI(BUTTON_PIN); 
	}
}


// Initialiization 
void setup(void){	
	
	RCC_PLL_init();             // System Clock = 84MHz	
	sevensegment_display_init(LED_PINA_7, LED_PINB_6, LED_PINC_7, LED_PINA_9);
	
	EXTI_init(BUTTON_PIN, FALL, 0);	
	GPIO_init(BUTTON_PIN, INPUT);             
	GPIO_pupd(BUTTON_PIN, PULL_UP); 

  PWM_init(PWM_PIN);
	PWM_period_ms(PWM_PIN, 20);	
	
	TIM_UI_init(TIM3, 1000);
	TIM_period_ms(TIM3, 1000);
	TIM_UI_enable(TIM3);
	

}

