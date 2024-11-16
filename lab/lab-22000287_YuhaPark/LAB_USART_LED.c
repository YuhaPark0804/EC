/*
******************************************************************************
* @author  Hee-Won Kim &
* @Mod	   2024-10-09 by KHW0619 &
* @brief   Embedded Controller:  LAB_RCcar
******************************************************************************
*/

#include "ecSTM32F4v2.h"

#define LEFT 0
#define RIGHT 1
#define LED_PIN PA_5

// DC motor
PinName_t PWM_PIN[2] = {PA_0, PA_6}; // TIM2, TIM3
PinName_t DIR_PIN[2] = {PC_2, PC_3};
uint32_t PWM_value[2] = { 0, 0 };
uint32_t DIR_value[2] = { 0, 0 };

// IR
PinName_t IR_PIN[2] = {PB_0, PB_1};
uint32_t IR_value[2] = { 0, 0 };

//Input Capture-Ultrasonic
#define TRIG PA_8 //TIM1
#define ECHO PB_6 //TIM4

float ICAP_time1 = 0;
float ICAP_time2 = 0;
float ICAP_distance = 0;
float ICAP_timeInterval = 0;
uint32_t ICAP_ovf_cnt = 0;

//USART - bluetooth
#define TXD_PIN PA_9
#define RXD_PIN PA_10

/*
manual

led_value
speed_value
steer_value
dir_flag
stop_flag
*/


static volatile uint8_t PC_Data = 0;
static volatile uint8_t BT_Data = 0;


int main(void){   
   setup();  
   while(1){
      ICAP_distance = (float) ICAP_timeInterval * 340.0 / 2.0 / 100.0; 	// [mm] -> [cm]
			printf("%f cm\r\n", ICAP_distance);
			delay_ms(500);   

         
      //IR
		 /*
      printf("value1 = %d \r\n",IR_value[0]);
      printf("value2 = %d \r\n",IR_value[1]);
      printf("\r\n");
      
      delay_ms(1000);
		 */
      //IR end
      
      //ICAP
		 /*
      ICAP_distance = (float) ICAP_timeInterval * 340.0 / 2.0 / 10.0;    // [mm] -> [cm]
      printf("distance:%f cm\r\n", ICAP_distance);
      delay_ms(2000);
		 */
      //ICAP end
   }
}

void USART2_IRQHandler(){                // USART2 RX Interrupt : Recommended
   if(is_USART2_RXNE()){
      PC_Data = USART2_read();      // RX from UART2 (PC)
      USART2_write(&PC_Data,1);      // TX to USART2    (PC)    Echo of keyboard typing      
   }
}


void USART1_IRQHandler(){                // USART2 RX Interrupt : Recommended
   if(is_USART1_RXNE()){
		 
     BT_Data = USART1_read();      // RX from UART1 (BT)      
     printf("RX: %c \r\n",BT_Data); // TX to USART2(PC)
		 
		 if(BT_Data == 'R'){
			 
		 }
		 else if(BT_Data == 'L'){
			 
		 }

   }
}

/*void TIM4_IRQHandler(void){

   if(is_UIF(TIM4)){    // update interrupt flag (1<<0)
         
      LED_toggle();
      TIM_period_ms(TIM4, 200+200*i); //i=0 -> 0.2s, i=1 -> 0.4s, i=2 -> 0.6s
      
      
      clear_UIF(TIM4);                 // clear by writing 0
   }
}*/

void TIM4_IRQHandler(void){
   if(is_UIF(TIM4)){                     // Update interrupt
      ICAP_ovf_cnt++;                                       // overflow count
      clear_UIF(TIM4);                           // clear update interrupt flag
   }
   if(is_CCIF(TIM4, IC_1)){                      // TIM4_Ch1 (IC1) Capture Flag. Rising Edge Detect
      ICAP_time1 = ICAP_capture(TIM4, IC_1);      // Capture TimeStart
      
      
      clear_CCIF(TIM4, IC_1);                       // clear capture/compare interrupt flag 
   }                                              
   else if(is_CCIF(TIM4, IC_2)){                            // TIM4_Ch2 (IC2) Capture Flag. Falling Edge Detect
      ICAP_time2 = ICAP_capture(TIM4, IC_2);                     // Capture TimeEnd
      ICAP_timeInterval = ((ICAP_time2 - ICAP_time1) + ICAP_ovf_cnt * (TIM4->ARR + 1)) / 100;    // (10us * counter pulse -> [msec] unit) Total time of echo pulse
      
      ICAP_ovf_cnt = 0;                                       // overflow reset
      clear_CCIF(TIM4,IC_2);                                     // clear capture/compare interrupt flag 
   }
}

/*
void TIM3_IRQHandler(void){

   if(is_UIF(TIM3)){    // update interrupt flag (1<<0)
         
      PWM_duty(PWM_PIN, 0.5);

      clear_UIF(TIM3);                 // clear by writing 0
   }
}*/

void ADC_IRQHandler(void){
   if(is_ADC_OVR())
      clear_ADC_OVR();
   
   if(is_ADC_JEOC()){      // after finishing sequence
      IR_value[0] = JADC_read(1);
      IR_value[1] = JADC_read(2);
      clear_ADC_JEOC();
   }
}

void setup(void){
   RCC_PLL_init();
   SysTick_init();
   
   // USART2: USB serial init
   UART2_init();
   UART2_baud(BAUD_9600);

   // USART1: BT serial init 
   UART1_init();
   UART1_baud(BAUD_9600);
   
   //GPIO_init(PA_5, OUTPUT);
   
   
   //IR
   // ADC Init  Default: HW triggered by TIM3 counter @ 1msec
   JADC_init(IR_PIN[0]);
   JADC_init(IR_PIN[1]);

   // ADC channel sequence setting
   JADC_sequence(IR_PIN, 2);
   //IR end
   
   //ICAP
   // PWM configuration ---------------------------------------------------------------------   
   PWM_init(TRIG);                    // PA_6: Ultrasonic trig pulse
   PWM_period_us(TRIG, 50000);    // PWM of 50ms period. Use period_us()
   PWM_pulsewidth_us(TRIG, 10);   // PWM pulse width of 10us
   
   
  // Input Capture configuration -----------------------------------------------------------------------   
   ICAP_init(ECHO);                    // PB_6 as input caputre
   ICAP_counter_us(ECHO, 10);       // ICAP counter step time as 10us
   ICAP_setup(ECHO, 1, IC_RISE);  // TIM4_CH1 as IC1 , rising edge detect
   ICAP_setup(ECHO, 2, IC_FALL);  // TIM4_CH2 as IC2 , falling edge detect
   //ICAP end
   
	 for(int i = 0; i < 2; i++){
		 GPIO_init(DIR_PIN[i], OUTPUT);             
	   GPIO_pupd(DIR_PIN[i], PUSH_PULL);
		 
		 PWM_init(PWM_PIN[i]);
	   PWM_period_ms(PWM_PIN[i], 20);	
	 }
	  
	 GPIO_write(DIR_PIN[0], 1);	    //SET DIR Pin Low(CW)
	 GPIO_write(DIR_PIN[1], 0);
	 
  
	//TIM_UI_init(TIM3);
	//TIM_period_ms(TIM3, 1000);
	
	//TIM_UI_init(TIM4);
	//TIM_period_ms(TIM4, 200);
}