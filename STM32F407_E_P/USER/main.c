#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "delay.h" 
#include "GPIO_Init.h"
#include "AT24C02.h"
#include "lcd.h"
#include "DAC.h"
#include "TFT_LCD.h"
#include "bsp_tim_pwm.h"
volatile u8 ADNum;
volatile u16 Pulse;
volatile u16 Sine_Fre1;
volatile u16 Sine_Amp1;
volatile u16 Sine_Fre2;
volatile u16 Sine_Amp2;
volatile u8 K1_Flag;
volatile u8 K2_Flag;
volatile u8 K3_Flag;
volatile u8 Relay_Flag;
volatile u8 S19_Flag;
volatile u8 ADNumt;
volatile u16 Pulset;
volatile u16 Sine_Fre1t;
volatile u16 Sine_Amp1t;
volatile u16 Sine_Fre2t;
volatile u16 Sine_Amp2t;
volatile u16 Sine_FreNum1;
volatile u16 Sine_FreNum2;
volatile u8 K1_Flagt;
volatile u8 K2_Flagt;
volatile u8 K3_Flagt;
volatile u8 Relay_Flagt;
//volatile  u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色

volatile u16 tableSize1;
volatile u16 tableSize2;
volatile u16 PulseNum;
volatile u16 VoltageValue;   //0-5000
volatile u16 ADV;  
void StartInit(void);
void AD_Scan(void);
void Pulse_Scan(void);
void CheckFlag(void);
volatile u16 FreqNuma;
void Sine1_Scan(void);
void Sine2_Scan(void);
void K1_Scan(void);
void K2_Scan(void);
void K3_Scan(void);
void Realys_Scan(void);
int main(void)
{
  u8 i;
//	POINT_COLOR =BLACK;
//  BACK_COLOR=BROWN;
	delay_init(168);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	AT24C02_Init();
	Gpio_Init();
	LCD_Init();
	TFT_LCD_Init();
//	TFT_LCD_Clear(YELLOW);
	TFT_LCD_Clear(WHITE);
	TFT_LCD_ShowLogo();
	TFT_LCD_ShowLASER(152,160);
	TFT_LCD_ShowPOWER(255,159);
	TFT_LCD_ShowPULSE(150,215);
 
  TFT_LCD_ShowLASER(152,325);
	TFT_LCD_ShowMODE(152,380);
	TFT_LCD_ShowRED(150,270);
//	TFT_LCD_ShowON(300,300);
	TFT_LCD_ShowWIDTH(152,435);
//	
//	TFT_LCD_ShowOFF(300,200);
	ShowLine();
//	TFT_LCD_ShowPower();
//	while(1)
//	{
//		
//     TFT_LCD_ShowPOWER(220,153);
//		delay_ms(1000);
//	}
//	TFT_LCD_ShowPower();
//	TFT_LCD_Clear(WHITE);
//	TFT_LCD_ShowLogo();
//	delay_ms(10);
//  ShowLine();
//	delay_ms(10);
//	TFT_LCD_ShowPower();
//	while(1)
//	{
//		TFT_LCD_ShowLogo();
//		delay_ms (1000);
//	}
//	TFT_LCD_ShowPulse();
//	TFT_LCD_ShowRed();
//  TFT_LCD_ShowLaser();
//  TFT_LCD_ShowMode();
//  TFT_LCD_ShowWidth();

	StartInit();
	i=5;
	while(1)
	{
		AD_Scan();
		Pulse_Scan();
		Sine1_Scan();
		Sine2_Scan();
		K1_Scan();
		K2_Scan();
		K3_Scan();
		Realys_Scan();
	}

}

void StartInit(void)
{
	u16 Fres;
	LCD_Display();
//	//AD设置部分
	ADNum = AT24C02_ReadOneByte(0x00);
	LCD_ShowADNum(ADNum);
  TFT_LCD_ShowADNum(ADNum);
	ADNumt =ADNum ;
	SetAD(ADNum);

	//方波频率设置部分
	Pulse=AT24C02_ReadOneByte(0x01);
	Pulse<<=8;
	Pulse+=AT24C02_ReadOneByte(0x02);
	Pulset = Pulse;
	PulseNum=168000/Pulset-1;
	bsp_SetTIMOutPWM(GPIOA, GPIO_Pin_9, TIM1, 2, PulseNum, 5000);  
	TFT_LCD_ShowPulseValue(Pulse);
	LCD_ShowPulse(Pulse);

	//三角形波1
	Sine_Amp1 =AT24C02_ReadOneByte(0x03);
	Sine_Amp1<<=8;
	Sine_Amp1+=AT24C02_ReadOneByte(0x04);
	Sine_Fre1 =AT24C02_ReadOneByte(0x05);
	Sine_Fre1<<=8;
	Sine_Fre1+=AT24C02_ReadOneByte(0x06);
	LCD_ShowSine1(Sine_Amp1,Sine_Fre1); 
	Sine_Amp1t =Sine_Amp1;
	Sine_Fre1t=Sine_Fre1;
	sin_Generation1(Sine_Fre1t,Sine_Amp1);	
	Sine_FreNum1=42000/Sine_Fre1t-1;
	TIM2_Configuration(Sine_FreNum1);
	DAC_DMA_Configuration1();
	TFT_LCD_ShowWidthValue(Sine_Amp1);
	//三角形波1
	Sine_Amp2 =AT24C02_ReadOneByte(0x07);
	Sine_Amp2<<=8;
	Sine_Amp2+=AT24C02_ReadOneByte(0x08);
	Sine_Fre2 =AT24C02_ReadOneByte(0x09);
	Sine_Fre2<<=8;
	Sine_Fre2+=AT24C02_ReadOneByte(0x0A);
	LCD_ShowSine2(Sine_Amp2,Sine_Fre2);
	Sine_Amp2t =Sine_Amp2;
	Sine_Fre2t=Sine_Fre2;
	sin_Generation2(Sine_Fre2t,Sine_Amp2);	
	Sine_FreNum2 =42000/Sine_Fre2t-1;
	TIM7_Configuration(Sine_FreNum2);
	DAC_DMA_Configuration2(); 
	//开关1控制部分
	if(K1==1)   //开关闭合
	{
		K1_Flag=1;
	}
	else
	{
		K1_Flag=0;
	}
	K1_Flagt=K1_Flag;
	if(K1_Flagt==1)
	{
		S18=1;
		delay_ms(100);
		TIM_SetCompare4(TIM3,450);
	}
	else
	{
		
		S18=0;
		TIM_SetCompare4(TIM3,0);
	}
	LCD_ShowLaser(K1_Flagt);
	TFT_LCD_ShowLaserValue(K1_Flagt);
	//开关2控制部分
	if(K2==1)   //开关闭合
	{
		K2_Flag=1;
	}
	else
	{
		K2_Flag=0;
	}
	K2_Flagt=K2_Flag;
	if(K2_Flagt==1)
	{
		S22=1;
	}
	else
	{
		S22=0;
	}
	LCD_ShowRed(K2_Flagt);
	TFT_LCD_ShowRedValue(K2_Flagt);
	//开关3控制部分
	if(K3==1)   //开关闭合
	{
		K3_Flag=1;
	}
	else
	{
		K3_Flag=0;
	}
	K3_Flagt=K3_Flag;
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
	TFT_LCD_ShowModeValue(K3_Flagt);
	LCD_ShowMode(K3_Flagt);
	//继电器控制部分
	if(Relays==0)   //继电器应闭合
		Relay_Flag =1;
	else 
		Relay_Flag =0;
	Relay_Flagt =Relay_Flag ;
	if(Relay_Flagt==1)
		Relay_On ;
	else 
		Relay_Off ;
	LCD_ShowWarning(Relay_Flagt);
//	TFT_LCD_ShowWarning(Relay_Flagt);
}
void AD_Scan(void)
{
	if(ADNumt!=ADNum)
	{
		
		ADNumt =ADNum ;
		SetAD(ADNum);
		TFT_LCD_ShowADNum(ADNum);
	}
}
void Pulse_Scan(void)
{
	if(Pulset!=Pulse)
	{
		delay_ms(10);
		Pulset =Pulse;
		PulseNum=168000/Pulset-1;
		bsp_SetTIMOutPWM(GPIOA, GPIO_Pin_9, TIM1, 2, PulseNum, 5000);  
	}
	
}
void Sine1_Scan(void)
{
  u16 Fres;
	if((Sine_Amp1t!=Sine_Amp1)||(Sine_Fre1t!=Sine_Fre1))
	{
		delay_ms(10);
		Sine_Amp1t =Sine_Amp1;
		Sine_Fre1t=Sine_Fre1;
		sin_Generation1(Sine_Fre1t,Sine_Amp1);	
		Sine_FreNum1 =42000/Sine_Fre1t-1;
		TIM2_Configuration(Sine_FreNum1);
		DAC_DMA_Configuration1(); 
		if(K1_Flagt==1)
			TIM_SetCompare4(TIM3,450);
		else
			TIM_SetCompare4(TIM3,0);
		TFT_LCD_ShowWidthValue(Sine_Amp1);
	}
}
void Sine2_Scan(void)
{
	if((Sine_Amp2t!=Sine_Amp2)||(Sine_Fre2t!=Sine_Fre2))
	{
		delay_ms(10);
		Sine_Amp2t =Sine_Amp2;
		Sine_Fre2t=Sine_Fre2;
		sin_Generation2(Sine_Fre2t,Sine_Amp2);	
		Sine_FreNum2 =42000/Sine_Fre2t-1;
		TIM7_Configuration(Sine_FreNum2);
		DAC_DMA_Configuration2(); 
	}
}
void K1_Scan(void)
{
	if(K1==1)   //开关闭合
	{
		K1_Flag=1;
	}
	else
	{
		K1_Flag=0;
	}delay_ms(5);
	if(K1_Flagt!=K1_Flag)
	{
		K1_Flagt=K1_Flag;
		if(K1_Flagt==1)
		{
			S18=1;
			delay_ms(100);
			TIM_SetCompare4(TIM3,450);
		}
		else
		{
			S18=0;
			TIM_SetCompare4(TIM3,0);
		}
		TFT_LCD_ShowLaserValue(K1_Flagt);
		LCD_ShowLaser(K1_Flagt);
	}
}
void K2_Scan(void)
{
	if(K2==1)   //开关闭合
	{
		K2_Flag=1;
	}
	else
	{
		K2_Flag=0;
	}
	delay_ms(5);
	if(K2_Flagt!=K2_Flag)
	{
		K2_Flagt=K2_Flag;
		if(K2_Flagt==1)
		{
			S22=1;
		}
		else
		{
			S22=0;
		}
		TFT_LCD_ShowRedValue(K2_Flagt);
		LCD_ShowRed(K2_Flagt);
	}
}
void K3_Scan(void)
{
	if(K3==1)   //开关闭合
	{
		K3_Flag=1;
	}
	else
	{
		K3_Flag=0;
	}
	if(K3_Flagt!=K3_Flag)
	{
		K3_Flagt=K3_Flag;
		if(K3_Flagt==1)
		{
			DMA_Cmd(DMA1_Stream6, ENABLE);
			DAC_Cmd(DAC_Channel_2, ENABLE);
			DAC_DMACmd(DAC_Channel_2, ENABLE);
		}
		if(K3_Flagt==0)
		{
			DMA_Cmd(DMA1_Stream6, DISABLE);
			DAC_Cmd(DAC_Channel_2, DISABLE);
			DAC_DMACmd(DAC_Channel_2, DISABLE); 
		}
		LCD_ShowMode(K3_Flagt);
		TFT_LCD_ShowModeValue(K3_Flagt);
	}
}
void Realys_Scan(void)
{
	if(Relays==0)   //继电器应闭合
	{
		Relay_Flag =1;
	}
	else 
		Relay_Flag =0;
	delay_ms(5);
	if(Relay_Flagt!=Relay_Flag)
	{
		Relay_Flagt =Relay_Flag ;
		if(Relay_Flagt==1)
			Relay_On ;
		else 
			Relay_Off ;
		LCD_ShowWarning(Relay_Flagt);
	}
}

