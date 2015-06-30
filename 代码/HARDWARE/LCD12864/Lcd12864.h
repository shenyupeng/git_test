#include "head.h"


/**
*宽：128 == 72mm
×高：64  == 40mm
*/
//LCD相关端口定义

sbit LCD_RS=P0^7;
sbit LCD_RW=P0^6;
sbit LCD_E=P0^5;
sbit PSB=P0^4;	 		//PSB脚为12864-12系列的串、并通讯功能切换


#define LCD_Data P2		//LCD数据口
#define Busy 0x80


#ifndef _LCD12864_
#define _LCD12864_



//函数声明
void LCDInit(void);		//LCD初始化
void WriteCommandLCD(u8 WCLCD,BuysC);	//写指令
u8 ReadStatusLCD(void);			//读状态即检测忙
void WriteDataLCD(u8 WDLCD);		//写数据
u8 ReadDataLCD(void);			//读数据
void LCDClear(void);		   		//清屏
void LCDFlash(void);				//屏幕闪动
void DisplayOneChar(u8 X,u8 Y,u8 DData);	//显示一个字符
void DisplayListChar(u8 X, u8 Y, u8 *DData);	//显示一串字符
void DisplayImage(u8 code *DData);	//显示图形
void DisplayNumber(u8 X, u8 Y, u32 number,u8 count);	//显示一串数字
void DisplayFloatNumber(u8 X, u8 Y, u32 number,u8 count); //显示为浮点数字

#endif