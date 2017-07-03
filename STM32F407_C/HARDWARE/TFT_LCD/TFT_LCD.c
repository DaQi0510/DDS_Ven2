#include "TFT_LCD.h"
#include "delay.h"
#include "stm32f4xx_fsmc.h"
#include "Logo.h"
_lcd_dev lcddev;
u16 POINT_COLOR=0x0000;	//画笔颜色
//u16 BACK_COLOR=0xFEE9;  //背景色 
u16 BACK_COLOR=0xffff;  //背景色 
//写寄存器函数
//regval:寄存器值
void TFT_LCD_WR_REG(vu16 regval)
{
	regval=regval;		   //使用-O2优化的时候,必须插入的延时
//	for(i=0;i<20;i++)
	LCD->LCD_REG=regval;//写入要写的寄存器序号	 
}
//写LCD数据
//data:要写入的值
void TFT_LCD_WR_DATA(vu16 data)
{	 

  data=data;
	LCD->LCD_RAM=data;		 
}
//读LCD数据
//返回值:读到的值
u16 TFT_LCD_RD_DATA(void)
{
	vu16 ram;			//防止被优化
	ram=LCD->LCD_RAM;	
	return ram;	 
}					   
//写寄存器
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
void TFT_LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;		  //写入要写的寄存器序号	 
	LCD->LCD_RAM = LCD_RegValue;//写入数据	    		 
}	   
//读寄存器
//LCD_Reg:寄存器地址
//返回值:读到的数据
u16 TFT_LCD_ReadReg(u16 LCD_Reg)
{	
  u8 i;	
	TFT_LCD_WR_REG(LCD_Reg);		//写入要读的寄存器序号	
  for(i=0;i<250;i++) ; 
	return TFT_LCD_RD_DATA();		//返回读到的值
}   
//开始写GRAM
void TFT_LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=lcddev.wramcmd;	  
}	 
//LCD写GRAM
//RGB_Code:颜色值
void TFT_LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;//写十六位GRAM
}


//TFT_LCD开启显示
void TFT_LCD_DisplayOn(void)
{					   
	TFT_LCD_WR_REG(0X2900);	//开启显示
}	 
//TFT_LCD关闭显示
void TFT_LCD_DisplayOff(void)
{	   
	TFT_LCD_WR_REG(0X2800);	//关闭显示
}   
//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void TFT_LCD_SetCursor(u16 Xpos, u16 Ypos)
{	 
	TFT_LCD_WR_REG(lcddev.setxcmd);TFT_LCD_WR_DATA(Xpos>>8); 		
	TFT_LCD_WR_REG(lcddev.setxcmd+1);TFT_LCD_WR_DATA(Xpos&0XFF);			 
	TFT_LCD_WR_REG(lcddev.setycmd);TFT_LCD_WR_DATA(Ypos>>8);  		
	TFT_LCD_WR_REG(lcddev.setycmd+1);TFT_LCD_WR_DATA(Ypos&0XFF);			
}
u16 TFT_LCD_Read_X(void)
{
	u16 x;
	x=TFT_LCD_ReadReg(lcddev.setxcmd);
	x<<=8;
	x+=TFT_LCD_ReadReg(lcddev.setxcmd+1);
	return x;
}
//u16 TFT_LCD_Read_Y(void)
//{
//	u16 x;
//	x=TFT_LCD_ReadReg(lcddev.setxcmd);
//	x<<=8;
//	x+=TFT_LCD_ReadReg(lcddev.setxcmd+1);
//	return x;
//}
//设置LCD的自动扫描方向
//注意:其他函数可能会受到此函数设置的影响(尤其是9341/6804这两个奇葩),
//所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
//dir:0~7,代表8个方向(具体定义见lcd.h)
//9320/9325/9328/4531/4535/1505/b505/5408/9341/5310/5510/1963等IC已经实际测试	   	   
void TFT_LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;  
	if(lcddev.dir==1)//横屏时，对6804和1963不改变扫描方向！竖屏时1963改变方向
	{			   
		switch(dir)//方向转换
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	} 
	switch(dir)
	{
		case L2R_U2D://从左到右,从上到下
			regval|=(0<<7)|(0<<6)|(0<<5); 
			break;
		case L2R_D2U://从左到右,从下到上
			regval|=(1<<7)|(0<<6)|(0<<5); 
			break;
		case R2L_U2D://从右到左,从上到下
			regval|=(0<<7)|(1<<6)|(0<<5); 
			break;
		case R2L_D2U://从右到左,从下到上
			regval|=(1<<7)|(1<<6)|(0<<5); 
			break;	 
		case U2D_L2R://从上到下,从左到右
			regval|=(0<<7)|(0<<6)|(1<<5); 
			break;
		case U2D_R2L://从上到下,从右到左
			regval|=(0<<7)|(1<<6)|(1<<5); 
			break;
		case D2U_L2R://从下到上,从左到右
			regval|=(1<<7)|(0<<6)|(1<<5); 
			break;
		case D2U_R2L://从下到上,从右到左
			regval|=(1<<7)|(1<<6)|(1<<5); 
			break;	 
	}
	dirreg=0X3600;
	regval|=(0<<7)|(0<<6)|(1<<5); 
	TFT_LCD_WriteReg(dirreg,regval);
		
	TFT_LCD_WR_REG(lcddev.setxcmd);TFT_LCD_WR_DATA(0); 
	TFT_LCD_WR_REG(lcddev.setxcmd+1);TFT_LCD_WR_DATA(0); 
	TFT_LCD_WR_REG(lcddev.setxcmd+2);TFT_LCD_WR_DATA((lcddev.width-1)>>8); 
	TFT_LCD_WR_REG(lcddev.setxcmd+3);TFT_LCD_WR_DATA((lcddev.width-1)&0XFF); 
	TFT_LCD_WR_REG(lcddev.setycmd);TFT_LCD_WR_DATA(0); 
	TFT_LCD_WR_REG(lcddev.setycmd+1);TFT_LCD_WR_DATA(0); 
	TFT_LCD_WR_REG(lcddev.setycmd+2);TFT_LCD_WR_DATA((lcddev.height-1)>>8); 
	TFT_LCD_WR_REG(lcddev.setycmd+3);TFT_LCD_WR_DATA((lcddev.height-1)&0XFF);
		
}     
//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void TFT_LCD_DrawPoint(u16 x,u16 y)
{
	TFT_LCD_SetCursor(x,y);		//设置光标位置 
	TFT_LCD_WriteRAM_Prepare();	//开始写入GRAM
	LCD->LCD_RAM=POINT_COLOR; 
}
//快速画点
//x,y:坐标
//color:颜色
void TFT_LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{	 
  u8 i;  
	TFT_LCD_SetCursor(x,y);		//设置光标位置 
	TFT_LCD_WriteRAM_Prepare();	//开始写入GRAM
	LCD->LCD_RAM=color;
	
//	TFT_LCD_WR_REG(lcddev.setxcmd);TFT_LCD_WR_DATA(x>>8);  
//	TFT_LCD_WR_REG(lcddev.setxcmd+1);TFT_LCD_WR_DATA(x&0XFF);	  
//	TFT_LCD_WR_REG(lcddev.setycmd);TFT_LCD_WR_DATA(y>>8);  
//	TFT_LCD_WR_REG(lcddev.setycmd+1);TFT_LCD_WR_DATA(y&0XFF); 
//	LCD->LCD_REG=lcddev.wramcmd; 
//	LCD->LCD_RAM=color; 
}	 
//SSD1963 背光设置
//pwm:背光等级,0~100.越大越亮.
void TFT_LCD_SSD_BackLightSet(u8 pwm)
{	
	TFT_LCD_WR_REG(0xBE);	//配置PWM输出
	TFT_LCD_WR_DATA(0x05);	//1设置PWM频率
	TFT_LCD_WR_DATA(pwm*2.55);//2设置PWM占空比
	TFT_LCD_WR_DATA(0x01);	//3设置C
	TFT_LCD_WR_DATA(0xFF);	//4设置D
	TFT_LCD_WR_DATA(0x00);	//5设置E
	TFT_LCD_WR_DATA(0x00);	//6设置F
}

//设置LCD显示方向
//dir:0,竖屏；1,横屏
void TFT_LCD_Display_Dir(u8 dir)
{
	if(dir==0)			//竖屏
	{
		lcddev.dir=0;	//竖屏
		lcddev.wramcmd=0X2C00;
		lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00; 
		lcddev.width=480;
		lcddev.height=800;
	}
	else 				//横屏
	{	  				
		lcddev.dir=1;	//横屏
		lcddev.wramcmd=0X2C00;
		lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00; 
		lcddev.width=800;
		lcddev.height=480;
	} 
	TFT_LCD_Scan_Dir(DFT_SCAN_DIR);	//默认扫描方向
}	 
//设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//sx,sy:窗口起始坐标(左上角)
//width,height:窗口宽度和高度,必须大于0!!
//窗体大小:width*height. 
void TFT_LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{    
	u8 hsareg,heareg,vsareg,veareg;
	u16 hsaval,heaval,vsaval,veaval; 
	u16 twidth,theight;
	twidth=sx+width-1;
	theight=sy+height-1;
	TFT_LCD_WR_REG(lcddev.setxcmd);TFT_LCD_WR_DATA(sx>>8);  
	TFT_LCD_WR_REG(lcddev.setxcmd+1);TFT_LCD_WR_DATA(sx&0XFF);	  
	TFT_LCD_WR_REG(lcddev.setxcmd+2);TFT_LCD_WR_DATA(twidth>>8);   
	TFT_LCD_WR_REG(lcddev.setxcmd+3);TFT_LCD_WR_DATA(twidth&0XFF);   
	TFT_LCD_WR_REG(lcddev.setycmd);TFT_LCD_WR_DATA(sy>>8);   
	TFT_LCD_WR_REG(lcddev.setycmd+1);TFT_LCD_WR_DATA(sy&0XFF);  
	TFT_LCD_WR_REG(lcddev.setycmd+2);TFT_LCD_WR_DATA(theight>>8);   
	TFT_LCD_WR_REG(lcddev.setycmd+3);TFT_LCD_WR_DATA(theight&0XFF);  
	
}
//初始化lcd
//该初始化函数可以初始化各种ILI93XX液晶,但是其他函数是基于ILI9320的!!!
//在其他型号的驱动芯片上没有测试! 
void TFT_LCD_Init(void)
{ 	
	vu32 i=0;
  GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);//使能PD,PE,PF,PG时钟  
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟  
	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PB15 推挽输出,控制背光
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化 //PB15 推挽输出,控制背光
	
  GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14);//PD0,1,4,5,8,9,10,14,15 AF OUT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化  
	
  GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);//PE7~15,AF OUT
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PF12,FSMC_A6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PF12,FSMC_A6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化 

  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);//PD0,AF12
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);//PD1,AF12
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);//PD15,AF12
 
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);//PE7,AF12
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);//PE15,AF12
 
  GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FSMC);//PF12,AF12
  GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);


  readWriteTiming.FSMC_AddressSetupTime = 0X0F;	 //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns	
  readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
  readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
  readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
  readWriteTiming.FSMC_CLKDivision = 0x00;
  readWriteTiming.FSMC_DataLatency = 0x00;
  readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

	writeTiming.FSMC_AddressSetupTime =9;	      //地址建立时间（ADDSET）为9个HCLK =54ns 
  writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
  writeTiming.FSMC_DataSetupTime = 8;		 //数据保存时间为6ns*9个HCLK=54ns
  writeTiming.FSMC_BusTurnAroundDuration = 0x00;
  writeTiming.FSMC_CLKDivision = 0x01;
  writeTiming.FSMC_DataLatency = 0x01;
  writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

 
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
  FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
		
 	delay_ms(50); // delay 50 ms 
 	TFT_LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
  lcddev.id = TFT_LCD_ReadReg(0x0000);   
  if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)//读到ID不正确,新增lcddev.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
	{	
 		//尝试9341 ID的读取		
		TFT_LCD_WR_REG(0XD3);				   
		lcddev.id=TFT_LCD_RD_DATA();	//dummy read 	
 		lcddev.id=TFT_LCD_RD_DATA();	//读到0X00
  	lcddev.id=TFT_LCD_RD_DATA();   	//读取93								   
 		lcddev.id<<=8;
		lcddev.id|=TFT_LCD_RD_DATA();  	//读取41 	   			   
 		
	} 
	
		//重新配置写时序控制寄存器的时序   	 							    
		FSMC_Bank1E->BWTR[6]&=~(0XF<<0); //地址建立时间(ADDSET)清零 	 
		FSMC_Bank1E->BWTR[6]&=~(0XF<<8); //数据保存时间清零
		FSMC_Bank1E->BWTR[6]|=3<<0;		   //地址建立时间(ADDSET)为3个HCLK =18ns  	 
		FSMC_Bank1E->BWTR[6]|=2<<8; 	   //数据保存时间(DATAST)为6ns*3个HCLK=18ns
		TFT_LCD_WriteReg(0xF000,0x55);
		TFT_LCD_WriteReg(0xF001,0xAA);
		TFT_LCD_WriteReg(0xF002,0x52);
		TFT_LCD_WriteReg(0xF003,0x08);
		TFT_LCD_WriteReg(0xF004,0x01);
		//AVDD Set AVDD 5.2V
		TFT_LCD_WriteReg(0xB000,0x0D);
		TFT_LCD_WriteReg(0xB001,0x0D);
		TFT_LCD_WriteReg(0xB002,0x0D);
		//AVDD ratio
		TFT_LCD_WriteReg(0xB600,0x34);
		TFT_LCD_WriteReg(0xB601,0x34);
		TFT_LCD_WriteReg(0xB602,0x34);
		//AVEE -5.2V
		TFT_LCD_WriteReg(0xB100,0x0D);
		TFT_LCD_WriteReg(0xB101,0x0D);
		TFT_LCD_WriteReg(0xB102,0x0D);
		//AVEE ratio
		TFT_LCD_WriteReg(0xB700,0x34);
		TFT_LCD_WriteReg(0xB701,0x34);
		TFT_LCD_WriteReg(0xB702,0x34);
		//VCL -2.5V
		TFT_LCD_WriteReg(0xB200,0x00);
		TFT_LCD_WriteReg(0xB201,0x00);
		TFT_LCD_WriteReg(0xB202,0x00);
		//VCL ratio
		TFT_LCD_WriteReg(0xB800,0x24);
		TFT_LCD_WriteReg(0xB801,0x24);
		TFT_LCD_WriteReg(0xB802,0x24);
		//VGH 15V (Free pump)
		TFT_LCD_WriteReg(0xBF00,0x01);
		TFT_LCD_WriteReg(0xB300,0x0F);
		TFT_LCD_WriteReg(0xB301,0x0F);
		TFT_LCD_WriteReg(0xB302,0x0F);
		//VGH ratio
		TFT_LCD_WriteReg(0xB900,0x34);
		TFT_LCD_WriteReg(0xB901,0x34);
		TFT_LCD_WriteReg(0xB902,0x34);
		//VGL_REG -10V
		TFT_LCD_WriteReg(0xB500,0x08);
		TFT_LCD_WriteReg(0xB501,0x08);
		TFT_LCD_WriteReg(0xB502,0x08);
		TFT_LCD_WriteReg(0xC200,0x03);
		//VGLX ratio
		TFT_LCD_WriteReg(0xBA00,0x24);
		TFT_LCD_WriteReg(0xBA01,0x24);
		TFT_LCD_WriteReg(0xBA02,0x24);
		//VGMP/VGSP 4.5V/0V
		TFT_LCD_WriteReg(0xBC00,0x00);
		TFT_LCD_WriteReg(0xBC01,0x78);
		TFT_LCD_WriteReg(0xBC02,0x00);
		//VGMN/VGSN -4.5V/0V
		TFT_LCD_WriteReg(0xBD00,0x00);
		TFT_LCD_WriteReg(0xBD01,0x78);
		TFT_LCD_WriteReg(0xBD02,0x00);
		//VCOM
		TFT_LCD_WriteReg(0xBE00,0x00);
		TFT_LCD_WriteReg(0xBE01,0x64);
		//Gamma Setting
		TFT_LCD_WriteReg(0xD100,0x00);
		TFT_LCD_WriteReg(0xD101,0x33);
		TFT_LCD_WriteReg(0xD102,0x00);
		TFT_LCD_WriteReg(0xD103,0x34);
		TFT_LCD_WriteReg(0xD104,0x00);
		TFT_LCD_WriteReg(0xD105,0x3A);
		TFT_LCD_WriteReg(0xD106,0x00);
		TFT_LCD_WriteReg(0xD107,0x4A);
		TFT_LCD_WriteReg(0xD108,0x00);
		TFT_LCD_WriteReg(0xD109,0x5C);
		TFT_LCD_WriteReg(0xD10A,0x00);
		TFT_LCD_WriteReg(0xD10B,0x81);
		TFT_LCD_WriteReg(0xD10C,0x00);
		TFT_LCD_WriteReg(0xD10D,0xA6);
		TFT_LCD_WriteReg(0xD10E,0x00);
		TFT_LCD_WriteReg(0xD10F,0xE5);
		TFT_LCD_WriteReg(0xD110,0x01);
		TFT_LCD_WriteReg(0xD111,0x13);
		TFT_LCD_WriteReg(0xD112,0x01);
		TFT_LCD_WriteReg(0xD113,0x54);
		TFT_LCD_WriteReg(0xD114,0x01);
		TFT_LCD_WriteReg(0xD115,0x82);
		TFT_LCD_WriteReg(0xD116,0x01);
		TFT_LCD_WriteReg(0xD117,0xCA);
		TFT_LCD_WriteReg(0xD118,0x02);
		TFT_LCD_WriteReg(0xD119,0x00);
		TFT_LCD_WriteReg(0xD11A,0x02);
		TFT_LCD_WriteReg(0xD11B,0x01);
		TFT_LCD_WriteReg(0xD11C,0x02);
		TFT_LCD_WriteReg(0xD11D,0x34);
		TFT_LCD_WriteReg(0xD11E,0x02);
		TFT_LCD_WriteReg(0xD11F,0x67);
		TFT_LCD_WriteReg(0xD120,0x02);
		TFT_LCD_WriteReg(0xD121,0x84);
		TFT_LCD_WriteReg(0xD122,0x02);
		TFT_LCD_WriteReg(0xD123,0xA4);
		TFT_LCD_WriteReg(0xD124,0x02);
		TFT_LCD_WriteReg(0xD125,0xB7);
		TFT_LCD_WriteReg(0xD126,0x02);
		TFT_LCD_WriteReg(0xD127,0xCF);
		TFT_LCD_WriteReg(0xD128,0x02);
		TFT_LCD_WriteReg(0xD129,0xDE);
		TFT_LCD_WriteReg(0xD12A,0x02);
		TFT_LCD_WriteReg(0xD12B,0xF2);
		TFT_LCD_WriteReg(0xD12C,0x02);
		TFT_LCD_WriteReg(0xD12D,0xFE);
		TFT_LCD_WriteReg(0xD12E,0x03);
		TFT_LCD_WriteReg(0xD12F,0x10);
		TFT_LCD_WriteReg(0xD130,0x03);
		TFT_LCD_WriteReg(0xD131,0x33);
		TFT_LCD_WriteReg(0xD132,0x03);
		TFT_LCD_WriteReg(0xD133,0x6D);
		TFT_LCD_WriteReg(0xD200,0x00);
		TFT_LCD_WriteReg(0xD201,0x33);
		TFT_LCD_WriteReg(0xD202,0x00);
		TFT_LCD_WriteReg(0xD203,0x34);
		TFT_LCD_WriteReg(0xD204,0x00);
		TFT_LCD_WriteReg(0xD205,0x3A);
		TFT_LCD_WriteReg(0xD206,0x00);
		TFT_LCD_WriteReg(0xD207,0x4A);
		TFT_LCD_WriteReg(0xD208,0x00);
		TFT_LCD_WriteReg(0xD209,0x5C);
		TFT_LCD_WriteReg(0xD20A,0x00);

		TFT_LCD_WriteReg(0xD20B,0x81);
		TFT_LCD_WriteReg(0xD20C,0x00);
		TFT_LCD_WriteReg(0xD20D,0xA6);
		TFT_LCD_WriteReg(0xD20E,0x00);
		TFT_LCD_WriteReg(0xD20F,0xE5);
		TFT_LCD_WriteReg(0xD210,0x01);
		TFT_LCD_WriteReg(0xD211,0x13);
		TFT_LCD_WriteReg(0xD212,0x01);
		TFT_LCD_WriteReg(0xD213,0x54);
		TFT_LCD_WriteReg(0xD214,0x01);
		TFT_LCD_WriteReg(0xD215,0x82);
		TFT_LCD_WriteReg(0xD216,0x01);
		TFT_LCD_WriteReg(0xD217,0xCA);
		TFT_LCD_WriteReg(0xD218,0x02);
		TFT_LCD_WriteReg(0xD219,0x00);
		TFT_LCD_WriteReg(0xD21A,0x02);
		TFT_LCD_WriteReg(0xD21B,0x01);
		TFT_LCD_WriteReg(0xD21C,0x02);
		TFT_LCD_WriteReg(0xD21D,0x34);
		TFT_LCD_WriteReg(0xD21E,0x02);
		TFT_LCD_WriteReg(0xD21F,0x67);
		TFT_LCD_WriteReg(0xD220,0x02);
		TFT_LCD_WriteReg(0xD221,0x84);
		TFT_LCD_WriteReg(0xD222,0x02);
		TFT_LCD_WriteReg(0xD223,0xA4);
		TFT_LCD_WriteReg(0xD224,0x02);
		TFT_LCD_WriteReg(0xD225,0xB7);
		TFT_LCD_WriteReg(0xD226,0x02);
		TFT_LCD_WriteReg(0xD227,0xCF);
		TFT_LCD_WriteReg(0xD228,0x02);
		TFT_LCD_WriteReg(0xD229,0xDE);
		TFT_LCD_WriteReg(0xD22A,0x02);
		TFT_LCD_WriteReg(0xD22B,0xF2);
		TFT_LCD_WriteReg(0xD22C,0x02);
		TFT_LCD_WriteReg(0xD22D,0xFE);
		TFT_LCD_WriteReg(0xD22E,0x03);
		TFT_LCD_WriteReg(0xD22F,0x10);
		TFT_LCD_WriteReg(0xD230,0x03);
		TFT_LCD_WriteReg(0xD231,0x33);
		TFT_LCD_WriteReg(0xD232,0x03);
		TFT_LCD_WriteReg(0xD233,0x6D);
		TFT_LCD_WriteReg(0xD300,0x00);
		TFT_LCD_WriteReg(0xD301,0x33);
		TFT_LCD_WriteReg(0xD302,0x00);
		TFT_LCD_WriteReg(0xD303,0x34);
		TFT_LCD_WriteReg(0xD304,0x00);
		TFT_LCD_WriteReg(0xD305,0x3A);
		TFT_LCD_WriteReg(0xD306,0x00);
		TFT_LCD_WriteReg(0xD307,0x4A);
		TFT_LCD_WriteReg(0xD308,0x00);
		TFT_LCD_WriteReg(0xD309,0x5C);
		TFT_LCD_WriteReg(0xD30A,0x00);

		TFT_LCD_WriteReg(0xD30B,0x81);
		TFT_LCD_WriteReg(0xD30C,0x00);
		TFT_LCD_WriteReg(0xD30D,0xA6);
		TFT_LCD_WriteReg(0xD30E,0x00);
		TFT_LCD_WriteReg(0xD30F,0xE5);
		TFT_LCD_WriteReg(0xD310,0x01);
		TFT_LCD_WriteReg(0xD311,0x13);
		TFT_LCD_WriteReg(0xD312,0x01);
		TFT_LCD_WriteReg(0xD313,0x54);
		TFT_LCD_WriteReg(0xD314,0x01);
		TFT_LCD_WriteReg(0xD315,0x82);
		TFT_LCD_WriteReg(0xD316,0x01);
		TFT_LCD_WriteReg(0xD317,0xCA);
		TFT_LCD_WriteReg(0xD318,0x02);
		TFT_LCD_WriteReg(0xD319,0x00);
		TFT_LCD_WriteReg(0xD31A,0x02);
		TFT_LCD_WriteReg(0xD31B,0x01);
		TFT_LCD_WriteReg(0xD31C,0x02);
		TFT_LCD_WriteReg(0xD31D,0x34);
		TFT_LCD_WriteReg(0xD31E,0x02);
		TFT_LCD_WriteReg(0xD31F,0x67);
		TFT_LCD_WriteReg(0xD320,0x02);
		TFT_LCD_WriteReg(0xD321,0x84);
		TFT_LCD_WriteReg(0xD322,0x02);
		TFT_LCD_WriteReg(0xD323,0xA4);
		TFT_LCD_WriteReg(0xD324,0x02);
		TFT_LCD_WriteReg(0xD325,0xB7);
		TFT_LCD_WriteReg(0xD326,0x02);
		TFT_LCD_WriteReg(0xD327,0xCF);
		TFT_LCD_WriteReg(0xD328,0x02);
		TFT_LCD_WriteReg(0xD329,0xDE);
		TFT_LCD_WriteReg(0xD32A,0x02);
		TFT_LCD_WriteReg(0xD32B,0xF2);
		TFT_LCD_WriteReg(0xD32C,0x02);
		TFT_LCD_WriteReg(0xD32D,0xFE);
		TFT_LCD_WriteReg(0xD32E,0x03);
		TFT_LCD_WriteReg(0xD32F,0x10);
		TFT_LCD_WriteReg(0xD330,0x03);
		TFT_LCD_WriteReg(0xD331,0x33);
		TFT_LCD_WriteReg(0xD332,0x03);
		TFT_LCD_WriteReg(0xD333,0x6D);
		TFT_LCD_WriteReg(0xD400,0x00);
		TFT_LCD_WriteReg(0xD401,0x33);
		TFT_LCD_WriteReg(0xD402,0x00);
		TFT_LCD_WriteReg(0xD403,0x34);
		TFT_LCD_WriteReg(0xD404,0x00);
		TFT_LCD_WriteReg(0xD405,0x3A);
		TFT_LCD_WriteReg(0xD406,0x00);
		TFT_LCD_WriteReg(0xD407,0x4A);
		TFT_LCD_WriteReg(0xD408,0x00);
		TFT_LCD_WriteReg(0xD409,0x5C);
		TFT_LCD_WriteReg(0xD40A,0x00);
		TFT_LCD_WriteReg(0xD40B,0x81);

		TFT_LCD_WriteReg(0xD40C,0x00);
		TFT_LCD_WriteReg(0xD40D,0xA6);
		TFT_LCD_WriteReg(0xD40E,0x00);
		TFT_LCD_WriteReg(0xD40F,0xE5);
		TFT_LCD_WriteReg(0xD410,0x01);
		TFT_LCD_WriteReg(0xD411,0x13);
		TFT_LCD_WriteReg(0xD412,0x01);
		TFT_LCD_WriteReg(0xD413,0x54);
		TFT_LCD_WriteReg(0xD414,0x01);
		TFT_LCD_WriteReg(0xD415,0x82);
		TFT_LCD_WriteReg(0xD416,0x01);
		TFT_LCD_WriteReg(0xD417,0xCA);
		TFT_LCD_WriteReg(0xD418,0x02);
		TFT_LCD_WriteReg(0xD419,0x00);
		TFT_LCD_WriteReg(0xD41A,0x02);
		TFT_LCD_WriteReg(0xD41B,0x01);
		TFT_LCD_WriteReg(0xD41C,0x02);
		TFT_LCD_WriteReg(0xD41D,0x34);
		TFT_LCD_WriteReg(0xD41E,0x02);
		TFT_LCD_WriteReg(0xD41F,0x67);
		TFT_LCD_WriteReg(0xD420,0x02);
		TFT_LCD_WriteReg(0xD421,0x84);
		TFT_LCD_WriteReg(0xD422,0x02);
		TFT_LCD_WriteReg(0xD423,0xA4);
		TFT_LCD_WriteReg(0xD424,0x02);
		TFT_LCD_WriteReg(0xD425,0xB7);
		TFT_LCD_WriteReg(0xD426,0x02);
		TFT_LCD_WriteReg(0xD427,0xCF);
		TFT_LCD_WriteReg(0xD428,0x02);
		TFT_LCD_WriteReg(0xD429,0xDE);
		TFT_LCD_WriteReg(0xD42A,0x02);
		TFT_LCD_WriteReg(0xD42B,0xF2);
		TFT_LCD_WriteReg(0xD42C,0x02);
		TFT_LCD_WriteReg(0xD42D,0xFE);
		TFT_LCD_WriteReg(0xD42E,0x03);
		TFT_LCD_WriteReg(0xD42F,0x10);
		TFT_LCD_WriteReg(0xD430,0x03);
		TFT_LCD_WriteReg(0xD431,0x33);
		TFT_LCD_WriteReg(0xD432,0x03);
		TFT_LCD_WriteReg(0xD433,0x6D);
		TFT_LCD_WriteReg(0xD500,0x00);
		TFT_LCD_WriteReg(0xD501,0x33);
		TFT_LCD_WriteReg(0xD502,0x00);
		TFT_LCD_WriteReg(0xD503,0x34);
		TFT_LCD_WriteReg(0xD504,0x00);
		TFT_LCD_WriteReg(0xD505,0x3A);
		TFT_LCD_WriteReg(0xD506,0x00);
		TFT_LCD_WriteReg(0xD507,0x4A);
		TFT_LCD_WriteReg(0xD508,0x00);
		TFT_LCD_WriteReg(0xD509,0x5C);
		TFT_LCD_WriteReg(0xD50A,0x00);
		TFT_LCD_WriteReg(0xD50B,0x81);

		TFT_LCD_WriteReg(0xD50C,0x00);
		TFT_LCD_WriteReg(0xD50D,0xA6);
		TFT_LCD_WriteReg(0xD50E,0x00);
		TFT_LCD_WriteReg(0xD50F,0xE5);
		TFT_LCD_WriteReg(0xD510,0x01);
		TFT_LCD_WriteReg(0xD511,0x13);
		TFT_LCD_WriteReg(0xD512,0x01);
		TFT_LCD_WriteReg(0xD513,0x54);
		TFT_LCD_WriteReg(0xD514,0x01);
		TFT_LCD_WriteReg(0xD515,0x82);
		TFT_LCD_WriteReg(0xD516,0x01);
		TFT_LCD_WriteReg(0xD517,0xCA);
		TFT_LCD_WriteReg(0xD518,0x02);
		TFT_LCD_WriteReg(0xD519,0x00);
		TFT_LCD_WriteReg(0xD51A,0x02);
		TFT_LCD_WriteReg(0xD51B,0x01);
		TFT_LCD_WriteReg(0xD51C,0x02);
		TFT_LCD_WriteReg(0xD51D,0x34);
		TFT_LCD_WriteReg(0xD51E,0x02);
		TFT_LCD_WriteReg(0xD51F,0x67);
		TFT_LCD_WriteReg(0xD520,0x02);
		TFT_LCD_WriteReg(0xD521,0x84);
		TFT_LCD_WriteReg(0xD522,0x02);
		TFT_LCD_WriteReg(0xD523,0xA4);
		TFT_LCD_WriteReg(0xD524,0x02);
		TFT_LCD_WriteReg(0xD525,0xB7);
		TFT_LCD_WriteReg(0xD526,0x02);
		TFT_LCD_WriteReg(0xD527,0xCF);
		TFT_LCD_WriteReg(0xD528,0x02);
		TFT_LCD_WriteReg(0xD529,0xDE);
		TFT_LCD_WriteReg(0xD52A,0x02);
		TFT_LCD_WriteReg(0xD52B,0xF2);
		TFT_LCD_WriteReg(0xD52C,0x02);
		TFT_LCD_WriteReg(0xD52D,0xFE);
		TFT_LCD_WriteReg(0xD52E,0x03);
		TFT_LCD_WriteReg(0xD52F,0x10);
		TFT_LCD_WriteReg(0xD530,0x03);
		TFT_LCD_WriteReg(0xD531,0x33);
		TFT_LCD_WriteReg(0xD532,0x03);
		TFT_LCD_WriteReg(0xD533,0x6D);
		TFT_LCD_WriteReg(0xD600,0x00);
		TFT_LCD_WriteReg(0xD601,0x33);
		TFT_LCD_WriteReg(0xD602,0x00);
		TFT_LCD_WriteReg(0xD603,0x34);
		TFT_LCD_WriteReg(0xD604,0x00);
		TFT_LCD_WriteReg(0xD605,0x3A);
		TFT_LCD_WriteReg(0xD606,0x00);
		TFT_LCD_WriteReg(0xD607,0x4A);
		TFT_LCD_WriteReg(0xD608,0x00);
		TFT_LCD_WriteReg(0xD609,0x5C);
		TFT_LCD_WriteReg(0xD60A,0x00);
		TFT_LCD_WriteReg(0xD60B,0x81);

		TFT_LCD_WriteReg(0xD60C,0x00);
		TFT_LCD_WriteReg(0xD60D,0xA6);
		TFT_LCD_WriteReg(0xD60E,0x00);
		TFT_LCD_WriteReg(0xD60F,0xE5);
		TFT_LCD_WriteReg(0xD610,0x01);
		TFT_LCD_WriteReg(0xD611,0x13);
		TFT_LCD_WriteReg(0xD612,0x01);
		TFT_LCD_WriteReg(0xD613,0x54);
		TFT_LCD_WriteReg(0xD614,0x01);
		TFT_LCD_WriteReg(0xD615,0x82);
		TFT_LCD_WriteReg(0xD616,0x01);
		TFT_LCD_WriteReg(0xD617,0xCA);
		TFT_LCD_WriteReg(0xD618,0x02);
		TFT_LCD_WriteReg(0xD619,0x00);
		TFT_LCD_WriteReg(0xD61A,0x02);
		TFT_LCD_WriteReg(0xD61B,0x01);
		TFT_LCD_WriteReg(0xD61C,0x02);
		TFT_LCD_WriteReg(0xD61D,0x34);
		TFT_LCD_WriteReg(0xD61E,0x02);
		TFT_LCD_WriteReg(0xD61F,0x67);
		TFT_LCD_WriteReg(0xD620,0x02);
		TFT_LCD_WriteReg(0xD621,0x84);
		TFT_LCD_WriteReg(0xD622,0x02);
		TFT_LCD_WriteReg(0xD623,0xA4);
		TFT_LCD_WriteReg(0xD624,0x02);
		TFT_LCD_WriteReg(0xD625,0xB7);
		TFT_LCD_WriteReg(0xD626,0x02);
		TFT_LCD_WriteReg(0xD627,0xCF);
		TFT_LCD_WriteReg(0xD628,0x02);
		TFT_LCD_WriteReg(0xD629,0xDE);
		TFT_LCD_WriteReg(0xD62A,0x02);
		TFT_LCD_WriteReg(0xD62B,0xF2);
		TFT_LCD_WriteReg(0xD62C,0x02);
		TFT_LCD_WriteReg(0xD62D,0xFE);
		TFT_LCD_WriteReg(0xD62E,0x03);
		TFT_LCD_WriteReg(0xD62F,0x10);
		TFT_LCD_WriteReg(0xD630,0x03);
		TFT_LCD_WriteReg(0xD631,0x33);
		TFT_LCD_WriteReg(0xD632,0x03);
		TFT_LCD_WriteReg(0xD633,0x6D);
		//LV2 Page 0 enable
		TFT_LCD_WriteReg(0xF000,0x55);
		TFT_LCD_WriteReg(0xF001,0xAA);
		TFT_LCD_WriteReg(0xF002,0x52);
		TFT_LCD_WriteReg(0xF003,0x08);
		TFT_LCD_WriteReg(0xF004,0x00);
		//Display control
		TFT_LCD_WriteReg(0xB100, 0xCC);
		TFT_LCD_WriteReg(0xB101, 0x00);
		//Source hold time
		TFT_LCD_WriteReg(0xB600,0x05);
		//Gate EQ control
		TFT_LCD_WriteReg(0xB700,0x70);
		TFT_LCD_WriteReg(0xB701,0x70);
		//Source EQ control (Mode 2)
		TFT_LCD_WriteReg(0xB800,0x01);
		TFT_LCD_WriteReg(0xB801,0x03);
		TFT_LCD_WriteReg(0xB802,0x03);
		TFT_LCD_WriteReg(0xB803,0x03);
		//Inversion mode (2-dot)
		TFT_LCD_WriteReg(0xBC00,0x02);
		TFT_LCD_WriteReg(0xBC01,0x00);
		TFT_LCD_WriteReg(0xBC02,0x00);
		//Timing control 4H w/ 4-delay
		TFT_LCD_WriteReg(0xC900,0xD0);
		TFT_LCD_WriteReg(0xC901,0x02);
		TFT_LCD_WriteReg(0xC902,0x50);
		TFT_LCD_WriteReg(0xC903,0x50);
		TFT_LCD_WriteReg(0xC904,0x50);
		TFT_LCD_WriteReg(0x3500,0x00);
		TFT_LCD_WriteReg(0x3A00,0x55);  //16-bit/pixel
		TFT_LCD_WR_REG(0x1100);
		delay_us(120);
		TFT_LCD_WR_REG(0x2900);
	
	TFT_LCD_Display_Dir(1);		//默认为竖屏
	TFT_LCD_LED=1;				//点亮背光
	TFT_LCD_Clear(BACK_COLOR);
}  
//清屏函数
//color:要清屏的填充色
void TFT_LCD_Clear(u16 color)
{
	u32 index=0;      
	u32 totalpoint=lcddev.width;
	totalpoint*=lcddev.height ; 			//得到总点数
//	totalpoint=totalpoint/2;
	TFT_LCD_SetCursor(0x00,0x0000);	//设置光标位置 
	TFT_LCD_WriteRAM_Prepare();     		//开始写入GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	
	}
}
void TFT_LCD_SetWindow(u16 sx,u16 sy,u16 width,u16 height)
{
	u16 twidth,theight;
	twidth=sx+width-1;
	theight=sy+height-1;
	TFT_LCD_WR_REG(lcddev.setxcmd);TFT_LCD_WR_DATA(sx>>8);  
	TFT_LCD_WR_REG(lcddev.setxcmd+1);TFT_LCD_WR_DATA(sx&0XFF);	  
	TFT_LCD_WR_REG(lcddev.setxcmd+2);TFT_LCD_WR_DATA(twidth>>8);   
	TFT_LCD_WR_REG(lcddev.setxcmd+3);TFT_LCD_WR_DATA(twidth&0XFF);   
	TFT_LCD_WR_REG(lcddev.setycmd);TFT_LCD_WR_DATA(sy>>8);   
	TFT_LCD_WR_REG(lcddev.setycmd+1);TFT_LCD_WR_DATA(sy&0XFF);  
	TFT_LCD_WR_REG(lcddev.setycmd+2);TFT_LCD_WR_DATA(theight>>8);   
	TFT_LCD_WR_REG(lcddev.setycmd+3);TFT_LCD_WR_DATA(theight&0XFF);
}
void TFT_LCD_ShowTop(void)
{
//	u8 i;
	volatile u16 AddressX=93,AddressY=35;
	volatile u16 AddressX1=478,AddressY1=39;
	TFT_LCD_ShowTop1(AddressX,AddressY);
	TFT_LCD_ShowTop2(AddressX1,AddressY1);
}
u16 TFT_LCD_ShowTop1(u16 x ,u16 y)
{
	u8 InfNum[5]={0,1,2,3,4};
	u16 i,j,k,m,n;
  u16 Infs[320];
	u16 x1,y1;
	u16 l;
	u16 StartNum;
	u16 Index=0;
	x1=x;
	y1=y;
  for(i=0;i<320;i++)
		Infs[i]=BACK_COLOR;
	for(i=0;i<64;i++)
	{
		
		for(j=0;j<5;j++)
		{
			StartNum=InfNum[j]*512+8*i;
			for(k=0;k<8;k++)
			{
				l=Char_L[StartNum];
				for(m=0;m<8;m++)
				{
					if(l&0x80)
						Infs[Index]=POINT_COLOR;
					else
						Infs[Index]=BACK_COLOR;
					l<<=1;
					Index++;
				}
				StartNum++;
			}
		}
		TFT_LCD_SetCursor(x1,y1+i);	//设置光标位置 
		TFT_LCD_SetCursor(x1,y1+i);	//设置光标位置 
 	  TFT_LCD_WriteRAM_Prepare();
		for(n=0;n<Index;n++)
			LCD->LCD_RAM=Infs[n];
		Index=0;
	}	
}
u16 TFT_LCD_ShowTop2(u16 x ,u16 y)
{
	u8 InfNum[5]={0,1,2,3};
	u16 i,j,k,m,n;
	u16 Inf[320];
	u16 StartNum;
	u16 Index=0;
	u16 x1,y1;
	volatile  u16 l;
	x1=x;
	y1=y;	
	for(i=0;i<320;i++)
   Inf[i]=BACK_COLOR;
	for(i=0;i<56;i++)
	{
		
		for(j=0;j<4;j++)
		{
			StartNum=InfNum[j]*392+7*i;
			for(k=0;k<7;k++)
			{
				l=Char_S[StartNum];
				for(m=0;m<8;m++)
				{
					if(l&0x80)
						Inf[Index]=POINT_COLOR;
					else
						Inf[Index]=BACK_COLOR;
					l<<=1;
					Index++;
				}
				StartNum++;
			}
		}
		Index=320;		
		TFT_LCD_SetCursor(x1,y1+i);	//设置光标位置 
		TFT_LCD_SetCursor(x1,y1+i);	//设置光标位置 
 	  TFT_LCD_WriteRAM_Prepare();
		for(n=0;n<Index;n++)
			LCD->LCD_RAM=Inf[n];
		Index=0;
	}	
}
void TFT_LCD_Show_Inf1(u16 x,u16 y,u8 *InfNum,u8 Num)
{
	u16 i,j,k,m,n;
	u16 Inf[320];
	u16 StartNum;
	u16 Index=0;
	volatile u16 l;
	for(i=0;i<320;i++)
   Inf[i]=BACK_COLOR;
	for(i=0;i<48;i++)
	{
		
		for(j=0;j<Num;j++)
		{
			StartNum=InfNum[j]*288+6*i;
			for(k=0;k<6;k++)
			{
				l=Char_Ss[StartNum];
				for(m=0;m<8;m++)
				{
					if(l&0x80)
						Inf[Index]=POINT_COLOR;
					else
						Inf[Index]=BACK_COLOR;
					l<<=1;
					Index++;
				}
				StartNum++;
			}
		}
		Index=320;
		TFT_LCD_SetCursor(x,y+i);	//设置光标位置 
		TFT_LCD_SetCursor(x,y+i);	//设置光标位置 
 	  TFT_LCD_WriteRAM_Prepare();
		for(n=0;n<Index;n++)
			LCD->LCD_RAM=Inf[n];
		Index=0;
	}	
}
void TFT_LCD_Show_Inf2(u16 x,u16 y,u8 *InfNum,u8 Num)
{
	u16 i,j,k,m,n;
	u16 Inf[370];
	u16 StartNum;
	u16 Index=0;
	volatile u16 l;
	for(i=0;i<370;i++)
   Inf[i]=BACK_COLOR;
	for(i=0;i<48;i++)
	{
		
		for(j=0;j<Num;j++)
		{
			StartNum=InfNum[j]*144+3*i;
			for(k=0;k<3;k++)
			{
				l=Chars[StartNum];
				for(m=0;m<8;m++)
				{
					if(l&0x80)
						Inf[Index+50]=POINT_COLOR;
					else
						Inf[Index+50]=BACK_COLOR;
					l<<=1;
					Index++;
				}
				StartNum++;
			}
		}
		Index=370;
		TFT_LCD_SetCursor(x-50,y+i);	//设置光标位置 
		TFT_LCD_SetCursor(x-50,y+i);	//设置光标位置 
 	  TFT_LCD_WriteRAM_Prepare();
		for(n=0;n<Index;n++)
			LCD->LCD_RAM=Inf[n];
		Index=0;
	}	
}
void TFT_LCD_Show_Inf3(u16 x,u16 y,u8 *InfNum,u8 Num)
{
	u16 i,j,k,m,n;
	u16 Inf[420];
	u16 StartNum;
	u16 Index=0;
	volatile u16 l;
	for(i=0;i<420;i++)
   Inf[i]=BACK_COLOR;
	for(i=0;i<48;i++)
	{
		
		for(j=0;j<Num;j++)
		{
			StartNum=InfNum[j]*288+6*i;
			for(k=0;k<6;k++)
			{
				l=Char_Ss[StartNum];
				for(m=0;m<8;m++)
				{
					if(l&0x80)
						Inf[Index+100]=POINT_COLOR;
					else
						Inf[Index+100]=BACK_COLOR;
					l<<=1;
					Index++;
				}
				StartNum++;
			}
		}
		Index=420;
		TFT_LCD_SetCursor(x-100,y+i);	//设置光标位置 
		TFT_LCD_SetCursor(x-100,y+i);	//设置光标位置 
 	  TFT_LCD_WriteRAM_Prepare();
		for(n=0;n<Index;n++)
			LCD->LCD_RAM=Inf[n];
		Index=0;
	}	
}
void TFT_LCD_ShowPower(void)
{
	u16 AddressX=120,AddressY=140;
	u8 InfNum[4]={0,1,2,3};
	u8 Num=4; 
	TFT_LCD_Show_Inf1(AddressX,AddressY,InfNum,Num);
//	TFT_LCD_ShowCharSS(AddressX,AddressY,0);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,1);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,2);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,3);
}
void TFT_LCD_ShowPulse(void)
{
	u16 AddressX=120,AddressY=194;
	u8 InfNum[4]={4,5,6,3};
	u8 Num=4; 
	TFT_LCD_Show_Inf1(AddressX,AddressY,InfNum,Num);
//	TFT_LCD_ShowCharSS(AddressX,AddressY,4);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,5);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,6);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,3);
}
void TFT_LCD_ShowRed(void)
{
	u16 AddressX=120,AddressY=248;
	u8 InfNum[4]={7,1};
	u8 Num=2; 
	TFT_LCD_Show_Inf1(AddressX,AddressY,InfNum,Num);
//	TFT_LCD_ShowCharSS(AddressX,AddressY,7);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,1);
}
void TFT_LCD_ShowLaser(void)
{
	u16 AddressX=120,AddressY=302;
	u8 InfNum[4]={0,1};
	u8 Num=2; 
	TFT_LCD_Show_Inf1(AddressX,AddressY,InfNum,Num);
//	TFT_LCD_ShowCharSS(AddressX,AddressY,0);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,1);
}
void TFT_LCD_ShowMode(void)
{
	u16 AddressX=120,AddressY=356;
	u8 InfNum[4]={8,9};
	u8 Num=2; 
	TFT_LCD_Show_Inf1(AddressX,AddressY,InfNum,Num);
//	TFT_LCD_ShowCharSS(AddressX,AddressY,8);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,9);
}
void TFT_LCD_ShowWidth(void)
{
	u16 AddressX=120,AddressY=410;
	u8 InfNum[4]={10,11};
	u8 Num=2; 
	TFT_LCD_Show_Inf1(AddressX,AddressY,InfNum,Num);
//	TFT_LCD_ShowCharSS(AddressX,AddressY,10);
//	AddressX+=48;
//	TFT_LCD_ShowCharSS(AddressX,AddressY,11);
}
void ShowLine(void)
{
	u8 i;
	u16 index;
	u16 AddressX=35,AddressY=116;
	for(i=0;i<5;i++)
	{
		TFT_LCD_SetCursor(AddressX,AddressY+i);	//设置光标位置 
		TFT_LCD_SetCursor(AddressX,AddressY+i);	//设置光标位置 
	  TFT_LCD_WriteRAM_Prepare();
		for(index=0;index<730;index++)
		{
			LCD->LCD_RAM=POINT_COLOR;	
		}
	}
//	TFT_LCD_SetCursor(35,116);	//设置光标位置 
//	TFT_LCD_WriteRAM_Prepare();
//  for(index=0;index<730;index++)
//	{
//		LCD->LCD_RAM=POINT_COLOR;	
//	} 
//	TFT_LCD_SetCursor(35,117);	//设置光标位置 
//	TFT_LCD_WriteRAM_Prepare();
//  for(index=0;index<730;index++)
//	{
//		LCD->LCD_RAM=POINT_COLOR;	
//	} 
//	TFT_LCD_SetCursor(35,118);	//设置光标位置 
//	TFT_LCD_WriteRAM_Prepare();
//  for(index=0;index<730;index++)
//	{
//		LCD->LCD_RAM=POINT_COLOR;	
//	} 
//	TFT_LCD_SetCursor(35,119);	//设置光标位置 
//	TFT_LCD_WriteRAM_Prepare();
//  for(index=0;index<730;index++)
//	{
//		LCD->LCD_RAM=POINT_COLOR;	
//	} 
//	TFT_LCD_SetCursor(35,120);	//设置光标位置 
//	TFT_LCD_WriteRAM_Prepare();
//  for(index=0;index<730;index++)
//	{
//		LCD->LCD_RAM=POINT_COLOR;	
//	} 
}
void TFT_LCD_ShowADNum(u8 Value)
{
	u8 i;
	u16 Num;
	u8 InfNum[8];
	u16 AddressX=476,AddressY=140;
	Num=Value*200/51;
	InfNum[0]=12;
	if(Num<100)
	{
		i=Num/10;
		InfNum[1]=i;
		InfNum[2]=10;
		i=Num%10;
		InfNum[3]=i;
		InfNum[4]=11;
		InfNum[5]=12;
		InfNum[6]=12;
	}
	if(Num<1000&&Num>99)
	{
		i=Num/100;
		InfNum[1]=i;
		i=(Num%100)/10;
		InfNum[2]=i;
		InfNum[3]=10;
		i=Num%10;
		InfNum[4]=i;
		InfNum[5]=11;
		InfNum[6]=12;
	}
	if(Num==1000)
	{
		i=Num/1000;
		InfNum[1]=i;
		InfNum[2]=0;
		InfNum[3]=0;
		InfNum[4]=10;
		InfNum[5]=0;
		InfNum[6]=11;
	}
	 TFT_LCD_Show_Inf2(AddressX,AddressY,InfNum,7);
}
void TFT_LCD_ShowPulseValue(u16 Value)
{
	u8 i;
	u16 Num;
	u8 InfNum[8];
	u16 AddressX=476,AddressY=194;
	Num=Value*200/51;
	InfNum[0]=12;
	if(Value<100)
	{
		i=Value/10;
		InfNum[1]=i;
		i=Value%10;
		InfNum[2]=i;
		InfNum[3]=12;
	}
	else
	{
		i=Value/100;
		InfNum[1]=i;
		i=(Value%100)/10;
		InfNum[2]=i;
		i=Value%10;
		InfNum[3]=i;
	}
	TFT_LCD_Show_Inf2(AddressX,AddressY,InfNum,4);
}
void TFT_LCD_ShowRedValue(u8 Value)
{
	u16 AddressX=500,AddressY=248;
	u8 InfNum[4];
	u8 Num=1; 
	if(Value==1)
	{
		InfNum[0]=12;
//		TFT_LCD_ShowCharSS(AddressX,AddressY,12);
	}
	else
	{
		InfNum[0]=13;
	}
	TFT_LCD_Show_Inf3(AddressX,AddressY,InfNum,Num);

}
void TFT_LCD_ShowLaserValue(u8 Value)
{
	u16 AddressX=500,AddressY=302;
	u8 InfNum[4];
	u8 Num=1; 
	if(Value==1)
	{
		InfNum[0]=12;
//		TFT_LCD_ShowCharSS(AddressX,AddressY,12);
	}
	else
	{
		InfNum[0]=13;
	}
	TFT_LCD_Show_Inf3(AddressX,AddressY,InfNum,Num);
}
void TFT_LCD_ShowModeValue(u8 Value)
{
	u8 i;
	u16 Num;
	u8 InfNum[8];
	u16 AddressX=476,AddressY=356;
	Num=Value*200/51;
	InfNum[0]=12;
	if(Value==1)
	{
		InfNum[1]=2;
	}
	else
	{
		InfNum[1]=1;
	}
	TFT_LCD_Show_Inf2(AddressX,AddressY,InfNum,2);
}
void TFT_LCD_ShowWidthValue(u16 Value)
{
	u8 i;
	u16 Num;
	u8 InfNum[8];
	u16 AddressX=476,AddressY=410;
	Num=Value*200/51;
	InfNum[0]=12;
	if(Value<100&&Value!=0)
	{
		i=Value/10;
		InfNum[1]=i;
		i=Value%10;
		InfNum[2]=i;
		InfNum[3]=12;
	}
	
	if(Value>=100)
	{
		i=Value/100;
		InfNum[1]=i;
		i=(Value%100)/10;
		InfNum[2]=i;
		i=Value%10;
		InfNum[3]=i;
	}
	if(Value==0)
	{
		InfNum[1]=0;
		InfNum[2]=12;
		InfNum[3]=12;
	}
	TFT_LCD_Show_Inf2(AddressX,AddressY,InfNum,4);
}



