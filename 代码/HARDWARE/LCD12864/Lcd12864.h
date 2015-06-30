#include "head.h"


/**
*��128 == 72mm
���ߣ�64  == 40mm
*/
//LCD��ض˿ڶ���

sbit LCD_RS=P0^7;
sbit LCD_RW=P0^6;
sbit LCD_E=P0^5;
sbit PSB=P0^4;	 		//PSB��Ϊ12864-12ϵ�еĴ�����ͨѶ�����л�


#define LCD_Data P2		//LCD���ݿ�
#define Busy 0x80


#ifndef _LCD12864_
#define _LCD12864_



//��������
void LCDInit(void);		//LCD��ʼ��
void WriteCommandLCD(u8 WCLCD,BuysC);	//дָ��
u8 ReadStatusLCD(void);			//��״̬�����æ
void WriteDataLCD(u8 WDLCD);		//д����
u8 ReadDataLCD(void);			//������
void LCDClear(void);		   		//����
void LCDFlash(void);				//��Ļ����
void DisplayOneChar(u8 X,u8 Y,u8 DData);	//��ʾһ���ַ�
void DisplayListChar(u8 X, u8 Y, u8 *DData);	//��ʾһ���ַ�
void DisplayImage(u8 code *DData);	//��ʾͼ��
void DisplayNumber(u8 X, u8 Y, u32 number,u8 count);	//��ʾһ������
void DisplayFloatNumber(u8 X, u8 Y, u32 number,u8 count); //��ʾΪ��������

#endif