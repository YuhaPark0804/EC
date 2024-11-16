/**
******************************************************************************
* @author  SSSLAB
* @created 2024-10-11 by YuhaPark 	
* @Mod		 2024-10-17 by YuhaPark 	
* @brief   Embedded Controller:  Tutorial ___
*					 - Input Capture
* 
******************************************************************************
*/

#include "stm32f411xe.h"
#include "math.h"
#include "ecSTM32F4v2.h"
#include "ecICAP2.h"
#include "ecUART2_simple_student.h"

#define TRIG PA_6
#define ECHO PB_6

uint32_t ovf_cnt = 0;
float distance = 0;
float timeInterval = 0;
float time1 = 0;
float time2 = 0;

void setup(void);


int main(void){
	
	setup();
	while(1){
		distance = (float) timeInterval * 340.0 / 2.0 / 10.0; 	// [mm] -> [cm]
		printf("distance:%f cm\r\n", distance);
		delay_ms(2000);
	}
}

// Timer2 IRQ Handler (timer & Input Capture)
void TIM4_IRQHandler(void){
	if(is_UIF(TIM4)){                     // Update interrupt
		ovf_cnt++;													// overflow count
		clear_UIF(TIM4);  							    // clear update interrupt flag
	}
	if(is_CCIF(TIM4, IC_1)){ 							// TIM4_Ch1 (IC1) Capture Flag. Rising Edge Detect
		time1 = ICAP_capture(TIM4, IC_1);		// Capture TimeStart
		
		
		clear_CCIF(TIM4, IC_1);                       // clear capture/compare interrupt flag 
	}								                      
	else if(is_CCIF(TIM4, IC_2)){ 									// TIM4_Ch2 (IC2) Capture Flag. Falling Edge Detect
		time2 = ICAP_capture(TIM4, IC_2);							// Capture TimeEnd
		timeInterval = ((time2 - time1) + ovf_cnt * (TIM4->ARR + 1)) / 100; 	// (10us * counter pulse -> [msec] unit) Total time of echo pulse
		
		
		ovf_cnt = 0;                        					// overflow reset
		clear_CCIF(TIM4,IC_2);								 				// clear capture/compare interrupt flag 
	}
}

void setup(void) {	
	// Configuration Clock PLL (System Clock = 84MHz)
	RCC_PLL_init();                   
	
	// UART2 Configuration to use printf()
	UART2_init();
	
	// SysTick Configuration to use delay_ms()
	SysTick_init();

	
	// PWM configuration ---------------------------------------------------------------------	
	PWM_init(TRIG);			           // PA_6: Ultrasonic trig pulse
	PWM_period_us(TRIG, 50000);    // PWM of 50ms period. Use period_us()
	PWM_pulsewidth_us(TRIG, 10);   // PWM pulse width of 10us
	
	
  // Input Capture configuration -----------------------------------------------------------------------	
	ICAP_init(ECHO);    					 // PB_6 as input caputre
 	ICAP_counter_us(ECHO, 10);   	 // ICAP counter step time as 10us
	ICAP_setup(ECHO, 1, IC_RISE);  // TIM4_CH1 as IC1 , rising edge detect
	ICAP_setup(ECHO, 2, IC_FALL);  // TIM4_CH2 as IC2 , falling edge detect
	
}