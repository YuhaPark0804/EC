---
description: EC_HAL API
---


# Embedded Controller - STM32f411 HAL API

Documentation for HAL functions

Written by: Yuha Park

Course:   Embedded Controller

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10

MCU:  STM32F411RE (Nucleo-64)



---

[TOC]

  * [GPIO Digital In/Out](#gpio-digital-inout)
    + [Header File](#header-file)
    + [GPIO_init\(\)](#gpio_init)
    + [GPIO_mode\(\)](#gpio_mode)
    + [GPIO_write\(\)](#gpio_write)
    + [GPIO_read\(\)](#gpio_read)
    + [GPIO_ospeed\(\)](#gpio_ospeed)
    + [GPIO_otype\(\)](#gpio_otype)
    + [GPIO_pupd\(\)](#gpio_pupd)
    + [sevensegment_display_init\(\)](#sevensegment_display_init)
    + [sevensegment_display\(\)](#sevensegment_display)
    + [sevensegment_decoder_init\(\)](#sevensegment_decoder_init)
    + [sevensegment_decoder\(\)](#sevensegment_decoder)
    + [delay_ms\(\)](#delay_ms)

---

## GPIO Digital InOut 

### Header File

 `#include "ecGPIO2.h"`


```c++
#include "stm32f411xe.h"
#include "ecRCC2.h"
#include "ecPinNames.h"

#ifndef __ECGPIO2_H
#define __ECGPIO2_H

// IDR & ODR
#define HIGH 		1
#define LOW  		0

//MODER
typedef enum {INPUT  = 0b00, 
              OUTPUT = 0b01,
              AF     = 0b10,
              ANALOG = 0b11
}GPIO_MODE;

//OSPEEDR
typedef enum {LOW_SPEED    = 0b00, 
              MEDIUM_SPEED = 0b01, 
              FAST_SPEED   = 0b10, 
              HIGH_SPEED   = 0b11
}GPIO_SPEED;

//OTYPER
typedef enum {PUSH_PULL  = 0, 
              OPEN_DIAIN = 1
}GPIO_TYPE;


//PUPDR
typedef enum {NO_PUPD   = 0b00, 
              PULL_UP   = 0b01, 
              PULL_DOWN = 0b10, 
              RESERVED  = 0b11
}GPIO_PUPD;

// PIN
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
void sevensegment_off(void);

//7-segment decoder: problem 2
void sevensegment_decoder_init(void); 
void sevensegment_decoder(uint8_t  num);

//TU_Systick: LED toggle
void LED_toggle(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
```




### GPIO_init\(\)

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```c++
void GPIO_init(PinName_t pinName, uint32_t mode);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15

* **mode**:   INPUT(0), OUTPUT(1),  AF(02), ANALOG (03)

  

**Example code**

```c++
GPIO_init(pinNameA, OUTPUT);
GPIO_init(BUTTON_PIN, INPUT);
```



### GPIO_mode\(\)

Configures  GPIO pin modes: In/Out/AF/Analog

```c++
void GPIO_mode(PinName_t pinName, uint32_t mode);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15

* **mode**:   INPUT (0), OUTPUT (1),  AF(02), ANALOG (03)

  

**Example code**

```c++
GPIO_mode(pinNameA, OUTPUT);
```



### GPIO_write\(\)

Write the data to GPIO pin: High, Low

```c++
void GPIO_write(PinName_t pinName, int Output);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15
* **output**:   LOW(0), HIGH(1)



**Example code**

```c++
GPIO_write(LED_PIN5, HIGH); 
```



### GPIO_read\(\)

Read the data from GPIO pin

```c++
int GPIO_read(PinName_t pinName);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15



**Example code**

```c++
GPIO_read(BUTTON_PIN);
```



### GPIO_ospeed\(\)

Configures  output speed of GPIO pin : Low, Mid, Fast, High

```c++
void GPIO_ospeed(PinName_t pinName, int speed);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15
* **speed**:   LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2) , HIGH_SPEED(3)



**Example code**

```c++
GPIO_ospeed(pinNameB, MEDIUM_SPEED);
```



### GPIO_otype\(\)

Configures  output type of GPIO pin: Push-Pull / Open-Drain

```c++
void GPIO_otype(PinName_t pinName, int type);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15
* **type**:   PUSH_PULL(0), OPEN_DRAIN(1)



**Example code**

```c++
GPIO_otype(pinNameA, PUSH_PULL);
```



### GPIO_pupd\(\)

Configures  Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c++
void GPIO_pupd(PinName_t pinName, int pupd);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15
* **pupd**:   NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), RESERVED(3)



**Example code**

```c++
GPIO_pupd(pinNameA, NO_PUPD);
```


### sevensegment_display_init\(\)

Indicates the initialization status of the 7-segment display.

```c++
void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD);
```

**Parameters**

* **pinName**
  * Port:  Port Number,  GPIOA~GPIOH

  * pin:  pin number (int) 0~15



**Example code**

```c++
sevensegment_display_init(PA_7, PB_6, PC_7, PA_9);  // Decoder input A,B,C,D
```



### sevensegment_display\(\)

Depending on the input number, the four pins will be in the high or low state.

```c++
void sevensegment_display(uint8_t  num);
```

**Parameters**

* **num**: Number of counts in 7 segments (0 ~ 9)
  



**Example code**

```c++
sevensegment_display(count % 10); //count = 0 ~ 9
```



### sevensegment_decoder_init\(\)

Indicates the initialization status of the 7-segment display without a decoder.

```c++
void sevensegment_decoder_init(void);
```

**Parameters**

* **No parameters** 


**Example code**

```c++
sevensegment_decoder_init(); // Use one button pin and eight led pins in 7-segment.
```


### sevensegment_decoder\(\)

When the button is pressed, the eight pins of the 7-segment (without a decoder) will be high or low depending on the count.

```c++
void sevensegment_decoder(uint8_t  num);
```

**Parameters**

* **num**: Number of counts in 7 segments (0 ~ 9)
  



**Example code**

```c++
sevensegment_decoder(count % 10); //count = 0 ~ 9
```




### delay_ms\(\)

Delays for debounceing processing.

```c++
void delay_ms(int ms);
```

**Parameters**

* **ms**: Delays execution by milliseconds by the value given in the parameter.
  



**Example code**

```c++
delay_ms(200);  // delays 0.2 [s]
```


### sevensegment_off\(\)

Turn off sevensegment.

```c++
void sevensegment_off(void);
```

**Parameters**

* **No parameters**
  

**Example code**

```c++
sevensegment_off();
```



------



## Class or Header name

### Function Name

```text

```

**Parameters**

* p1
* p2

**Example code**

```text

```
