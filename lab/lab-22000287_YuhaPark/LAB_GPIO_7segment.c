/**
******************************************************************************
* @author  SSSLAB
* @Mod		 2024-09-18 by YuhaPark  	
* @brief   Embedded Controller:  Tutorial Digital In/Out 7-segment Display
* 
******************************************************************************
*/

#include "stm32f4xx.h"
#include "ecRCC2.h"
#include "ecGPIO2.h"

	
int main(void) {	
	// Initialiization --------------------------------------------------------
	setup();
	unsigned int count = 0;
	int last_button_state = 1; //(1 = pressed button, 0 = did not pressed button)
	
	
	// Inifinite Loop ----------------------------------------------------------
	while(1){
		
		int button_state = GPIO_read(BUTTON_PIN);
		sevensegment_display(count % 10);
		
		if(button_state == 0 && last_button_state == 1) {
            delay_ms(50);  
            if(GPIO_read(BUTTON_PIN) == 0) {
                delay_ms(200);  // Debounce delay
			          count++; 
                if (count > 9) {
                    count = 0; 
								}
						}
			}
		  last_button_state = button_state;
		  delay_ms(500);  // delay_ms(500);
		}
	}


// Initialiization 
void setup(void)
{
	RCC_HSI_init();	
	sevensegment_display_init(PA_7, PB_6, PC_7, PA_9);  // Decoder input A,B,C,D
}
