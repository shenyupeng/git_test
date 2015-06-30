#include "head.h"

sbit cs = P1^1;		//片选
sbit clk = P1^2;	//时钟
sbit din = P1^3;	//数据入口

#ifndef __TLC5615_H__
#define __TLC5615_H__

void DA_Conver(u16 DAValue);

#endif