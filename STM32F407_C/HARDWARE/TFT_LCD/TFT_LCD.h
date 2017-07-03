#ifndef __TFT_LCD_H
#define __TFT_LCD_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	TFT_LCD_LED PCout(12)  		//LCD����    		 PB15 
u16 TFT_LCD_ShowTop1(u16 x ,u16 y);
u16 TFT_LCD_ShowTop2(u16 x ,u16 y);
void TFT_LCD_ShowInformation(void);

typedef struct  
{										    
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	wramcmd;		//��ʼдgramָ��
	u16  setxcmd;		//����x����ָ��
	u16  setycmd;		//����y����ָ�� 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����

typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A6��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111 1110=0X7E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  7  //Ĭ�ϵ�ɨ�跽��

//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ

void TFT_LCD_Writ_Bus(char dat);   //��������д��
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


//LCD�ֱ�������
#define SSD_HOR_RESOLUTION		800		//LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION		480		//LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH		1		//ˮƽ����
#define SSD_HOR_BACK_PORCH		46		//ˮƽǰ��
#define SSD_HOR_FRONT_PORCH		210		//ˮƽ����

#define SSD_VER_PULSE_WIDTH		1		//��ֱ����
#define SSD_VER_BACK_PORCH		23		//��ֱǰ��
#define SSD_VER_FRONT_PORCH		22		//��ֱǰ��
//���¼����������Զ�����
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)

#endif
