#include "head.h"

sbit cs = P1^1;		//Ƭѡ
sbit clk = P1^2;	//ʱ��
sbit din = P1^3;	//�������

#ifndef __TLC5615_H__
#define __TLC5615_H__

void DA_Conver(u16 DAValue);

#endif