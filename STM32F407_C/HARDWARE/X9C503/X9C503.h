#ifndef __X9C503_H
#define __X9C503_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"

#define X9C503_CS   PFout(1)
#define X9C503_INC  PFout(2)
#define X9C503_UD   PFout(3)

void X9C503_Init(void);
void X9C503_SetValue(u8 Value);   //…Ë÷√X9C503µƒ÷µ
void Delaysss(void);
void Voltage_Init(void);
void SetVoltage(void);
void DAC_Sine_Init(void);
void TIM6_Config(void);
void DAC_Ch1_EscalatorConfig(void);
#endif
