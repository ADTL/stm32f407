/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: work.c
* Type: C code file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/
/* includes */
#include "stm32f4xx.h"
#include "usart.h"
#include "xprintf.h"
/* main work function */
void work(void) {
    const char message[] = "Hello work";
    /* setup serial console */
    usart1_setup();
    /* printf message and it length */
    xprintf("Message: %s, Len: %d\r\n", message, sizeof(message));
    /* infinity loop */
    while (1);
}