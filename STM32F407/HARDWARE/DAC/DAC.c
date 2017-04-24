#include "DAC.h"
#include "math.h"

#define DAC_DHR12R1_ADDRESS     0x40007408
#define DAC_DHR12R2_ADDRESS     0x40007414

extern volatile u16 tableSize1;
volatile u16 sinTable1[1024];
extern volatile u16 tableSize2;
volatile u16 sinTable2[1024];
extern volatile u8 K3_Flagt;
void sin_Generation1(u16 Fre,u16 Vol)
{
	u32 Voltage;
	u16 n;
	if(Vol>480)
		Vol =480;
	Voltage= Vol*4080/500;
		if(Voltage>4000)
		Voltage=4000;
	if(Fre>150)
		tableSize1=512;
	else
		tableSize1=1024;
//	for(n=0;n<tableSize;n++)
//	{
//		sinTable[n] = (sin(2*PI*n/tableSize)+1)*Voltage+50;	
//	}	

	if(Voltage>40)
	{
		for(n=0;n<tableSize1/2;n++)
		{
			sinTable1[n] =n*2*Voltage/tableSize1+65;	
		}
		for(n=tableSize1/2;n<tableSize1;n++)
		{
			sinTable1[n] =Voltage-(2*n+2-tableSize1)*Voltage/tableSize1+65;	
		}
	}
	if((Voltage<=40)&&(Voltage>=10))
	{
		for(n=0;n<tableSize1/2;n++)
		{
			sinTable1[n] =n*2*Voltage/tableSize1+90;	
		}
		for(n=tableSize1/2;n<tableSize1;n++)
		{
			sinTable1[n] =Voltage-(2*n+2-tableSize1)*Voltage/tableSize1+90;	
		}
	}
	if(Voltage==0)
	{
		for(n=0;n<tableSize1/2;n++)
		{
			sinTable1[n] =n*2*Voltage/tableSize1+105;	
		}
		for(n=tableSize1/2;n<tableSize1;n++)
		{
			sinTable1[n] =Voltage-(2*n+2-tableSize1)*Voltage/tableSize1+105;	
		}
	}
	
}
void sin_Generation2(u16 Fre,u16 Vol)
{
	u32 Voltage;
	u16 n;
	if(Vol>480)
		Vol =480;
	Voltage= Vol*4080/500;
	if(Voltage>4000)
		Voltage=4000;
	if(Fre>150)
		tableSize2=512;
	else
		tableSize2=1024;
//	for(n=0;n<tableSize;n++)
//	{
//		sinTable[n] = (sin(2*PI*n/tableSize)+1)*Voltage+50;	
//	}	

	if(Voltage>40)
	{
		for(n=0;n<tableSize2/2;n++)
		{
			sinTable2[n] =n*2*Voltage/tableSize2+65;	
		}
		for(n=tableSize2/2;n<tableSize2;n++)
		{
			sinTable2[n] =Voltage-(2*n+2-tableSize2)*Voltage/tableSize2+65;	
		}
	}
	if((Voltage<=40)&&(Voltage>=10))
	{
		for(n=0;n<tableSize2/2;n++)
		{
			sinTable2[n] =n*2*Voltage/tableSize2+90;	
		}
		for(n=tableSize2/2;n<tableSize2;n++)
		{
			sinTable2[n] =Voltage-(2*n+2-tableSize2)*Voltage/tableSize2+90;	
		}
	}
	if(Voltage==0)
	{
		for(n=0;n<tableSize2/2;n++)
		{
			sinTable2[n] =n*2*Voltage/tableSize2+105;	
		}
		for(n=tableSize2/2;n<tableSize2;n++)
		{
			sinTable2[n] =Voltage-(2*n+2-tableSize2)*Voltage/tableSize2+105;	
		}
	}
	
}
void TIM6_Configuration(u16 Fre)
{

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
		TIM_PrescalerConfig(TIM6,1, TIM_PSCReloadMode_Update);
		TIM_SetAutoreload(TIM6, Fre);
		TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
		TIM_Cmd(TIM6, ENABLE);
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

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sinTable1;
	DMA_InitStructure.DMA_BufferSize = tableSize1;
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
	DMA_InitStructure.DMA_BufferSize = tableSize2;
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
	TIM6_Configuration(FreNum);
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


