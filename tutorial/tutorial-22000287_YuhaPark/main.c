/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-09-2024
Modified         : 09-12-2024
Language/ver     : C++ in Keil uVision

Description      : LAB_GPIO; Toggle LED with Button
/----------------------------------------------------------------*/


#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecPinNames.h"

#define LED_PIN PA_5
#define BUTTON_PIN PC_13

// Initialiization 
void setup(void) {
	RCC_HSI_init();
	// initialize the pushbutton pin as an input:
	GPIO_init(BUTTON_PIN, INPUT);  
	// initialize the LED pin as an output:
	GPIO_init(LED_PIN, OUTPUT);  


	GPIO_ospeed(LED_PIN, MEDIUM_SPEED);
	GPIO_otype(LED_PIN, OPEN_DIAIN);
	GPIO_pupd(LED_PIN, PULL_UP);
	
	GPIO_pupd(BUTTON_PIN, PULL_UP);
}
	
int main(void) { 
 	setup();
	int buttonState = 0;
	int ledState = 0;
	
	
	while(1){
		// check if the pushbutton is pressed. Turn LED on/off accordingly:
		buttonState = GPIO_read(BUTTON_PIN);
		
		if(buttonState == 0){
			if(ledState == 0) {
				GPIO_write(LED_PIN, HIGH);
				ledState = 1;
		}
			else{
				GPIO_write(LED_PIN, LOW);
				ledState = 0;
			}
		
		}
	}
}
	