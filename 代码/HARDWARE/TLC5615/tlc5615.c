#include "tlc5615.h"
#include <intrins.h>


//��ģת��
void DA_Conver(u16 DAValue)
{

	u8 i;
	DAValue <<= 6;
	//ƬѡDAоƬ
	cs = 0;
	clk = 0;

	for(i = 0; i < 12; i++)
	{
		din = (bit)(DAValue & 0x8000);
		clk = 1;
		DAValue <<= 1;
		clk = 0;
	}

	//cs�������غ��½���ֻ����clkΪ�Ͷ�ʱ�����Ч
	cs = 1;		 	
	clk = 0;
}