#include "head.h"

#ifndef __TIMER_H__
#define __TIMER_H__

sfr T2MOD = 0xC9;

void TimerInit(void);
void Delayms(u16 ms);

extern u16 system_time;

#endif
