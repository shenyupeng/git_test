#include "algo.h"
#include "tlc5615.h"
#include "timer.h"


u16 mid[] = {(MIN+MAX)>>1,MIN,MAX};

void dich()
{
	u16 temp = 0;
	u16 num = 9;
	mid[0] = (MIN+MAX)>>1;
	mid[1] = MIN;
	mid[2] = MAX;
	while(num--)
	{
		if(!value)
		{
			temp = mid[0];
			mid[0] = (mid[0]+mid[1])>>1;
			mid[2] = temp;
		}
		else
		{
			temp = mid[0];
			mid[0] = (mid[0]+mid[2])>>1;
			mid[1] = temp;
		}
		DA_Conver(mid[0]);
	}
}
