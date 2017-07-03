#ifndef __AD9851_H
#define __AD9851_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"

#define AD9851S_D0  PAout(0)
#define AD9851S_D1  PCout(2)
#define AD9851S_D2  PCout(1)
#define AD9851S_D3  PFout(7)
#define AD9851S_D4  PAout(7)
#define AD9851S_D5  PAout(6)
#define AD9851S_D6  PAout(2)
#define AD9851S_D7  PAout(1)

#define AD9851S_RST_CLR  PFout(4)=0
#define AD9851S_RST_SET  PFout(4)=1  

#define AD9851S_WCLK_CLR  PFout(6)=0
#define AD9851S_WCLK_SET  PFout(6)=1 

#define AD9851S_FQUD_CLR  PFout(5)=0
#define AD9851S_FQUD_SET  PFout(5)=1 

void AD9851S_Init(void);
void AD9851S_Reset(void);
void AD9851S_SetFreq(u8 W0,unsigned long Freq);    //设置AD9851频率，W0 00000001 
void AD9851S_SetData(u8 data);  //设置AD9851并行接口数值
 
void Delayss(void);    //短延时
void Delaysl(void);    //长延时

#define AD9851Z_D0  PEout(1)
#define AD9851Z_D1  PEout(0)
#define AD9851Z_D2  PBout(9)
#define AD9851Z_D3  PBout(8)
#define AD9851Z_D4  PEout(2)
#define AD9851Z_D5  PEout(3)
#define AD9851Z_D6  PEout(4)
#define AD9851Z_D7  PEout(5)

#define AD9851Z_RST_CLR  PEout(6)=1
#define AD9851Z_RST_SET  PEout(6)=0  

#define AD9851Z_WCLK_CLR  PCout(13)=0
#define AD9851Z_WCLK_SET  PCout(13)=1 

#define AD9851Z_FQUD_CLR  PFout(0)=0
#define AD9851Z_FQUD_SET  PFout(0)=1

void AD9851Z_Init(void);
void AD9851Z_SetFreq(u8 W0,unsigned long Freq);    //设置AD9851频率，W0 00000001 
void AD9851Z_SetData(u8 data);  //设置AD9851并行接口数值

#endif
