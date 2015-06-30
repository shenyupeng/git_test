#include "lcd1602.h"
#include "timer.h"



/*
*1602��ʼ��
*�����������
*�����������
*/
void LCD_Init(void)
{
	LCD_Data = 0;


	
	//������ʾģʽ���ã������æ�ź�
	LCD_WriteCommand(0x38,0);
	Delayms(5);
	LCD_WriteCommand(0x38,0);
	Delayms(5);
	LCD_WriteCommand(0x38,0);
	Delayms(5);

	//��ʾģʽ���ã���ʼҪ��ÿ�μ��æ�ź�
	LCD_WriteCommand(0x38,1);
	//�ر���ʾ
	LCD_WriteCommand(0x08,1);
	//��ʾ����
	LCD_WriteCommand(0x01,1);
	//��ʾ����ƶ�����
	LCD_WriteCommand(0x06,1);
	//��ʾ�����������
	LCD_WriteCommand(0x0C,1);
}

/*
*1602дָ��
*���������Ҫд���ָ��
*�����������
*/
void LCD_WriteCommand(u8 WCLCD,BuysC)
{
	if(BuysC)
	{
		//������Ҫ���æ
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
*1602��״̬
�������������
*���������1602���ص�״̬
*/
u8 LCD_ReadStatus(void)
{
	LCD_Data = 0xFF;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;

	//���æ�ź�
	while(LCD_Data & 0x80)
	{}
	return (LCD_Data);
}


/*
*1602��ָ��λ����ʾһ���ַ�
*���������X���� Y���� Ҫ��ʾ���ַ�
�������������
*/
void DisplayOneChar(u8 X, u8 Y, u8 DData)
{
	//����X���ܴ���15��Y���ܴ���1
	Y &= 0x01;
	X &= 0x0F;

	//��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40��
	if(Y)
	{
		X |= 0x40;
	}
	//���ָ����
	X |= 0x80;

	//���ﲻ���æ�źţ����͵�ַ��
	LCD_WriteCommand(X,0);
	LCD_WriteData(DData);
}


/*
*1602д����
*���������Ҫд�������
*�����������
*/
void LCD_WriteData(u8 WDLCD)
{
	//���æ
	LCD_ReadStatus();
	LCD_Data = WDLCD;
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_E = 0;
	LCD_E = 0;
	LCD_E = 1;
}

/*
*1602ָ��λ����ʾһ���ַ�
*���������X���� Y���� Ҫ��ʾ�ַ������׵�ַ
*/
void DisplayListChar(u8 X, u8 Y, u8 *DData)
{
	u8 ListLength = 0;
	//����X���ܴ���15��Y���ܴ���1
	Y &= 0x01;
	X &= 0x0F;

	while(0x20 <= DData[ListLength])
	{
		if(0x0F >= X)
		{
			//��ʾ�����ַ�
			DisplayOneChar(X,Y,DData[ListLength]);
			ListLength++;
			X++;
		}
	}
}

/*
*1602��ʾһ������
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


//��ʾ��������
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
*��ʾ����
*/
void LCD_Clear(void)
{
	//��ʾ����
	LCD_WriteCommand(0x01,1);
	//��ʾ����ƶ�����
	LCD_WriteCommand(0x06,1);
	//��ʾ�����������
	LCD_WriteCommand(0x0C,1);
}