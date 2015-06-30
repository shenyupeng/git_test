#include "timer.h"

//系统时间
u16 system_time;

void TimerInit(void)
{
	//总中断打开
	EA = 1;
	//有关定时器2的设置
	T2CON = 0;
  	T2MOD = 0;
 	ET2 = 1;
	TR2 = 1;  //启动
  	RCAP2H = (0xFFFF - 1000) >> 8;
  	RCAP2L = (0xFFFF - 1000) & 0xFF;
	
	//定时器状态控制变量初始化
	system_time = 0;
}

//定时器2的中断函数

void timer2(void) interrupt 5
{
	TF2 = 0;  //定时器2必须由软件对溢出标志位清零
	system_time++;
}

void Delayms(u16 ms)
{
	u16 tmp_delay;
	tmp_delay = system_time;
	for(;system_time-tmp_delay<ms;)
	{}
}

