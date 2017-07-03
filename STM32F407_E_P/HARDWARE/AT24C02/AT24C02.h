#ifndef __AT24C02_H
#define __AT24C02_H

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "sys.h"

//IO��������
#define AT24C02_SDA_IN()  {GPIOF->MODER&=~(3<<(5*2));GPIOF->MODER|=0<<5*2;}	//PD13����ģʽ
#define AT24C02_SDA_OUT() {GPIOF->MODER&=~(3<<(5*2));GPIOF->MODER|=1<<5*2;} //PD13���ģʽ
//IO��������	 
#define AT24C02_SCL    PFout(4)      //SCL
#define AT24C02_SDA    PFout(5)      //SDA	 
#define AT24C02_READ_SDA   PFin(5)   //��ȡSDA 

void SetDeviceInformation(u8 *Information,u8 Length);
void GetDeviceInformation(void);

void AT24C02_GPIO_Init(void);
void AT24C02_Init(void);
u8 AT24C02_ReadOneByte(u8 ReadAddr);
void AT24C02_WriteOneByte(u8 WriteAddr,u8 DataToWrite);
void AT24C02_Read(u8 ReadAddr,u8 *pBuffer,u8 NumToRead);
void AT24C02_Write(u8 WriteAddr,u8 *pBuffer,u8 NumToWrite);
void AT24C02_IIC_Start(void);
void AT24C02_IIC_Stop(void);
u8 AT24C02_IIC_Wait_Ack(void);
void AT24C02_IIC_Ack(void);
void AT24C02_IIC_NAck(void);
void AT24C02_Send_Byte(u8 TxData);
u8 AT24C02_Read_Byte(u8 Ack);

#endif
