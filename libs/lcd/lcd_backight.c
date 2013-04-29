#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "lcd_internal.h"
/* Setup backlight for LCD*/
void lcd_backlight_setup(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 99;
    TIM_TimeBaseStructure.TIM_Prescaler = 10;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
    
    TIM_Cmd(TIM5, ENABLE);
}
/* Set backlight */
void lcd_set_backlight(uint8_t brightness) {
    uint16_t temp_brightness;
    if (brightness == BACKLIGHT_ON) {
	TIM_Cmd(TIM5, ENABLE);
    }
    if (brightness == BACKLIGHT_OFF) {
	TIM5->CCR2 = 0;
	TIM_Cmd(TIM5, DISABLE);
    }
    if (brightness > 0) {
	temp_brightness = brightness * 10 / 100 * 75 / 10;
	TIM5->CCR2 = temp_brightness;
    }
    
}
