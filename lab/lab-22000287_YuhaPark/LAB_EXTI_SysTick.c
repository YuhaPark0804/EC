/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-29-2024
Modified         : 10-01-2024
Language/ver     : C++ in Keil uVision

Description      : LAB_SysTick& EXTI; Problem 2: Counting numbers on 7-Segment using SysTick
/----------------------------------------------------------------*/


//#include "stm32f411xe.h"
//#include "ecRCC2.h"
//#include "ecGPIO2.h"
#include "ecSTM32F4v2.h"

int count = 0;
int direction = 1;   //1: up, -1: down 

void setup(void);
void EXTI15_10_IRQHandler(void);


int main(void) {

	// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();


	// While loop ------------------------------------------------------				


	while (1) {

		delay_ms(1000);         // 1[s] delay		


		sevensegment_display(count);

		count += direction;


		if (count > 9) count = 0;
		if (count < 0) count = 9;

	}
}


//EXTI for Pin 13
void EXTI15_10_IRQHandler(void) {

	if (is_pending_EXTI(BUTTON_PIN)) {

		direction = -1 * direction;

		clear_pending_EXTI(BUTTON_PIN);
	}
}


void setup(void)
{
	RCC_PLL_init();                    // System Clock = 84MHz	
	SysTick_init();
	sevensegment_display_init(LED_PINA_7, LED_PINB_6, LED_PINC_7, LED_PINA_9);
	EXTI_init(BUTTON_PIN, FALL, 0);
}

