#ifndef __TFT_LCD_H
#define __TFT_LCD_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD端口定义---------------- 
#define	TFT_LCD_LED PCout(12)  		//LCD背光    		 PB15 
u16 TFT_LCD_ShowTop1(u16 x ,u16 y);
u16 TFT_LCD_ShowTop2(u16 x ,u16 y);
void TFT_LCD_ShowInformation(void);

typedef struct  
{										    
	u16 width;			//LCD 宽度
	u16 height;			//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	wramcmd;		//开始写gram指令
	u16  setxcmd;		//设置x坐标指令
	u16  setycmd;		//设置y坐标指令 
}_lcd_dev; 	  

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;
//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A6作为数据命令区分线 
//注意设置时STM32内部会右移一位对其! 111 1110=0X7E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  7  //默认的扫描方向

//画笔颜色
#define WHITE         	  0xFFFF
#define BLACK         	  0x0000	  
#define BLUE         	    0x001F  
#define BRED              0XF81F
#define GRED 			        0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

void TFT_LCD_Writ_Bus(char dat);   //串行数据写入
void LCD_WR_REG_DATA(int reg,int da);
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void TFT_LCD_Init(void) ;
void TFT_LCD_Clear(u16 Color);
void TFT_LCD_ShowChar(u16 x,u16 y,u16 CharNum);
void TFT_LCD_ShowPower(void);
void TFT_LCD_ShowPulse(void);
void TFT_LCD_ShowRed(void);
void TFT_LCD_ShowLaser(void);
void TFT_LCD_ShowMode(void);
void TFT_LCD_ShowWidth(void);
void TFT_LCD_ShowLogo(void);
void ShowLine(void);
void TFT_LCD_ShowADNum(u8 Value);
void TFT_LCD_ShowPulseValue(u16 Value);
void TFT_LCD_ShowRedValue(u8 Value);
void TFT_LCD_ShowLaserValue(u8 Value);
void TFT_LCD_ShowModeValue(u8 Value);
void TFT_LCD_ShowWidthValue(u16 Value);
void TFT_LCD_ShowCharL(u16 x,u16 y,u16 CharNum);
void TFT_LCD_ShowCharS(u16 x,u16 y,u16 CharNum);
void TFT_LCD_ShowCharSS(u16 x,u16 y,u16 CharNum);
void TFT_LCD_ShowTop(void);
void TFT_LCD_SetCursor(u16 Xpos, u16 Ypos);

u16 TFT_LCD_ShowTop1(u16 x ,u16 y);
u16 TFT_LCD_ShowTop2(u16 x ,u16 y);
void TFT_LCD_Show_Inf1(u16 x,u16 y,u8 *InfNum,u8 Num);
void TFT_LCD_Show_Inf2(u16 x,u16 y,u8 *InfNum,u8 Num);
void TFT_LCD_Show_Inf3(u16 x,u16 y,u8 *InfNum,u8 Num);


//LCD分辨率设置
#define SSD_HOR_RESOLUTION		800		//LCD水平分辨率
#define SSD_VER_RESOLUTION		480		//LCD垂直分辨率
//LCD驱动参数设置
#define SSD_HOR_PULSE_WIDTH		1		//水平脉宽
#define SSD_HOR_BACK_PORCH		46		//水平前廊
#define SSD_HOR_FRONT_PORCH		210		//水平后廊

#define SSD_VER_PULSE_WIDTH		1		//垂直脉宽
#define SSD_VER_BACK_PORCH		23		//垂直前廊
#define SSD_VER_FRONT_PORCH		22		//垂直前廊
//如下几个参数，自动计算
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif
