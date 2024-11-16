/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-24-2024
Modified         : 09-25-2024
Language/ver     : C++ in Keil uVision

Description      : TU_SysTick
/----------------------------------------------------------------*/


#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"

#define MCU_CLK_PLL 84000000
#define MCU_CLK_HSI 16000000

volatile uint32_t msTicks = 0;
volatile uint32_t curTicks;

void setup(void);
void SysTick_Handler(void);

int main(void) {
	
// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();

// SysTick Initialiization ------------------------------------------------------				
	//  SysTick Control and Status Register
	SysTick->CTRL = 0;				// Disable SysTick IRQ and SysTick Counter

	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;     

	// uint32_t MCU_CLK=EC_SYSTEM_CLK
	// SysTick Reload Value Register
	SysTick->LOAD = (1e-3)*(MCU_CLK_PLL)-1;  				// 1ms
																						// Reload = Tick Period * Clock Freq - 1

	// Clear SysTick Current Value 
	SysTick->VAL = 0;

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   //1
		
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   //1
		
	NVIC_SetPriority(SysTick_IRQn, 1);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);			// Enable interrupt in NVIC


// While loop ------------------------------------------------------				
	
	msTicks = 0;

	while(1){
		curTicks = msTicks;
		while ((msTicks - curTicks) < 1000);	// 1[s] delay
		msTicks = 0;
		LED_toggle();
		
	}
}


void SysTick_Handler(void){
	msTicks++;
}

void setup(void)
{
	RCC_PLL_init();              // System Clock = 84MHz	
	GPIO_init(PA_5, OUTPUT);     // calls RCC_GPIOA_enable()	
}

