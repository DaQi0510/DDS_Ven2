#include "GPIO_Init.h"
#include "lcd.h"
#include "AT24C02.h"
#include "delay.h"
#include "TFT_LCD.h"
extern volatile u8 ADNum;
extern volatile u16 Pulse;
extern volatile u16 Sine_Fre1;
extern volatile u16 Sine_Amp1;
extern volatile u16 Sine_Fre2;
extern volatile u16 Sine_Amp2;
void Gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;	

	//Һ����ʾ����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIO	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO	
	
	//���ز���
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
	
	//ģ��ת������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIO	
	
	//�̵������Ʋ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIO	
	GPIO_SetBits(GPIOG,GPIO_Pin_10);
	//�̵����źŲ���
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIO
	
	//���ؿ����������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO	
	GPIO_ResetBits(GPIOD,GPIO_Pin_10| GPIO_Pin_11 | GPIO_Pin_12);
	
	//ģ��ת����ť������Ƶ�ʵ�����ť�����Ҳ�Ƶ�ʵ�����ť�����Ҳ���ֵ������ť
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 ;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;//RST��ӦIO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//RST��ӦIO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//RST��ӦIO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//RST��ӦIO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��GPIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource11);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);
	
		/* ����EXTI_Line1 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������½����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	
	
	/* ����EXTI_Line2 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������½��ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	
	
	/* ����EXTI_Line3 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	
	
	/* ����EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	
	
	/* ����EXTI_Line8 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	
	
	/* ����EXTI_Line11 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line11;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	
	
	
}

//�ⲿ�жϴ�����,���ؽӿ�
void EXTI1_IRQHandler(void)
{
	u8 i=0;
	Delays();
	if(PFin(1)==1)
	{
		if(EXTI_GetITStatus(EXTI_Line1) != RESET)
		{
			Delays();
			if(B4==1)   
			{
				if(Sine_Amp1>=500)
					Sine_Amp1=500;
				else
					Sine_Amp1+=10;
			}
			else 
			{
				if(Sine_Amp1<=0)
					Sine_Amp1=0;
				else
					Sine_Amp1-=10;
			}
			AT24C02_WriteOneByte(0x03,Sine_Amp1/256);
			AT24C02_WriteOneByte(0x04,Sine_Amp1%256);
			LCD_ShowSine1(Sine_Amp1,Sine_Fre1);
			while(PFin(1)==1)
			{
				Delays();
				i++;
				if(i>3)
					break;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
//�ⲿ�жϴ�����,ģ��ת��
void EXTI2_IRQHandler(void)
{
	u8 i=0;
	Delays();
	if(PFin(2)==1)
	{
		if(EXTI_GetITStatus(EXTI_Line2) != RESET)
		{
			Delays();	
			if(B5==1)   
			{
				if(Pulse>=200)
					Pulse=200;
				else
					Pulse+=10;
			}
			else 
			{
				if(Pulse<=40)
					Pulse=40;
				else
					Pulse-=10;
			}
			AT24C02_WriteOneByte(0x01,Pulse/256);
			AT24C02_WriteOneByte(0x02,Pulse%256);
			LCD_ShowPulse(Pulse);
			TFT_LCD_ShowPulse(Pulse);
			while(PFin(2)==1)
			{
				Delays();
				i++;
				if(i>3)
					break;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}
//�ⲿ�жϴ�����,����Ƶ��
void EXTI3_IRQHandler(void)
{
	u8 i=0;
	Delays();
	if(PFin(3)==1)
	{
		Delays();	
		if(B6==1)
		{
			if(ADNum>=255)
				ADNum=255;
			else
				ADNum++;
		}
		else
		{
			if(ADNum<=0)
				ADNum =0;
			else
				ADNum--;
		}
		AT24C02_WriteOneByte(0x00,ADNum);
    LCD_ShowADNum(ADNum);
		TFT_LCD_ShowADNum(ADNum);
		while(PFin(3)==1)
		{
			Delays();
			i++;
			if(i>3)
				break;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
	Delays();

}
//�ⲿ�жϴ�����,���Ҳ�Ƶ��
void EXTI4_IRQHandler(void)
{
	u8 i=0;
	Delays();
	if(PGin(4)==1)
	{
		if(EXTI_GetITStatus(EXTI_Line4) != RESET)
		{
			Delays();
			if(B2==1)
			{
				if(Sine_Fre2>=300)
					Sine_Fre2=300;
				else
					Sine_Fre2+=10;
			}
			else
			{
				if(Sine_Fre2<=50)
					Sine_Fre2=50;
				else
					Sine_Fre2-=10;
			}
			AT24C02_WriteOneByte(0x09,Sine_Fre2/256);
			AT24C02_WriteOneByte(0x0A,Sine_Fre2%256);
			LCD_ShowSine2(Sine_Amp2,Sine_Fre2);
			while(PGin(4)==1)
			{
				Delays();
				i++;
				if(i>3)
					break;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}

//�ⲿ�жϴ�����,���Ҳ���ֵ
void EXTI9_5_IRQHandler(void)
{
	u8 i=0;
	Delays();
	if(PCin(8)==1)
	{
		if(EXTI_GetITStatus(EXTI_Line8) != RESET)
		{
			Delays();
			if(B3==1)
			{
				if(Sine_Amp2>=500)
					Sine_Amp2=500;
				else
					Sine_Amp2+=10;
			}
			else
			{
				if(Sine_Amp2<=0)
					Sine_Amp2=0;
				else
					Sine_Amp2-=10;
			}
			AT24C02_WriteOneByte(0x07,Sine_Amp2/256);
			AT24C02_WriteOneByte(0x08,Sine_Amp2%256);
			LCD_ShowSine2(Sine_Amp2,Sine_Fre2);
			while(PCin(8)==1)
			{
				Delays();
				i++;
				if(i>3)
					break;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line8);
}

void EXTI15_10_IRQHandler(void)
{
	u8 i=0;
	Delays();
	if(PAin(11)==1)
	{
		if(EXTI_GetITStatus(EXTI_Line11) != RESET)
		{
			Delays();
			if(B1==1)
			{
				if(Sine_Fre1>=300)
					Sine_Fre1=300;
				else
					Sine_Fre1+=10;
			}
			else
			{
				if(Sine_Fre1<=50)
					Sine_Fre1=50;
				else
					Sine_Fre1-=10;
			}
			AT24C02_WriteOneByte(0x05,Sine_Fre1/256);
			AT24C02_WriteOneByte(0x06,Sine_Fre1%256);
			LCD_ShowSine1(Sine_Amp1,Sine_Fre1);
			while(PAin(11)==1)
			{
				Delays();
				i++;
				if(i>3)
					break;
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line11);
}
void Delays(void)    //��ʱ����
{
	u8 i,j;
	for(i=0;i<80;i++)
		for(j=0;j<20;j++);
}
void SetAD(u8 SetNum)  //���ģ��ת��
{
	if(SetNum&1<<0)
		AD1=1;     //��Ӧ����ߵ�ƽ
	else
		AD1=0;
	if(SetNum&1<<1)
		AD2=1;     //��Ӧ����ߵ�ƽ
	else
		AD2=0;
	if(SetNum&1<<2)
		AD3=1;     //��Ӧ����ߵ�ƽ
	else
		AD3=0;
	if(SetNum&1<<3)
		AD4=1;     //��Ӧ����ߵ�ƽ
	else
		AD4=0;
	if(SetNum&1<<4)
		AD5=1;     //��Ӧ����ߵ�ƽ
	else
		AD5=0;
	if(SetNum&1<<5)
		AD6=1;     //��Ӧ����ߵ�ƽ
	else
		AD6=0;
	if(SetNum&1<<6)
		AD7=1;     //��Ӧ����ߵ�ƽ
	else
		AD7=0;
	if(SetNum&1<<7)
		AD8=1;     //��Ӧ����ߵ�ƽ
	else
		AD8=0;
}
