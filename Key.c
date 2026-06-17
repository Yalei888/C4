#include <REGX52.H>
#include "Delay.h"

unsigned char Key_KeyNum;

unsigned char Key(void)
{
	unsigned char Temp;
	Temp=Key_KeyNum;
	Key_KeyNum=0;
	return Temp;
}

unsigned char Key_GetState(void)
{
	unsigned char Keynum=0;
	
	if(P3_1==0)
	{
		Keynum=1;
	}
	if(P3_0==0)
	{
		Keynum=2;
	}
	if(P3_2==0)
	{
		Keynum=3;
	}
	if(P3_3==0)
	{
		Keynum=4;
	}
	return Keynum;
}

void Key_Loop()
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=Key_GetState();
	if(LastState==1 && NowState==0)
	{
		Key_KeyNum=1;
	}
	if(LastState==2 && NowState==0)
	{
		Key_KeyNum=2;
	}
	if(LastState==3 && NowState==0)
	{
		Key_KeyNum=3;
	}
	if(LastState==4 && NowState==0)
	{
		Key_KeyNum=4;
	}
}

unsigned char Key_IsPress(void)
{
	return (P3_1==0);
}

