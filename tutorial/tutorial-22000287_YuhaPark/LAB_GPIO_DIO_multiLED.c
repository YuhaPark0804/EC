/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-09-2024
Modified         : 09-12-2024
Language/ver     : C++ in Keil uVision

Description      : LAB_GPIO; Toggle Multi LED with Button
/----------------------------------------------------------------*/

#include "ecRCC2.h"
#include "ecGPIO2.h"
#include "ecPinNames.h"

#define LED_PIN5 PA_5
#define LED_PIN6 PA_6
#define LED_PIN7 PA_7
#define LED_PINB6 PB_6
#define BUTTON_PIN PC_13

// Initialiization 
void setup(void) {
	RCC_HSI_init();
	// initialize the pushbutton pin as an input:
	GPIO_init(BUTTON_PIN, INPUT);  
	// initialize the LED pin as an output:
	GPIO_init(LED_PIN5, OUTPUT); 
  GPIO_init(LED_PIN6, OUTPUT);	
	GPIO_init(LED_PIN7, OUTPUT);
	GPIO_init(LED_PINB6, OUTPUT);
	
	GPIO_pupd(BUTTON_PIN, PULL_UP);
	//PA_5
	GPIO_ospeed(LED_PIN5, MEDIUM_SPEED);
	GPIO_otype(LED_PIN5, PUSH_PULL);
	GPIO_pupd(LED_PIN5, PULL_UP);
	//PA_6
	GPIO_ospeed(LED_PIN6, MEDIUM_SPEED);
	GPIO_otype(LED_PIN6, PUSH_PULL);
	GPIO_pupd(LED_PIN6, PULL_UP);
	//PA_7
	GPIO_ospeed(LED_PIN7, MEDIUM_SPEED);
	GPIO_otype(LED_PIN7, PUSH_PULL);
	GPIO_pupd(LED_PIN7, PULL_UP);
	//PB_6
	GPIO_ospeed(LED_PINB6, MEDIUM_SPEED);
	GPIO_otype(LED_PINB6, PUSH_PULL);
	GPIO_pupd(LED_PINB6, PULL_UP);
}
	
int main(void) { 
 	setup();
	int buttonState = 0;
	int button = 1; // button did not pressed
	int count = 0;
	
	while(1){
		// check if the pushbutton is pressed. Turn LED on/off accordingly:
		buttonState = GPIO_read(BUTTON_PIN);
		
		if(buttonState == 0 && button ==1){
			if(count == 0) {
				GPIO_write(LED_PIN5, HIGH);
				GPIO_write(LED_PIN6, LOW);
				GPIO_write(LED_PIN7, LOW);
				GPIO_write(LED_PINB6, LOW);
				
		}
			else if(count == 1){
				GPIO_write(LED_PIN5, LOW);
				GPIO_write(LED_PIN6, HIGH);
				GPIO_write(LED_PIN7, LOW);
				GPIO_write(LED_PINB6, LOW);
				
			}
			else if(count == 2){
				GPIO_write(LED_PIN5, LOW);
				GPIO_write(LED_PIN6, LOW);
				GPIO_write(LED_PIN7, HIGH);
				GPIO_write(LED_PINB6, LOW);
				
			}
			else if(count == 3){
				GPIO_write(LED_PIN5, LOW);
				GPIO_write(LED_PIN6, LOW);
				GPIO_write(LED_PIN7, LOW);
				GPIO_write(LED_PINB6, HIGH);
				
			}
			count = (count + 1) % 4;
		}
		button = buttonState;
	}
}
	