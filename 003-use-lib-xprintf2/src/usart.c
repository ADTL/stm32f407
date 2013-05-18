/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: usart.c
* Type: C code file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/
/* include headers */
#include "stm32f4xx.h"
#include "usart.h"
#include "xprintf.h"
#include "gpio_af.h"
/*USARTx send byte */
void usart_sendb(USART_TypeDef * USART, char byte) {
    while ((USART->SR & USART_SR_TXE) == 0);
    USART->DR = byte;
}
/*USART1 send byte */
void ser1_sendb(unsigned char byte) {
    usart_sendb(USART1, byte);
}
/*USART1 setup */
void usart1_setup(void) {
    /* enable usart port*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    /* enable usart1 */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    /* setup usart1 pins to af mode */
    GPIOB->MODER |= GPIO_MODER_MODER6_1;
    /* select af block usart1..3(af7 function) to usart pins */
    GPIOB->AFR[0] |= (GPIO_AF7_USART1_3 << GPIO_AFP6);
    /* usart1 setup baudrate */ /** 115200 baud 16MHz/16/115200 = 8.68 */
    USART1->BRR = (8 << 4) + 5;
    /* usart1 enable block and enable tx line */
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_UE;
    /* preinit xprintf lib
     * route xprintf output function to ser1_sendb function
     */
    xdev_out(ser1_sendb);
}