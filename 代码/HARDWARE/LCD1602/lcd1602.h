#include "head.h"


//引脚定义
//数据口
#define LCD_Data P2


sbit LCD_RS = P0^7;
sbit LCD_RW = P0^6;
sbit LCD_E = P0^5;

#ifndef _LCD1602_H_
#define _LCD1602_H_


//函数声明
void LCD_WriteData(u8 WDLCD);
void LCD_WriteCommand(u8 WCLCD,BuysC);
u8 LCD_ReadData(void);
u8 LCD_ReadStatus(void);
void LCD_Init(void);
void DisplayOneChar(u8 X, u8 Y, u8 DData);
void DisplayListChar(u8 X, u8 Y, u8 *DData);
void DisplayNumber(u8 X, u8 Y, u32 number,u8 count);
void LCD_Clear(void);
void DisplayFloatNumber(u8 X, u8 Y, u32 number,u8 count); //显示为浮点数字
#endif