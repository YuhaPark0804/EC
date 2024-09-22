/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-09-2024
Modified         : 09-18-2024
Language/ver     : C++ in Keil uVision

Description      : LAB_GPIO Digital InOut
/----------------------------------------------------------------*/


#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"

#define HIGH 1
#define LOW  0

//MODER
typedef enum {INPUT  = 0b00, 
							OUTPUT = 0b01,
							AF     = 0b10,
							ANALOG = 0b11
}GPIO_MODE;

//OTYPER
typedef enum {PUSH_PULL  = 0, 
							OPEN_DIAIN = 1
}GPIO_TYPE;

//OSPEEDR
typedef enum {LOW_SPEED    = 0b00, 
              MEDIUM_SPEED = 0b01, 
              FAST_SPEED   = 0b10, 
              HIGH_SPEED   = 0b11
}GPIO_SPEED;

//PUPDR
typedef enum {NO_PUPD   = 0b00, 
              PULL_UP   = 0b01, 
              PULL_DOWN = 0b10, 
              RESERVED  = 0b11
}GPIO_PUPD;


#define LED_PINA_5 PA_5     
#define LED_PINA_6 PA_6 
#define LED_PINA_7 PA_7     
#define LED_PINB_6 PB_6 
#define LED_PINC_7 PC_7 
#define LED_PINA_9 PA_9 
#define LED_PINA_8 PA_8 
#define LED_PINB_10 PB_10 

#define BUTTON_PIN PC_13  

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_write(PinName_t pinName, int Output);
int  GPIO_read(PinName_t pinName);
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, int speed);
void GPIO_otype(PinName_t pinName, int type);
void GPIO_pupd(PinName_t pinName, int pupd);

//7-segment decoder: problem 1
void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD); 
void sevensegment_display(uint8_t  num);
void setup(void);
void delay_ms(int ms);

//7-segment decoder: problem 2
void sevensegment_decoder_init(void); 
void sevensegment_decoder(uint8_t  num);

 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
