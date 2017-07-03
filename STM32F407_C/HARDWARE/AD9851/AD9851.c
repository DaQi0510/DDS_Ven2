#include "AD9851.h"
#include "lcd.h"

/*
	PA0->D0
	PC2->D1
	PC7->D2
	PF7->D3
	PA7->D4
	PA6->D5
	PA2->D6
	PA1->D7
	PF5->FQUD
	PF6->WCLK
	PF4->RST
*/
void AD9851S_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO	
	
	AD9851S_WCLK_CLR ;
	Delayss();
  AD9851S_FQUD_CLR ;
	Delayss();
  //RST信号
  AD9851S_RST_CLR ;
	Delaysl();
  AD9851S_RST_SET ;
  Delaysl();
  AD9851S_RST_CLR ;
	Delaysl();
}
void AD9851S_Reset(void)
{
	AD9851S_WCLK_CLR;
	AD9851S_FQUD_CLR;
  AD9851S_RST_CLR;
	AD9851S_RST_SET;
	Delaysl();
	AD9851S_RST_CLR;
  
}
void AD9851S_SetFreq(u8 W0,unsigned long Freq)    //设置AD9851频率，W0 00000001 
{
	u8 data;
	unsigned long Wdata;
	Wdata =Freq *(28.63311531);
	data=W0;         //写W0；
	AD9851S_SetData(data);
	Delayss();
	AD9851S_WCLK_SET;
	Delayss();
	AD9851S_WCLK_CLR ;
	Delayss();
	
	data=Wdata>>24; //写W1   
	AD9851S_SetData(data);
	Delayss();
	AD9851S_WCLK_SET;
	Delayss();
	AD9851S_WCLK_CLR ;
	Delayss();
	
	data=Wdata>>16; //写W2
	AD9851S_SetData(data);
	Delayss();
	AD9851S_WCLK_SET;
	Delayss();
	AD9851S_WCLK_CLR ;
	Delayss();
	
	data=Wdata>>8; //写W3   
	AD9851S_SetData(data);
	Delayss();
	AD9851S_WCLK_SET;
	Delayss();
	AD9851S_WCLK_CLR ;
	Delayss();
	
	data=Wdata; //写W4
	AD9851S_SetData(data);
	Delayss();
	AD9851S_WCLK_SET;
	Delayss();
	AD9851S_WCLK_CLR ;
	Delayss();
	
	AD9851S_FQUD_SET ;
	Delaysl();
	AD9851S_FQUD_CLR ;	
}

void AD9851S_SetData(u8 data)  //设置AD9851并行接口数值
{
	if(data&1<<0)
		AD9851S_D0=1;
	else
		AD9851S_D0=0;
	if(data&1<<1)
		AD9851S_D1=1;
	else
		AD9851S_D1=0;
	if(data&1<<2)
		AD9851S_D2=1;
	else
		AD9851S_D2=0;
	if(data&1<<3)
		AD9851S_D3=1;
	else
		AD9851S_D3=0;
	if(data&1<<4)
		AD9851S_D4=1;
	else
		AD9851S_D4=0;
	if(data&1<<5)
		AD9851S_D5=1;
	else
		AD9851S_D5=0;
	if(data&1<<6)
		AD9851S_D6=1;
	else
		AD9851S_D6=0;
	if(data&1<<7)
		AD9851S_D7=1;
	else
		AD9851S_D7=0;
}


/*
	PE1->D0
	PE0->D1
	PB9->D2
	PB8->D3
	PE2->D4
	PE3->D5
	PE4->D6
	PE5->D7
	PF0->FQUD
	PC13->WCLK
	PE6->RST
*/
void AD9851Z_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO	
	
	AD9851Z_WCLK_CLR ;
	Delayss();
  AD9851Z_FQUD_CLR ;
	Delayss();
  //RST信号
  AD9851Z_RST_CLR ;
	Delaysl();
  AD9851Z_RST_SET ;
  Delaysl();
  AD9851Z_RST_CLR ;
	Delaysl();
}
void AD9851Z_SetFreq(u8 W0,unsigned long Freq)    //设置AD9851频率，W0 00000001 
{
	u8 data;
	unsigned long Wdata;
	Wdata =Freq *(28.63311531);

	data=W0;         //写W0；
	AD9851Z_SetData(data);
	AD9851Z_WCLK_SET;
	Delayss();
	AD9851Z_WCLK_CLR ;
	Delayss();
	
	data=Wdata>>24; //写W1 ;	
	AD9851Z_SetData(data);
	AD9851Z_WCLK_SET;
	Delayss();
	AD9851Z_WCLK_CLR ;
	Delayss();
	
	data=Wdata>>16; //写W2
	AD9851Z_SetData(data);
	AD9851Z_WCLK_SET;
	Delayss();
	AD9851Z_WCLK_CLR ;
	Delayss();
	
	data=Wdata>>8; //写W3    
	AD9851Z_SetData(data);
	AD9851Z_WCLK_SET;
	Delayss();
	AD9851Z_WCLK_CLR ;
	Delayss();
	
	data=Wdata; //写W4
	AD9851Z_SetData(data);
	AD9851Z_WCLK_SET;
	Delayss();
	AD9851Z_WCLK_CLR ;
	Delayss();
	
	AD9851Z_FQUD_SET ;
	Delaysl();
	AD9851Z_FQUD_CLR ;	
	Delaysl();
}

void AD9851Z_SetData(u8 data)  //设置AD9851并行接口数值
{
	if(data&1<<0)
		AD9851Z_D0=1;
	else
		AD9851Z_D0=0;
	if(data&1<<1)
		AD9851Z_D1=1;
	else
		AD9851Z_D1=0;
	if(data&1<<2)
		AD9851Z_D2=1;
	else
		AD9851Z_D2=0;
	if(data&1<<3)
		AD9851Z_D3=1;
	else
		AD9851Z_D3=0;
	if(data&1<<4)
		AD9851Z_D4=1;
	else
		AD9851Z_D4=0;
	if(data&1<<5)
		AD9851Z_D5=1;
	else
		AD9851Z_D5=0;
	if(data&1<<6)
		AD9851Z_D6=1;
	else
		AD9851Z_D6=0;
	if(data&1<<7)
		AD9851Z_D7=1;
	else
		AD9851Z_D7=0;
}
void Delayss(void)    //短延时
{
	u8 i,j;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++);
}
void Delaysl(void)   //长延时
{
	u8 i,j;
	for(i=0;i<200;i++)
		for(j=0;j<200;j++);
}
