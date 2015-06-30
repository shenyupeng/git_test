#include "man.h"
#include "timer.h"
#include "lcd12864.h"
#include "display.h"
#include "tlc5615.h"
#include "algo.h"
//#include "lcd1602.h"


sbit out = P1^4;

//������
void
main(void)
{
	//��ʼ����ش���
	led = 0;
	MnInit();
	while(1)
	{
		dich();
		if(mid[0] < 515 && mid[0] > 505)
		{
			continue;
		}
		if(mid[0]==1)
		{
			mid[0] = 0;
		}
		DisplayListChar(0,1,"��ǰ��ѹֵΪ��");
		DisplayFloatNumber(0, 2, 4.888*mid[0],13);
		DisplayOneChar(7,2,'V');
		Delayms(1);
		DisplayNumber(0,4,mid[0],8);
		Delayms(1000);	
	}
}


//����ʼ������
void MnInit(void)
{
	TimerInit();
	LCDInit();
//	LCD_Init();
	DisplayInit();
	led = 1;
}
