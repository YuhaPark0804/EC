/*----------------------------------------------------------------\
@ Embedded Controller by Yuha Park - Handong Global University
Author           : SSS LAB
Created          : 09-09-2024
Modified         : 09-18-2024
Language/ver     : C++ in Keil uVision

Description      : LAB_GPIO Digital InOut
/----------------------------------------------------------------*/



#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO2.h"


void GPIO_init(PinName_t pinName, uint32_t mode){     
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	
	if (Port == GPIOC)
		RCC_GPIOC_enable();
	
	if (Port == GPIOD)
		RCC_GPIOD_enable();
	
	if (Port == GPIOH)
		RCC_GPIOH_enable();
	
	

	// You can also make a more general function of
	// void RCC_GPIO_enable(GPIO_TypeDef *Port); 
	void RCC_GPIO_enable(GPIO_TypeDef* Port);

	GPIO_mode(pinName, mode);
}


// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
	
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
   Port->MODER &= ~(3UL<<(2*pin));  
	
   Port->MODER |= mode<<(2*pin);    
}


// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, int speed){
	
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
   Port->OSPEEDR &= ~(0b11<<(2*pin));  	
   Port->OSPEEDR |= speed<<(2*pin);    
}

// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, int type){
	
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
   Port->OTYPER &= ~(1UL<<pin);     
   Port->OTYPER |= type<<(pin);    
}

// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, int pupd){
	
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
   Port->PUPDR &= ~(3UL<<(2*pin));     
   Port->PUPDR |= pupd<<(2*pin);    
}

int GPIO_read(PinName_t pinName){
	
	GPIO_TypeDef * Port;	 
  unsigned int pin;
  ecPinmap(pinName,&Port,&pin);
   
	return (Port->IDR>>pin)&0b1;
}

void GPIO_write(PinName_t pinName, int Output){
	
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
	
	 Port->ODR &= ~(1UL << pin);
	 Port->ODR |= (Output << pin);
	
}

void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD){
	  GPIO_TypeDef *PortA, *PortB, *PortC, *PortD;
    unsigned int pinA, pinB, pinC, pinD;

    ecPinmap(pinNameA, &PortA, &pinA);
    ecPinmap(pinNameB, &PortB, &pinB);
    ecPinmap(pinNameC, &PortC, &pinC);
    ecPinmap(pinNameD, &PortD, &pinD);
	
	
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
	GPIO_init(pinNameA, OUTPUT); 
  GPIO_init(pinNameB, OUTPUT);	
	GPIO_init(pinNameC, OUTPUT);
	GPIO_init(pinNameD, OUTPUT);
	
	//PC_13
	GPIO_pupd(BUTTON_PIN, PULL_UP);
	//PA_7
	GPIO_ospeed(pinNameA, MEDIUM_SPEED);
	GPIO_otype(pinNameA, PUSH_PULL);
	GPIO_pupd(pinNameA, NO_PUPD);
	//PB_6
	GPIO_ospeed(pinNameB, MEDIUM_SPEED);
	GPIO_otype(pinNameB, PUSH_PULL);
	GPIO_pupd(pinNameB, NO_PUPD);
	//PC_7
	GPIO_ospeed(pinNameC, MEDIUM_SPEED);
	GPIO_otype(pinNameC, PUSH_PULL);
	GPIO_pupd(pinNameC, NO_PUPD);
	//PA_9
	GPIO_ospeed(pinNameD, MEDIUM_SPEED);
	GPIO_otype(pinNameD, PUSH_PULL);
	GPIO_pupd(pinNameD, NO_PUPD);
	
	
	
}



void sevensegment_display(uint8_t  num){
	uint8_t segment_map[10] = {
			
		 0b0000, // 0
     0b0001, // 1
     0b0010, // 2
     0b0011, // 3
     0b0100, // 4
     0b0101, // 5
     0b0110, // 6
     0b0111, // 7
     0b1000, // 8
     0b1001  // 9
	};
	
	uint8_t segments = segment_map[num];
	

	GPIO_write(LED_PINA_7, (segments & 0b0001) ? HIGH : LOW);  // A Segment
	GPIO_write(LED_PINB_6, (segments & 0b0010) ? HIGH : LOW);  // B Segment
	GPIO_write(LED_PINC_7, (segments & 0b0100) ? HIGH : LOW);  // C Segment
	GPIO_write(LED_PINA_9, (segments & 0b1000) ? HIGH : LOW);  // D Segment
	
}

void sevensegment_decoder_init(void){
	
	GPIO_init(BUTTON_PIN, INPUT);  
	GPIO_init(LED_PINA_5, OUTPUT); 
  GPIO_init(LED_PINA_6, OUTPUT); 
	GPIO_init(LED_PINA_7, OUTPUT); 
	GPIO_init(LED_PINB_6, OUTPUT); 
	GPIO_init(LED_PINC_7, OUTPUT); 
	GPIO_init(LED_PINA_9, OUTPUT); 
	GPIO_init(LED_PINA_8, OUTPUT); 
	GPIO_init(LED_PINB_10, OUTPUT); 
	
	//PC_13
	GPIO_pupd(BUTTON_PIN, PULL_UP);
	//PA_5
	GPIO_ospeed(LED_PINA_5, MEDIUM_SPEED);
	GPIO_otype(LED_PINA_5, PUSH_PULL);
	GPIO_pupd(LED_PINA_5, NO_PUPD);
	//PA_6
	GPIO_ospeed(LED_PINA_6, MEDIUM_SPEED);
	GPIO_otype(LED_PINA_6, PUSH_PULL);
	GPIO_pupd(LED_PINA_6, NO_PUPD);
	//PA_7
	GPIO_ospeed(LED_PINA_7, MEDIUM_SPEED);
	GPIO_otype(LED_PINA_7, PUSH_PULL);
	GPIO_pupd(LED_PINA_7, NO_PUPD);
	//PB_6
	GPIO_ospeed(LED_PINB_6, MEDIUM_SPEED);
	GPIO_otype(LED_PINB_6, PUSH_PULL);
	GPIO_pupd(LED_PINB_6, NO_PUPD);
	//PC_7
	GPIO_ospeed(LED_PINC_7, MEDIUM_SPEED);
	GPIO_otype(LED_PINC_7, PUSH_PULL);
	GPIO_pupd(LED_PINC_7, NO_PUPD);
	//PA_9
	GPIO_ospeed(LED_PINA_9, MEDIUM_SPEED);
	GPIO_otype(LED_PINA_9, PUSH_PULL);
	GPIO_pupd(LED_PINA_9, NO_PUPD);
	//PA_8
	GPIO_ospeed(LED_PINA_8, MEDIUM_SPEED);
	GPIO_otype(LED_PINA_8, PUSH_PULL);
	GPIO_pupd(LED_PINA_8, NO_PUPD);
	//PA_10
	GPIO_ospeed(LED_PINB_10, MEDIUM_SPEED);
	GPIO_otype(LED_PINB_10, PUSH_PULL);
	GPIO_pupd(LED_PINB_10, NO_PUPD);
}
void sevensegment_decoder(uint8_t  num){
	
	uint8_t segment_map[10] = {
			
		 0b00000011, // 0
     0b10011111, // 1
     0b00100101, // 2
     0b00001101, // 3
     0b10011001, // 4
     0b01001001, // 5
     0b01000001, // 6
     0b00011011, // 7
     0b00000001, // 8
     0b00001001  // 9
	};
	
	uint8_t segments = segment_map[num];
	

	GPIO_write(LED_PINA_5, (segments & 0b10000000) ? HIGH : LOW);  // a
	GPIO_write(LED_PINA_6, (segments & 0b01000000) ? HIGH : LOW);  // b
	GPIO_write(LED_PINA_7, (segments & 0b00100000) ? HIGH : LOW);  // c
	GPIO_write(LED_PINB_6, (segments & 0b00010000) ? HIGH : LOW);  // d 
	GPIO_write(LED_PINC_7, (segments & 0b00001000) ? HIGH : LOW);  // e 
	GPIO_write(LED_PINA_9, (segments & 0b00000100) ? HIGH : LOW);  // f 
	GPIO_write(LED_PINA_8, (segments & 0b00000010) ? HIGH : LOW);  // g 
	GPIO_write(LED_PINB_10, (segments & 0b00000001) ? HIGH : LOW);  // dp 
	
	
}

// Simple delay function
void delay_ms(int ms) {
    for(int i = 0; i < ms * 1000; i++);  // Approximate delay
}

