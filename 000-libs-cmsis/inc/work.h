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
/** Led pins */
#define GREEN_LED (1 << 12)
#define ORANGE_LED (1 << 13)
#define RED_LED (1 << 14)
#define BLUE_LED (1 << 15)
#define ALL_LEDS (GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED)

/* main work function */
void work(void);
