#include <REGX52.H>
#include "Timer0.h"
#include "LCD1602.h"
#include "MatrixKey.h"
#include "Key.h"
#include "Delay.h"
#include "Buzzer.h"

unsigned char Password[7];
unsigned char Correct[]={7,3,5,5,6,0,8};
unsigned char Time1,i,MatrixKeyNum,KeyNum,flag,count,Sec=40;
unsigned char StartFlag=0;
unsigned char DefuseFlag=0;
unsigned char DefuseProgress=0;
unsigned int DefuseTime;
unsigned char DefuseDone=0;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"C4 Planting...");
	LCD_ShowString(2,1,"*******");
	while(1)
	{
		MatrixKeyNum=MatrixKey();
		KeyNum=Key();
		if(MatrixKeyNum)
		{
			Buzzer_Time(50);
			if(MatrixKeyNum<=10 && count<7)
			{
				if(MatrixKeyNum<=9)
				{
					Password[count]=MatrixKeyNum;
				}
				if(MatrixKeyNum==10)
				{
					Password[count]=0;
				}
				LCD_ShowNum(2,count+1,Password[count],1);
				count++;
			}
			if(MatrixKeyNum==11)
			{
				for(i=0;i<7;i++)
				{
					if(Password[i]==Correct[i])
					{
						flag++;
					}
				}
				if(flag==7)
				{
					LCD_ShowString(1,1,"C4 Start!     ");
					LCD_ShowString(2,1,"       ");
					Timer0_Init();
					StartFlag=1;
				}
				else
				{
					Delay(100);
					LCD_ShowString(2,1,"ERRO!  ");
					Buzzer_Time(1000);
					LCD_ShowString(2,1,"*******");
					count=0;
					flag=0;
					for(i=0;i<7;i++)
					{
						Password[i]=0;
					}
				}
			}
			if(MatrixKeyNum==12)
			{
				count=0;
				flag=0;
				for(i=0;i<7;i++)
				{
					Password[i]=0;
				}
				LCD_ShowString(2,1,"*******");
			}
		}
		if(StartFlag)
		{
			if(Sec>0 && DefuseFlag==0)
			{
				LCD_ShowNum(2,1,Sec,2);
			}
			if(Sec==0)
			{
				TR0=0;
				LCD_ShowString(1,1,"C4 Boom!      ");
				LCD_ShowString(2,1,"T Win!");
				Buzzer_Time(2000);
				while(1);
			}
		}
		if(StartFlag && !DefuseFlag && Sec>0)
		{
			if(Key_IsPress())
			{
				DefuseFlag=1;
				DefuseProgress=0;
				DefuseTime=0;
				LCD_ShowString(1,1,"C4 Defusing...");
				LCD_ShowString(2,1,"                ");
			}
		}
		if(DefuseFlag)
		{
			if(DefuseProgress==1){LCD_ShowString(2,1,"****");}
			if(DefuseProgress==2){LCD_ShowString(2,1,"********");}
			if(DefuseProgress==3){LCD_ShowString(2,1,"************");}
			if(DefuseProgress==4)
			{
				DefuseDone=1;
				TR0=0;
				LCD_ShowString(2,1,"****************");
				LCD_ShowString(2,1,"                ");
				Delay(100);
				LCD_ShowString(1,1,"C4 Defused!     ");
				LCD_ShowString(2,1,"CT Win!         ");
				while(1);
			}
			if(!Key_IsPress() && DefuseDone==0)
			{
				DefuseFlag=0;
				DefuseProgress=0;
				DefuseTime=0;
				LCD_ShowString(1,1,"C4 Start!         ");
				LCD_ShowString(2,1,"                ");
				LCD_ShowNum(2,1,Sec,2);
			}
		}
	}
	
}


void Timer0_Routine() interrupt 1
{	
	static unsigned int T0count1,T0count2,T0count3;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	T0count1++;
	if(T0count1>=1000)
	{
		T0count1=0;
		Sec--;
	}
	T0count2++;
	if(T0count2>=1000)
	{
		T0count2=0;
		if(Sec>=10)
		{
			Buzzer_Time(100);
		}
	}
	T0count3++;
	if(T0count3>=250)
	{
		T0count3=0;
		if(Sec>0 && Sec<10)
		{
			Buzzer_Time(50);
		}
	}
	if(DefuseFlag)
	{
		DefuseTime++;
		if(DefuseTime>1000)
		{
			DefuseTime=0;
			DefuseProgress++;
			if(DefuseProgress>=4)
			{
				DefuseProgress=0;
				DefuseProgress=4;
			}
		}
	}
}