# EC


# LAB: GPIO Digital InOut 7-segment

## LAB: GPIO Digital InOut 7-segment

**Date:** 2024-09-22

**Author/Partner:** YuhaPark/ no partner

**Github:** repository link

**Demo Video:** Youtube link

**PDF version:** 2024.003.20112

## Introduction

In this lab, you are required to create a simple program to control a 7-segment display to show a decimal number (0~9) that increases by pressing a push-button.

You must submit

- LAB Report (*.pdf)
- Zip source files(LAB***.c, ecRCC2.h, ecGPIO2.h etc...).
  - Only the source files. Do not submit project files

#### Requirement

**Hardware**

- MCU
  - NUCLEO-F411RE
- Actuator/Sensor/Others:
  - 7-segment display(5101ASR)
  - Array resistor (330 ohm)
  - decoder chip(74LS47)
  - breadboard

**Software**

- Keil uVision, CMSIS, EC_HAL library

## Exercise



| **Port/Pin**   | **Description**              | **Register setting**         |
| -------------- | ---------------------------- | ---------------------------- |
| Port A Pin 5   | Clear Pin5 mode              | GPIOA->MODER &= ~(3<<(5*2))  |
| Port A Pin 5   | Set Pin5 mode = Output       | GPIOA->MODER \|= 1<<(5*2)    |
| Port A Pin 6   | Clear Pin6 mode              | GPIOA->MODER &=~(3<<(6*2))   |
| Port A Pin 6   | Set Pin6 mode = Output       | GPIOA->MODER \|= 1<<(6*2)    |
| Port A Pin Y   | Clear PinY mode              | GPIOA->MODER &=~(3<<(Y*2))   |
| Port A Pin Y   | Set PinY mode = Output       | GPIOA->MODER \|= 1<<(Y*2)    |
| Port A Pin 5~9 | Clear Pin5~9 mode            | GPIOA->MODER &=~(3FF<<(5*2)) |
|                | Set Pin5~9 mode = Output     | GPIOA->MODER \|= 155<<(5*2)  |
| Port X Pin Y   | Clear Pin Y mode             | GPIOX->MODER &=~(3<<(Y*2))   |
|                | Set Pin Y mode = Output      | GPIOX->MODER \|= 1<<(Y*2)    |
| Port A Pin5    | Set Pin5 otype=push-pull     | GPIOA->OTYPER &= ~(1<<5)     |
| Port A PinY    | Set PinY otype=push-pull     | GPIOA-> OTYPER &= ~(1<<Y)    |
| Port A Pin5    | Set Pin5 ospeed=Fast         | GPIOA->OSPEEDR \|= 2<<(5*2)  |
| Port A PinY    | Set PinY ospeed=Fast         | GPIOA-> OSPEEDR \|= 2<<(Y*2) |
| Port A Pin 5   | Set Pin5 PUPD=no pullup/down | GPIOA->PUPDR &=~(3<<(5*2))   |
| Port A Pin Y   | Set PinY PUPD=no pullup/down | GPIOA-> PUPDR &=~(3<<(Y*2))  |

------

## Problem 0: Connection of 7-Segment Display and Decoder

### Procedure

Review 7-segment Decoder and Display from Digital Logic lecture.

- Read here: [7-segment tutorial](https://ykkim.gitbook.io/ec/ec-course/tutorial/tutorial-7segment-display)
- Read here: [How to connect 7-segment decoder to MCU](https://ykkim.gitbook.io/ec/ec-course/hardware/experiment-hardware/electronic-chips#7-segment-and-decoder)

#### 1. 7-segment display connection

First, connect the common anode 7-segment display with the given array resistors.

Then, apply VCC and GND to the 7-segment display.

Check that all LEDs of 7-segment work properly

- Give 'H' signal to each 7-segment pin of 'a'~'g' . Observe if that LED is turned ON or OFF
- Example: Connect VCC to all 'a'~'g' pins

#### 2. BCD 7-segment decoder connection

The popular BCD 7-segment decoder chip is **74LS47.** With the BCD chip, you need only 4 DOUT pins of MCU to display from 0 to 9.

Connect the decoder chip (**74LS47**) on the bread board.

<img src="./images/7segment.png" width="500" height="300"/>





Then, Check that the decoder chip works properly

- Supply a combination of VCC/GND to the pins of 'A'~'D' of the decoder.
- Check if the 7-segment LED display shows the correct number

#### Connection Diagram

Circuit diagram

<img src="./images/circuit_breadboard.png" width="500" height="400"/>

#### Discussion

1. Draw the truth table for the BCD 7-segment decoder with the 4-bit input.

   |  A   |  B   |  C   |  D   | num  |  a   |  b   |  c   |  d   |  e   |  f   |  g   |
   | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  1   |
   |  0   |  0   |  0   |  1   |  1   |  1   |  0   |  0   |  1   |  1   |  1   |  1   |
   |  0   |  0   |  1   |  0   |  2   |  0   |  0   |  1   |  0   |  0   |  1   |  0   |
   |  0   |  0   |  1   |  1   |  3   |  0   |  0   |  0   |  0   |  1   |  1   |  0   |
   |  0   |  1   |  0   |  0   |  4   |  1   |  0   |  0   |  1   |  1   |  0   |  0   |
   |  0   |  1   |  0   |  1   |  5   |  0   |  1   |  0   |  0   |  1   |  0   |  0   |
   |  0   |  1   |  1   |  0   |  6   |  0   |  1   |  0   |  0   |  0   |  0   |  0   |
   |  0   |  1   |  1   |  1   |  7   |  0   |  0   |  0   |  1   |  1   |  0   |  1   |
   |  1   |  0   |  0   |  0   |  8   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |
   |  1   |  0   |  0   |  1   |  9   |  0   |  0   |  0   |  0   |  1   |  0   |  0   |



2. What are the common cathode and common anode of 7-segment display?

> ​	A 7-segment display comes in two main types: Common Anode and Common Cathode. In a Common Anode display, all the anode (+) pins of the segments are connected to the positive voltage (VCC), meaning that to turn on a specific segment, you need to apply a LOW signal to its corresponding pin. This configuration allows the segment to light up when it receives a low voltage. On the other hand, a Common Cathode display connects all the cathode (-) pins to ground (GND). Here, each segment is activated by applying a HIGH signal to its pin, allowing it to turn on when it receives a positive voltage. 



3. Does the LED of a 7-segment display (common anode) pin turn ON when 'HIGH' is given to the LED pin from the MCU?

> ​	No, in a common anode 7-segment display, the LED segment will not turn ON when a 'HIGH' signal is given to its pin. In this configuration, all the anodes of the LEDs are connected to VCC (positive voltage), so to turn ON a specific segment, you need to apply a 'LOW' signal (0V) to that segment's pin. This creates a potential difference that allows current to flow from the anode to the cathode, lighting up the segment. Therefore, to activate a segment in a common anode display, you must provide a LOW signal from the MCU.

------

## Problem 1: Display a Number with Button Press

### Procedure

1. Create a new project under the directory `\repos\EC\LAB\LAB_GPIO_7segment`

- The project name is “**LAB_GPIO_7segment”.**

- Create a new source file named as “**LAB_GPIO_7segment.c”**

- Refer to the [sample code](https://github.com/ykkimhgu/EC-student/tree/main/tutorial/tutorial-student)

  > You MUST write your name on the source file inside the comment section.

2. Include your updated library in `\repos\EC\lib\` to your project.

- **ecGPIO.h, ecGPIO.c**
- **ecRCC.h, ecRCC.c**

3. Declare and Define the following functions in your library

```c
void sevensegment_display_init(PinNames_t pinNameA, PinNames_t pinNameB, PinNames_t pinNameC, PinNames_t pinNameD); 
void sevensegment_display(uint8_t  num);
```

- num: 0 to 9 only (unsigned)

4. Configure and connect the MCU to the circuit

5. First, check that every number, 0 to 9, can be displayed properly

6. Then, create a code that increase the displayed number from 0 to 9 with each button press.

- After the number '9', it should start from '0' again.

### Configuration

Configure the MCU

| Digital In for Button (B1) | Digital Out for 7-Segment                     |
| :------------------------- | :-------------------------------------------- |
| Digital In                 | Digital Out                                   |
| PC13                       | PA7, PB6, PC7, PA9                            |
| PULL-UP                    | Push-Pull, No Pull-up-Pull-down, Medium Speed |

#### Code

[**Sample Code**](https://ykkim.gitbook.io/ec/stm32-m4-programming/example-code#seven-segment).

```c
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
```

Your code goes here: [ADD Code LINK such as github](https://github.com/ykkimhgu/EC-student/)

> Explain your source code with necessary comments.

```c
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
	// (segments & 0b0001): checks each bit of the segment value.
    //if those bits are 1, segment should be HIGH.
    //if those bits are 0, segment should be LOW.
}

void delay_ms(int ms) {
    for(int i = 0; i < ms * 1000; i++);  // Approximate delay
}

```

### Results

Experiment images and results

<img src="./images/Problem1_result_image.jpg" width="500" height="400"/>

[demo video link](https://youtube.com/shorts/SunMrLusPfs?feature=share)

### Discussion

This project's main goal is to control the 7-segment display using the NUCLEO-F411RE microcontroller effectively. The resulting system successfully increases the numbers from 0 to 9 sequentially by pressing the button. 

The status check and delay mechanism introduced for debouncing prevents incorrect input, such as the vibration of the button or the time when the button is pressed.

It will be possible to expand the functionality of the system through various input methods such as infrared sensors, accelerometers, and sound detection instead of buttons as input.

------

## Problem 2: Program BCD-7-segment decoder

Instead of using the decoder chip, we are going to make the 7-segment decoder with the MCU programming.

> Do not use the 7-segment decoder for this problem

<img src="./images/7segment_wo_decoder.png" width="400" height="350"/>

### Procedure

1. Use the same project and source file.
2. Include your updated library in `\repos\EC\lib\` to your project.

- **ecGPIO.h, ecGPIO.c**
- **ecRCC.h, ecRCC.c**

3. Declare and Define the following functions in your library

```c
void sevensegment_decoder_init(void); 
void sevensegment_decoder(uint8_t  num);
```

- num: 0 to 9 only (unsigned)

4. Configure and connect the MCU to the circuit

5. First, check that every number, 0 to 9, can be displayed properly

6. Then, create a code that increases the displayed number from 0 to 9 with each button press.

- After the number '9', it should start from '0' again.

### Configuration

Configure the MCU

| Digital In for Button (B1) | Digital Out for 7-Segment                                    |
| :------------------------- | :----------------------------------------------------------- |
| Digital In                 | Digital Out                                                  |
| PC13                       | PA5, PA6, PA7, PB6, PC7, PA9, PA8, PB10 ('a'~'h', respectively) |
| PULL-UP                    | Push-Pull, No Pull-up-Pull-down, Medium Speed                |

### Code

Your code goes here: [ADD Code LINK such as github](https://github.com/ykkimhgu/EC-student/)

- [Example Code for MCU configuration](https://github.com/ykkimhgu/EC-student/blob/main/tutorial/tutorial-student/TU_GPIO_LED_7segment_student.c)
- [Example code of 7-segment decoder control](https://os.mbed.com/users/ShingyoujiPai/code/7SegmentDisplay/file/463ff11d33fa/main.cpp/)

> Main code

```c
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
		sevensegment_decoder(count % 10);
		
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
	sevensegment_decoder_init();
}
```



> Source code

```
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
    for(int i = 0; i < ms * 1000; i++); 
}
```

### Connection Diagram

Circuit diagram

> You need to include the circuit diagram

<img src="./images/7segment_wo_decoder.png" width="400" height="350"/>

### Results

Experiment images and results

<img src="./images/Problem2_result_image.jpg" width="500" height="350"/>

[demo video link](https://youtube.com/shorts/VPqnIqp76k4?feature=share)

### Discussion

The results of this project show that a 7-segment display can be effectively controlled using a NUCLEO-F411RE microcontroller. Specifically, the segment was controlled with eight pins directly, without using a dedicated decoder. The implemented system successfully performs the function of sequentially increasing the numbers from 0 to 9 by pressing the button, each of which appears on the display accurately.

A debounce function has been introduced to increase the stability of button input, which is critical to preventing incorrect input. It minimizes malfunctions caused by vibration or noise that can occur when the button is pressed.

------

## Reference

Complete list of all references used (github, blog, paper, etc)

[ToyMakers_blog](https://m.blog.naver.com/yulian/221717963553)

[Arduino_blog](https://kogun.tistory.com/18)

[Decoder_blog](https://vedacube.tistory.com/254)

[ykkim_gitbook](https://ykkim.gitbook.io/ec/ec-course/hardware/experiment-hardware/electronic-chips#7-segment-and-decoder)

[Datasheet](file:///C:/Users/User/Downloads/SN54LS47%20(2).PDF)



------

## Troubleshooting

Complicating code can make it harder to understand and find errors.
Reducing duplication of code and simplifying code by using arrays and iterations will increase readability and maintenance.
