#include "tlc5615.h"
#include <intrins.h>


//数模转换
void DA_Conver(u16 DAValue)
{

	u8 i;
	DAValue <<= 6;
	//片选DA芯片
	cs = 0;
	clk = 0;

	for(i = 0; i < 12; i++)
	{
		din = (bit)(DAValue & 0x8000);
		clk = 1;
		DAValue <<= 1;
		clk = 0;
	}

	//cs的上升沿和下降沿只有在clk为低端时候才有效
	cs = 1;		 	
	clk = 0;
}