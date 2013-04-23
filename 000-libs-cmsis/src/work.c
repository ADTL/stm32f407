/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: work.c
* Type: C code file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/
/* includes */
#include "stm32f4xx.h"
#include "work.h"
/* main work function */
void work(void) {
    /* enable led port */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    /* set led pins to output state */
    LED_PORT->MODER |=
    	GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 |
	GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
    /* enable leds */
    LED_PORT->ODR |= ALL_LEDS;
    /* infinity loop */
    while (1);
}
