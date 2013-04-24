/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: work.h
* Type: C header file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/ 
//-------------------- Defines ------------------------------------------------
/** Led port */
#define LED_PORT GPIOD
///** Led pins */
#define GREEN_LED GPIO_Pin_12
#define ORANGE_LED GPIO_Pin_13
#define RED_LED GPIO_Pin_14
#define BLUE_LED GPIO_Pin_15
#define ALL_LEDS (GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED)
/* main work function */
void work(void);
