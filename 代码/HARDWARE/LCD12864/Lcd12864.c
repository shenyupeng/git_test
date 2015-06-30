#include "Lcd12864.h"
#include "timer.h"





//LCD��ʼ��
void LCDInit(void)
{
	WriteCommandLCD(0x30,1);		//��ʾģʽ���ã���ʼҪ��ÿ�μ��æ�ź�
	WriteCommandLCD(0x01,1);		//��ʾ����
	WriteCommandLCD(0x06,1);		//��ʾ����ƶ�����
	WriteCommandLCD(0x0C,1);		//��ʾ�����������
	
}


//��״̬
u8 ReadStatusLCD(void)
{
	LCD_Data = 0xFF;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_E = 1;
	while(LCD_Data & Busy)	//���æ�ź�
	;
	return LCD_Data;
}

//дָ��
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


//д����
void WriteDataLCD(u8 WDLCD)
{
	ReadStatusLCD();		//���æ
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_Data = WDLCD;
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 1;
	LCD_E = 0;
}


//������
u8 ReadDataLCD(void)
{
	LCD_RS = 1;
	LCD_RW = 1;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
	return (LCD_Data);
}


//����
void LCDClear(void)
{
	WriteCommandLCD(0x01,1);		//��ʾ����
	WriteCommandLCD(0x34,1);		//��ʾ����ƶ�����
	WriteCommandLCD(0x30,1);		//��ʾ�����������
}


//��Ļ����
void LCDFlash(void)
{
	WriteCommandLCD(0x08,1);		//��ʾ����
	Delayms(400);
	WriteCommandLCD(0x0c,1);  		//��ʾ�����������
	Delayms(400);
	WriteCommandLCD(0x08,1);		//��ʾ����
	Delayms(400);
	WriteCommandLCD(0x0c,1);  		//��ʾ�����������
	Delayms(400);
	WriteCommandLCD(0x08,1);		//��ʾ����
	Delayms(400);

}


//��ʾһ���ַ�
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
	X &= 0x0F;		//����X���ܴ���16��Y���ܴ���1
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

	WriteCommandLCD(X,0);		//���ﲻ���æ�źţ����͵�ַ��
	WriteDataLCD(DData);
}

//��ʾһ���ַ�
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
	X &= 0x0F;		//����X���ܴ���16��Y��1-4֮��
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
	WriteCommandLCD(X2,1);		//���͵�ַ��
	while(DData[ListLength]>=0x20)		//�������ִ�β���˳�
	{
		if(X <= 0x0F)	//X����ӦС��0x0F
		{
			WriteDataLCD(DData[ListLength]);
			ListLength++;
			X++;
			Delayms(5);
		}
	}
}




//��ʾһ������

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


//��ʾ��������
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
	for(i = 0; i < 9; i+=8)		//���������ϰ������°���
	{
		for(x=0; x<32; x++)
		{
			WriteCommandLCD(0x34,1);
			WriteCommandLCD(0x80+x,1);		//�е�ַ
			WriteCommandLCD(0x80+i,1);		//�е�ַ���°���
			for(y=0;y<16;y++)
			{
				WriteDataLCD(DData[tmp+y]);	//��ȡ����д��LCD
			}
			tmp +=16;
		}
	}
	WriteCommandLCD(0x36,1);		//���书���趨
	WriteCommandLCD(0x30,1);
}