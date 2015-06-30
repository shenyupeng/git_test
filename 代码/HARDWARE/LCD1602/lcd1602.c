#include "lcd1602.h"
#include "timer.h"



/*
*1602初始化
*输入参数：无
*输出参数：无
*/
void LCD_Init(void)
{
	LCD_Data = 0;


	
	//三次显示模式设置，不检测忙信号
	LCD_WriteCommand(0x38,0);
	Delayms(5);
	LCD_WriteCommand(0x38,0);
	Delayms(5);
	LCD_WriteCommand(0x38,0);
	Delayms(5);

	//显示模式设置，开始要求每次检测忙信号
	LCD_WriteCommand(0x38,1);
	//关闭显示
	LCD_WriteCommand(0x08,1);
	//显示清屏
	LCD_WriteCommand(0x01,1);
	//显示光标移动设置
	LCD_WriteCommand(0x06,1);
	//显示开及光标设置
	LCD_WriteCommand(0x0C,1);
}

/*
*1602写指令
*输入参数：要写入的指令
*输出参数：无
*/
void LCD_WriteCommand(u8 WCLCD,BuysC)
{
	if(BuysC)
	{
		//根据需要检测忙
		LCD_ReadStatus();
	}
	LCD_Data = WCLCD;
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
}

u8 LCD_ReadData(void)
{
	LCD_RS = 1;
	LCD_RW = 1;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
	return(LCD_Data);
}



/*
*1602读状态
×输入参数：无
*输出参数：1602返回的状态
*/
u8 LCD_ReadStatus(void)
{
	LCD_Data = 0xFF;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;

	//检测忙信号
	while(LCD_Data & 0x80)
	{}
	return (LCD_Data);
}


/*
*1602按指定位置显示一个字符
*输入参数：X坐标 Y坐标 要显示的字符
×输出参数：无
*/
void DisplayOneChar(u8 X, u8 Y, u8 DData)
{
	//限制X不能大于15，Y不能大于1
	Y &= 0x01;
	X &= 0x0F;

	//当要显示第二行时地址码+0x40；
	if(Y)
	{
		X |= 0x40;
	}
	//算出指令码
	X |= 0x80;

	//这里不检测忙信号，发送地址码
	LCD_WriteCommand(X,0);
	LCD_WriteData(DData);
}


/*
*1602写数据
*输入参数：要写入的数据
*输出参数：无
*/
void LCD_WriteData(u8 WDLCD)
{
	//检测忙
	LCD_ReadStatus();
	LCD_Data = WDLCD;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
}

/*
*1602指定位置显示一串字符
*输入参数：X坐标 Y坐标 要显示字符串的首地址
*/
void DisplayListChar(u8 X, u8 Y, u8 *DData)
{
	u8 ListLength = 0;
	//限制X不能大于15，Y不能大于1
	Y &= 0x01;
	X &= 0x0F;

	while(0x20 <= DData[ListLength])
	{
		if(0x0F >= X)
		{
			//显示单个字符
			DisplayOneChar(X,Y,DData[ListLength]);
			ListLength++;
			X++;
		}
	}
}

/*
*1602显示一串数字
*
*/
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
	number /= 10;
	for (i = count; i>0; i--)
	{
		if(i==count - 2)
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


/*
*显示清屏
*/
void LCD_Clear(void)
{
	//显示清屏
	LCD_WriteCommand(0x01,1);
	//显示光标移动设置
	LCD_WriteCommand(0x06,1);
	//显示开及光标设置
	LCD_WriteCommand(0x0C,1);
}