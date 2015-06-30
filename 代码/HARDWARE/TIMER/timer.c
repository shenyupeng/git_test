#include "timer.h"

//ϵͳʱ��
u16 system_time;

void TimerInit(void)
{
	//���жϴ�
	EA = 1;
	//�йض�ʱ��2������
	T2CON = 0;
  	T2MOD = 0;
 	ET2 = 1;
	TR2 = 1;  //����
  	RCAP2H = (0xFFFF - 1000) >> 8;
  	RCAP2L = (0xFFFF - 1000) & 0xFF;
	
	//��ʱ��״̬���Ʊ�����ʼ��
	system_time = 0;
}

//��ʱ��2���жϺ���

void timer2(void) interrupt 5
{
	TF2 = 0;  //��ʱ��2����������������־λ����
	system_time++;
}

void Delayms(u16 ms)
{
	u16 tmp_delay;
	tmp_delay = system_time;
	for(;system_time-tmp_delay<ms;)
	{}
}

