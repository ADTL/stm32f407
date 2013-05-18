/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: usart.h
* Type: C header file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/  
/*USARTx send byte */
void usart_sendb(USART_TypeDef * USART, char byte);
/*USART1 send byte */
void ser1_sendb(unsigned char byte);
/*USART1 setup */
void usart1_setup(void);