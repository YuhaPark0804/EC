/**
******************************************************************************
* @author  SSSLAB
* @Created 2024-10-09 by Yuha Park
* @Mod		 2024-10-09 by Yuha Park
* @brief   Embedded Controller:  [LAB Timer & PWM ]Problem 2: DC motor
* 
******************************************************************************
*/
//#include "stm32f411xe.h"
//#include "ecGPIO2.h"
//#include "ecRCC2.h"
//#include "ecSysTick2.h"

#include "ecSTM32F4v2.h"

#define DIR_PIN PC_3
#define PWM_PIN PA_6  
#define LED_PIN PA_5  


float duty = 0.0;

uint8_t direction = 0;  //0 or 1
int i = 0;
int i_direction = 1;  //1 or -1

int count = 0;


void setup(void);

	
int main(void) { 
	// Initialiization --------------------------------------------------------
	setup();
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){}
	
}


void TIM2_IRQHandler(void){
	if(is_UIF(TIM2)){                  // update interrupt flag (1<<0)
		clear_UIF(TIM2);                 // clear by writing 0
	}
}



void TIM4_IRQHandler(void){

	if(is_UIF(TIM4)){    // update interrupt flag (1<<0)
			
		LED_toggle();
		TIM_period_ms(TIM4, 200+200*i); //i=0 -> 0.2s, i=1 -> 0.4s, i=2 -> 0.6s
		
		
		clear_UIF(TIM4);                 // clear by writing 0
	}
}


void TIM3_IRQHandler(void){

	if(is_UIF(TIM3)){    // update interrupt flag (1<<0)
			
		
		sevensegment_display(i); //i = 0,1,2
		
		
		if(direction == 0){
			PWM_duty(PWM_PIN, 0.25*i);
			i++;
			if(i>2) i=0;
		}
		else{
			PWM_duty(PWM_PIN, (direction-0.25*i));  //i=0->1, i=1->0.75, i=2->0.5
			i--;
			if(i<0) i=2;
		}
		
		
		
		//rc servo motor
		/*
		PWM_pulsewidth_us(PWM_PIN, 500 + 222 * count);
		count += i_direction;
		
		if (count > 9) { // i=10
			i_direction = -1;
			count += -2;  //i=8
		}
		if (count < 0) { // i=-1
			i_direction = 1;
			count += 2;  //i=1
		}
		*/
		
		
		clear_UIF(TIM3);                 // clear by writing 0
	}
}

void EXTI15_10_IRQHandler(void) {
	
	if (is_pending_EXTI(BUTTON_PIN)) {
		
		//When Button is pressed, it should PAUSE or CONTINUE motor run (flag)
		/*
		if( pause_flag == 1){
			pause_flag = 0;
			duty_state = duty;
			duty = 0;
		}
		else if(pause_flag == 0){
			pause_flag = 1;
			duty = duty_state;
		}
		PWM_duty(PWM_PIN, duty);
		*/
		
		//this is for rc servo motor
		i_direction *= -1; 
		
		//this is for Dc motor
		direction ^= 1;
		GPIO_write(DIR_PIN, direction);     //direction = 0(ccr), = 1 (cr)
		
		
																				// Clear EXTI Pending
		clear_pending_EXTI(BUTTON_PIN); 
	} 
	
}


// Initialiization 
void setup(void){	
	
	RCC_PLL_init();             // System Clock = 84MHz	
	
	SysTick_init();
	
	sevensegment_display_init(PA_7, PB_6, PC_7, PA_9); 
	
	GPIO_init(BUTTON_PIN, INPUT);             
	GPIO_pupd(BUTTON_PIN, PULL_UP); 
	EXTI_init(BUTTON_PIN, FALL, 0);	
	
	GPIO_init(DIR_PIN, OUTPUT);             
	GPIO_pupd(DIR_PIN, PUSH_PULL); 
	GPIO_write(DIR_PIN, 0);	    //SET DIR Pin Low(ccr)
	
	GPIO_init(LED_PIN, OUTPUT);

  PWM_init(PWM_PIN);
	PWM_period_ms(PWM_PIN, 20);	
	
	TIM_UI_init(TIM3);
	TIM_period_ms(TIM3, 1000);
	
	TIM_UI_init(TIM4);
	TIM_period_ms(TIM4, 200);
	

}

