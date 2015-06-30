#include "Lcd12864.h"
#include "timer.h"





//LCD初始化
void LCDInit(void)
{
	WriteCommandLCD(0x30,1);		//显示模式设置，开始要求每次检测忙信号
	WriteCommandLCD(0x01,1);		//显示清屏
	WriteCommandLCD(0x06,1);		//显示光标移动设置
	WriteCommandLCD(0x0C,1);		//显示开及光标设置
	
}


//读状态
u8 ReadStatusLCD(void)
{
	LCD_Data = 0xFF;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_E = 1;
	while(LCD_Data & Busy)	//检测忙信号
	;
	return LCD_Data;
}

//写指令
void WriteCommandLCD(u8 WCLCD,BuysC)
{
	if(BuysC)
	ReadStatusLCD();
	  LCD_RS = 0;
	  LCD_RW = 0;
	  LCD_Data = WCLCD;
	  LCD_E = 1;
	  LCD_E = 1;
	  LCD_E = 1;
	  LCD_E = 0;
}


//写数据
void WriteDataLCD(u8 WDLCD)
{
	ReadStatusLCD();		//检测忙
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_Data = WDLCD;
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 0;
}


//读数据
u8 ReadDataLCD(void)
{
	LCD_RS = 1;
	LCD_RW = 1;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
	return (LCD_Data);
}


//清屏
void LCDClear(void)
{
	WriteCommandLCD(0x01,1);		//显示清屏
	WriteCommandLCD(0x34,1);		//显示光标移动设置
	WriteCommandLCD(0x30,1);		//显示开及光标设置
}


//屏幕闪动
void LCDFlash(void)
{
	WriteCommandLCD(0x08,1);		//显示清屏
	Delayms(400);
	WriteCommandLCD(0x0c,1);  		//显示开及光标设置
	Delayms(400);
	WriteCommandLCD(0x08,1);		//显示清屏
	Delayms(400);
	WriteCommandLCD(0x0c,1);  		//显示开及光标设置
	Delayms(400);
	WriteCommandLCD(0x08,1);		//显示清屏
	Delayms(400);

}


//显示一个字符
void DisplayOneChar(u8 X,u8 Y,u8 DData)
{
	if(Y<1)
	{
		Y = 1;
	}
	if(Y>4)
	{
		Y = 4;
	}
	X &= 0x0F;		//限制X不能大于16，Y不能大于1
	switch(Y)
	{
		case 1:
			X |= 0x80;
			break;
		case 2:
			X |=0x90;
			break;
		case 3:
			X |=0x88;
			break;
		case 4:
			X |=0x98;
			break;
	}

	WriteCommandLCD(X,0);		//这里不检测忙信号，发送地址码
	WriteDataLCD(DData);
}

//显示一串字符
void DisplayListChar(u8 X, u8 Y, u8 *DData)
{
	u8 ListLength,X2;
	ListLength = 0;
	X2 = X;
	if(Y<1)
	{
		Y = 1;
	}
	if(Y>4)
	{
		Y=4;
	}
	X &= 0x0F;		//限制X不能大于16，Y在1-4之内
	switch(Y)
	{
		case 1:
			X2 |=0x80;
			break;
		case 2:
			X2 |=0x90;
			break;
		case 3:
			X2 |=0x88;
			break;
		case 4:
			X2 |=0x98;
			break;
	}
	WriteCommandLCD(X2,1);		//发送地址码
	while(DData[ListLength]>=0x20)		//若到达字串尾则退出
	{
		if(X <= 0x0F)	//X坐标应小于0x0F
		{
			WriteDataLCD(DData[ListLength]);
			ListLength++;
			X++;
			Delayms(5);
		}
	}
}




//显示一串数字

void DisplayNumber(u8 X, u8 Y, u32 number,u8 count)
{
	u8 array[11];
	u8 i;
	array[count] = 0;
	for (i = count; i>0; i--)
	{
		array[i-1] = number % 10 + '0';
		number /= 10; 
	}

	for (i = 0; i < count - 1; i++)
	{
		if(array[i] == '0')
		{
			array[i] = ' ';
		}
		else
		{
			break;
		}
	}

	DisplayListChar(X,Y,array);
}


//显示浮点数字
void DisplayFloatNumber(u8 X, u8 Y, u32 number,u8 count)
{
	u8 array[17];
	u8 i;
	array[count] = 0;
	for (i = count; i>0; i--)
	{
		if(i==count - 3)
		{
			array[i-1] = '.';
			i--;
		}
		array[i-1] = number % 10 + '0';
		number /= 10; 
	}

	for (i = 0; i < count - 1; i++)
	{
		if(array[i] == '0')
		{
			array[i] = ' ';
		}
		else
		{
			break;
		}
	}
	DisplayListChar(X,Y,array);
}


void DisplayImage(u8 code *DData)
{
	u8 x, y, i;
	u16 tmp = 0;
	for(i = 0; i < 9; i+=8)		//分两屏，上半屏和下半屏
	{
		for(x=0; x<32; x++)
		{
			WriteCommandLCD(0x34,1);
			WriteCommandLCD(0x80+x,1);		//列地址
			WriteCommandLCD(0x80+i,1);		//行地址，下半屏
			for(y=0;y<16;y++)
			{
				WriteDataLCD(DData[tmp+y]);	//读取数据写入LCD
			}
			tmp +=16;
		}
	}
	WriteCommandLCD(0x36,1);		//扩充功能设定
	WriteCommandLCD(0x30,1);
}