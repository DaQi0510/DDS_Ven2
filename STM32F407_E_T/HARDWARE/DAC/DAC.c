#include "DAC.h"
#include "math.h"
#include "GPIO_Init.h"
#define DAC_DHR12R1_ADDRESS     0x40007408
#define DAC_DHR12R2_ADDRESS     0x40007414

extern volatile u16 tableSize1;
volatile u16 sinTable1[1000];
volatile	u16 sinTable[1000];
extern volatile u16 tableSize2;
volatile u16 sinTable2[1000];
extern volatile u8 K3_Flagt;
extern volatile u8 S19_Flag;
volatile u8 Flag=0;
void sin_Generation1(u16 Fre,u16 Vol)
{
	u32 Voltage;
	u16 n;
	if(Vol>500)
		Vol =500;
	Voltage= Vol*4095/500;
	for(n=0;n<500;n++)
	{
		sinTable1
		[n] =n*Voltage/499;	
	}
	for(n=500;n<1000;n++)
	{
		sinTable1[n] =Voltage-(n-500)*Voltage/499;	
	}
//	for(n=0;n<973;n++)
//	{
//		sinTable1[n]=sinTable[n+27];
//	}
//	for(n=0;n<27;n++)
//	{
//		sinTable1[n+973]=sinTable[n];
//	}
}
void sin_Generation2(u16 Fre,u16 Vol)
{
	u32 Voltage;
	u16 n;
	if(Vol>500)
		Vol =500;
	Voltage= Vol*4095/500;
	for(n=0;n<500;n++)
	{
		sinTable2[n] =n*Voltage/499;	
	}
	for(n=500;n<1000;n++)
	{
		sinTable2[n] =Voltage-(n-500)*Voltage/499;	
	}
	
}
void TIM2_Configuration(u16 Fre)
{
//	  GPIO_InitTypeDef GPIO_InitStructure;
//	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	  TIM_OCInitTypeDef  TIM_OCInitStructure;
//	  NVIC_InitTypeDef NVIC_InitStructure;
//	  TIM_DeInit(TIM2);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
		TIM_PrescalerConfig(TIM2,1, TIM_PSCReloadMode_Update);
		TIM_SetAutoreload(TIM2, Fre);
		TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
//		TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
		TIM_Cmd(TIM2, ENABLE);


//  TIM_DeInit(TIM3);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//	
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOF9复用为定时器14
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOF9
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;        //上拉
//	GPIO_Init(GPIOB,&GPIO_InitStructure); 
//	
//	
//	
//	
//  TIM_TimeBaseInitStructure.TIM_Period =499; 	//自动重装载值
//	TIM_TimeBaseInitStructure.TIM_Prescaler=0;  //定时器分频
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
//	
//	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);
//  TIM_SelectInputTrigger(TIM3, TIM_TS_ITR1);
//	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
//	
////	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断

//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
// 
//  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
//  TIM_SetCompare4(TIM3,0);
//	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	  
		
}
void TIM7_Configuration(u16 Fre)
{

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);	
		TIM_PrescalerConfig(TIM7,1, TIM_PSCReloadMode_Update);
		TIM_SetAutoreload(TIM7, Fre);
		TIM_SelectOutputTrigger(TIM7, TIM_TRGOSource_Update);
		TIM_Cmd(TIM7, ENABLE);
}

void GPIO_Configuration1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void GPIO_Configuration2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void DAC_DMA_Configuration1(void)
{
	DAC_InitTypeDef  DAC_InitStructure;	

	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sinTable1;
	DMA_InitStructure.DMA_BufferSize = 1000;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);    
	
	DMA_Cmd(DMA1_Stream5, ENABLE);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);
	
	DAC_DMACmd(DAC_Channel_1, ENABLE);
	
} 

void DAC_DMA_Configuration2(void)
{
	DAC_InitTypeDef  DAC_InitStructure;	

	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T7_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	DMA_DeInit(DMA1_Stream6);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R2_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sinTable2;
	DMA_InitStructure.DMA_BufferSize = 1000;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);    
	if(K3_Flagt==1)
	{
		DMA_Cmd(DMA1_Stream6, ENABLE);
		DAC_Cmd(DAC_Channel_2, ENABLE);
		DAC_DMACmd(DAC_Channel_2, ENABLE);
	}
	else
	{
		DMA_Cmd(DMA1_Stream6, DISABLE);
		DAC_Cmd(DAC_Channel_2, DISABLE);
		DAC_DMACmd(DAC_Channel_2, DISABLE);
	}
} 

void Sine_Set1(u16 Fre,u16 Vol)
{
	u16 FreNum;
	sin_Generation1(Fre,Vol);
	FreNum=42000000/tableSize1/Fre-1;
	TIM2_Configuration(FreNum);
	DAC_DMA_Configuration1();
}
void Sine_Set2(u16 Fre,u16 Vol)
{
	u16 FreNum;
	sin_Generation2(Fre,Vol);
	FreNum=42000000/tableSize2/Fre-1;
	TIM7_Configuration(FreNum);
	DAC_DMA_Configuration2();
}
void TIM1_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);    //TIM4时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTF时钟	
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PF9
	  
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOB8复用为定时器4
	
  TIM_DeInit(TIM1);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Disable);
	TIM_ARRPreloadConfig(TIM1, DISABLE);
	TIM_Cmd(TIM1, DISABLE);
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;		/* TIM1 和 TIM8 必须设置 */	

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = (arr+1)/2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);						  
}  
void TIM3_Int_Init(void)
{
	 //使能定时器3
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//	
//	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOF9复用为定时器14
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;           //GPIOF9
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
//	GPIO_Init(GPIOB,&GPIO_InitStructure); 
//	
//	
//	
//	
//  TIM_TimeBaseInitStructure.TIM_Period =49; 	//自动重装载值
//	TIM_TimeBaseInitStructure.TIM_Prescaler=0;  //定时器分频
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
//	
//	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);
//  TIM_SelectInputTrigger(TIM3, TIM_TS_ITR1);
//	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
//	
////	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断

//  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
//	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1

//	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
// 
//  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
//  TIM_SetCompare4(TIM3,20);
//	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
}


//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		Flag++;
		if(S19_Flag==1)
		{
			if((Flag>=2)&&(Flag<=9))
			{
				S19=1;
			}
			else 
				S19=0;
		}
		else
			S19=0;
		if(Flag==11)
		{
			Flag=1;
		}	
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

