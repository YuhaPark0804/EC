#include "stm32f4xx.h"
#include "ecStepper2.h"

//State number 
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7


// Stepper Motor function
uint32_t direction = 1; 
uint32_t step_delay = 100; 
uint32_t step_per_rev = 64*32;
	 

// Stepper Motor variable
volatile Stepper_t myStepper; 


//FULL stepping sequence  - FSM
typedef struct {
	uint8_t out;
  uint32_t next[2];
} State_full_t;

State_full_t FSM_full[4] = {  	// 1010 , 0110 , 0101 , 1001
 	{0b1100,{S1,S3}},		// ABA'B'
 	{0b0110,{S2,S0}},
 	{0b0011,{S3,S1}},
	{0b1001,{S0,S2}}
};

//HALF stepping sequence
typedef struct {
	uint8_t out;
  uint32_t next[2];
} State_half_t;

State_half_t FSM_half[8] = {	// 1000 , 1010 , 0010 , 0110 , 0100 , 0101, 0001, 1001
 	{0b1000,{S1,S7}},	     	// ABA'B' 0
	{0b1100,{S2,S0}},			 	//1
	{0b0100,{S3,S1}},				//2
	{0b0110,{S4,S2}},				//3
	{0b0010,{S5,S3}},				//4
	{0b0011,{S6,S4}},				//5
	{0b0001,{S7,S5}},				//6
	{0b1001,{S0,S6}},				//7
};



void Stepper_init(PinName_t pinName1, PinName_t pinName2, PinName_t pinName3, PinName_t pinName4){
	 
	//  GPIO Digital Out Initiation
	myStepper.pin1 = pinName1;
	myStepper.pin2 = pinName2;
	myStepper.pin3 = pinName3;
	myStepper.pin4 = pinName4;
	
	//  GPIO Digital Out Initiation
	// No pull-up Pull-down , Push-Pull, Fast	
	// Pin1 ~ Port4
	
	GPIO_TypeDef *Port;
  unsigned int pin;
  PinName_t pins[4] = {myStepper.pin1, myStepper.pin2, myStepper.pin3, myStepper.pin4};

  for (int i = 0; i < 4; i++) {
      ecPinmap(pins[i], &Port, &pin);
			GPIO_init(pins[i], OUTPUT);
      GPIO_ospeed(pins[i], FAST_SPEED);
      GPIO_otype(pins[i], PUSH_PULL);
      GPIO_pupd(pins[i], NO_PUPD);
  }
}


void Stepper_pinOut (uint32_t state, uint32_t mode){	
   	if (mode == FULL){         // FULL mode
		GPIO_write(myStepper.pin1, (FSM_full[state].out & 0b1000) >> 3);
		GPIO_write(myStepper.pin2, (FSM_full[state].out & 0b0100) >> 2);
		GPIO_write(myStepper.pin3, (FSM_full[state].out & 0b0010) >> 1);
		GPIO_write(myStepper.pin4, (FSM_full[state].out & 0b0001) >> 0);
	}	 
 	else if (mode == HALF){    // HALF mode
		GPIO_write(myStepper.pin1, (FSM_half[state].out & 0b1000) >> 3);
		GPIO_write(myStepper.pin2, (FSM_half[state].out & 0b0100) >> 2);
		GPIO_write(myStepper.pin3, (FSM_half[state].out & 0b0010) >> 1);
		GPIO_write(myStepper.pin4, (FSM_half[state].out & 0b0001) >> 0);
	}
}


void Stepper_setSpeed (long whatSpeed){            // rpm [rev/min]
		step_delay = 	60000/(whatSpeed*step_per_rev);  // Convert rpm to  [msec/step] delay
}                                                  // [rev/min] * [min/60,000*msec] * [64*32*step/rev]


void Stepper_step(uint32_t steps, uint32_t direction, uint32_t mode){
	 uint32_t state = 0;
	 myStepper._step_num = steps;

	 for(; myStepper._step_num > 0; myStepper._step_num--){ // run for step size
		 
	   if (mode == FULL){
			 delay_ms(step_delay);                          // delay (step_delay); 
			 state = FSM_full[state].next[direction]; 
		 }			                                          // state = next state
		 else if (mode == HALF){ 
			 delay_ms(step_delay * 0.5);                    // delay (step_delay); 
			 state = FSM_half[state].next[direction];  
		 }			 																					// state = next state		
		Stepper_pinOut(state, mode);
		}
}


void Stepper_stop (void){ 
    	myStepper._step_num = 1;    
	// All pins(A,AN,B,BN) set as DigitalOut '0'
	GPIO_write(myStepper.pin1, LOW); 
	GPIO_write(myStepper.pin2, LOW); 
	GPIO_write(myStepper.pin3, LOW); 
	GPIO_write(myStepper.pin4, LOW); 
}

