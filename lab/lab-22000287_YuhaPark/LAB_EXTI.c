/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-27-2024
Modified         : 09-30-2024
Language/ver     : C++ in Keil uVision

Description      : LAB_EXTI; Problem 1: Counting numbers on 7-Segment using SysTick
/----------------------------------------------------------------*/


//#include "stm32f411xe.h"
//#include "ecRCC2.h"
//#include "ecGPIO2.h"
#include "ecSTM32F4v2.h"

unsigned int count = 0;

void setup(void);
void EXTI15_10_IRQHandler(void);

int main(void) {	
	// Initialiization --------------------------------------------------------
	setup();
		
	// Inifinite Loop ----------------------------------------------------------
	while(1){}
	}


//EXTI for Pin 13
void EXTI15_10_IRQHandler(void) {
	
	if (is_pending_EXTI(BUTTON_PIN)) {
		delayms(300);                      // delay 0.3s for debouncing 
		sevensegment_display(count % 10);
		count++;
		clear_pending_EXTI(BUTTON_PIN); 
		
		if ( count > 9) count = 0;
		

	}
}
		



void setup(void)
{
	RCC_PLL_init();                    // System Clock = 84MHz	
	sevensegment_display_init(LED_PINA_7, LED_PINB_6, LED_PINC_7, LED_PINA_9); 
	EXTI_init(BUTTON_PIN, FALL, 0);
}

