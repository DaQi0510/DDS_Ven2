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

void TFT_LCD_Writ_Bus(char dat);   //串行数据写入
void TFT_LCD_WR_DATA8(char da); //发送数据8位
void TFT_LCD_WR_DATA(int da);   //发送数据16位
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

//画笔颜色
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
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

#endif
