#include <REGX52.H>

/**
  * @brief  定时器0初始化，1毫秒@11.0592Mhz
  * @param  无
  * @retval 无
  */
void Timer0_Init(void)		
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x66;		
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 1;		

	ET0=1;
	EA=1;
	PT0=0;
}

/*定时器中断函数模版
void Timer0_Routine() interrupt 1
{	
	static unsigned int T0count;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	T0count++;
	if(T0count>=1000)
	{
		T0count=0;
		P2_0=~P2_0;
	}
}
*/