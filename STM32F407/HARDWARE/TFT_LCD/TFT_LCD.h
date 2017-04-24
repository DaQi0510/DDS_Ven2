#ifndef __TFT_LCD_H
#define __TFT_LCD_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"



#define TFT_LCD_W 240
#define TFT_LCD_H 320

#define TFT_LCD_BLK_Clr   PAout(0)=0 
#define TFT_LCD_BLK_Set   PAout(0)=1   
#define TFT_LCD_DC_Clr    PAout(1)=0 
#define TFT_LCD_DC_Set    PAout(1)=1   
#define TFT_LCD_RES_Clr   PAout(2)=0 
#define TFT_LCD_RES_Set   PAout(2)=1  
#define TFT_LCD_CLK_Clr   PBout(13)=0 
#define TFT_LCD_CLK_Set   PBout(13)=1   
#define TFT_LCD_MOSI_Clr  PCout(3)=0 
#define TFT_LCD_MOSI_Set  PCout(3)=1  

void TFT_LCD_Writ_Bus(char dat);   //��������д��
void TFT_LCD_WR_DATA8(char da); //��������8λ
void TFT_LCD_WR_DATA(int da);   //��������16λ
void TFT_LCD_WR_REG(char da);
void LCD_WR_REG_DATA(int reg,int da);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void TFT_LCD_Init(void) ;
void TFT_LCD_Clear(u16 Color);
void TFT_LCD_ShowChar(u16 x,u16 y,u8 Num);
void TFT_LCD_ShowString(u16 x,u16 y,const u8 *p);
void TFT_LCD_Display(void);
void TFT_LCD_ShowChars(u16 x,u16 y,u8 Num);
void TFT_LCD_ShowTop(void);
void TFT_LCD_ShowADNum(u8 Value);
void TFT_LCD_ShowPulse(u16 Value);
void TFT_LCD_ShowRed(u8 Value);
void TFT_LCD_ShowLaser(u8 Value);
void TFT_LCD_ShowMode(u8 Value);
void TFT_LCD_ShowWarning(u8 Value);

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	   0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //��ɫ
#define BRRED 			     0XFC07 //�غ�ɫ
#define GRAY  			     0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			     0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#endif
