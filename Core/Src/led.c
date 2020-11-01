/*
 * manage_pin.c
 *
 *  Created on: 22 дек. 2019 г.
 *      Author: sguss
 */
#include "main.h"

//#define STM32F401CCU
#define STM32F407VET
//#define STM32F769NI


#ifdef STM32F401CCU
#define LED1_PIN  			13
#define GPIO_PORT 			GPIOC
#define ENABLE_LED_BUS 		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN
#define ENABLE_LED_PIN_1	GPIOC->MODER |= GPIO_MODER_MODER13_1
#define LED_1_LIGTH			GPIOC->BSRR |= GPIO_BSRR_BR_13
#define LED_1_DARK			GPIOC->BSRR |= GPIO_BSRR_BS_13
#endif


#ifdef STM32F407VET

//both leds - red
#define LED1_PIN	 6
#define LED2_PIN	 7
#define GPIO_PORT	 GPIOA
#define ENABLE_LED_BUS 		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define ENABLE_LED_PIN_1	GPIOA->MODER |= GPIO_MODER_MODER6_0
#define ENABLE_LED_PIN_2	GPIOA->MODER |= GPIO_MODER_MODER7_0
#define LED_1_LIGTH			GPIOA->BSRR |= GPIO_BSRR_BR_6
#define LED_1_DARK			GPIOA->BSRR |= GPIO_BSRR_BS_6
#define LED_2_LIGTH			GPIOA->BSRR |= GPIO_BSRR_BR_7
#define LED_2_DARK			GPIOA->BSRR |= GPIO_BSRR_BS_7

#endif

#ifdef STM32F769NI

#define LED1_PIN	 5
#define LED2_PIN	 13
#define GPIO_PORT	 GPIOJ
#define LED3_PIN	 12 // GPIOA
#define LED4_PIN	 4  // GPIOA
// set clock for port J
#define ENABLE_LED_BUS 		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN
#define ENABLE_LED_PIN_1	GPIOJ->MODER |= GPIO_MODER_MODER5_1
#define ENABLE_LED_PIN_2	GPIOJ->MODER |= GPIO_MODER_MODER13_1
#define LED_1_LIGTH			GPIOJ->BSRR |= GPIO_BSRR_BR_5
#define LED_1_DARK			GPIOJ->BSRR |= GPIO_BSRR_BS_5
#define LED_2_LIGTH			GPIOJ->BSRR |= GPIO_BSRR_BR_13
#define LED_2_DARK			GPIOJ->BSRR |= GPIO_BSRR_BS_13

#endif



int	init_led1 = 0;
int init_led2 = 0;
int ligth1 = 0;
int ligth2 = 0;

void led1_on(){
	if(!init_led1){
		ENABLE_LED_BUS;
		ENABLE_LED_PIN_1;
		init_led1=1;
		ligth1=0;
	}
	if(!ligth1){
		LED_1_LIGTH;
		ligth1=1;
	}
}

void led1_off(){
if(ligth1){
	LED_1_DARK;
	ligth1=0;
}
}

void led2_on(){
	if(!init_led2){
		ENABLE_LED_BUS;
		ENABLE_LED_PIN_2;
		init_led2=1;
		ligth2=0;
	}
	if(!ligth2){
		LED_2_LIGTH;
		ligth2=1;
	}
}

void led2_off(){
if(ligth2){
	LED_2_DARK;
	ligth2=0;
}
}
