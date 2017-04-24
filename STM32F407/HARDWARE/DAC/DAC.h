#ifndef __DAC_H
#define __DAC_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dac.h"

void sin_Generation1(u16 Fre,u16 Vol);
void sin_Generation2(u16 Fre,u16 Vol);
void TIM6_Configuration(u16 Fre);
void TIM7_Configuration(u16 Fre);
void GPIO_Configuration1(void);
void GPIO_Configuration2(void);
void DAC_DMA_Configuration1(void);
void DAC_DMA_Configuration2(void);
void TIM1_PWM_Init(u32 arr,u32 psc);
#endif
