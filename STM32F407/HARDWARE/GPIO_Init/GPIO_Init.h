#ifndef __GPIO_Init_H
#define __GPIO_Init_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"

#define AD1  PCout(7)      
#define AD2  PCout(6) 
#define AD3  PGout(7)      
#define AD4  PGout(6) 
#define AD5  PGout(3)      
#define AD6  PGout(2) 
#define AD7  PDout(15)      
#define AD8  PDout(14) 

#define S18  PDout(10) 
#define S19  PDout(11)      
#define S22  PDout(12) 

#define K1  PDin(2) 
#define K2  PDin(3)      
#define K3  PDin(4) 



#define B1  PAin(12) 
#define B2  PGin(5)
#define B3  PCin(9) 
#define B4  PEin(4)
#define B5  PEin(3) 
#define B6  PEin(2)

#define Relays PGin(11)
#define Relay_On PGout(10)=0
#define Relay_Off PGout(10)=1
void Gpio_Init(void);
void Delays(void);    //延时消抖
void SetAD(u8 SetNum);    //完成模数转换

#endif

