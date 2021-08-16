#include"reg52.h"		
typedef unsigned int ui;	  
typedef unsigned char uc;
//---------138译码器的三个IO口-----------
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
//---------138译码器的三个IO口-----------
sbit beep=P1^5;//蜂鸣器

unsigned int hours=13,minutes=30,seconds=0,k=0;

void delaytime(unsigned int m)  // m代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=m;x>0;x--){
	    for(y=110;y>0;y--);//延时1ms
	}
        
}


void Timer0Init()
{
	TMOD|=0X01;//选择为定时器0模式，工作方式1，仅用TR0打开启动。
	TH0=0Xfc;//给定时器赋初值，定时1ms
	TL0=0X18;	
	ET0=1;//打开定时器0中断允许
	EA=1;//打开总中断
	TR0=1;//打开定时器			
}


void display(unsigned int x,unsigned int y){
//x 代表哪个数码管  y表示显示的数字
	unsigned char show[100]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f, 
	0x80,0x40,0x5c,0x63,0x76,0xdb};//显示0~9 10~15: .- 下口 上口 H 2.
		switch(x){//选择哪个数码管
			case 1:LSA=1;LSB=1;LSC=1;break;//led1
			case 2:LSA=0;LSB=1;LSC=1;break;//led2
			case 3:LSA=1;LSB=0;LSC=1;break;//led3
			case 4:LSA=0;LSB=0;LSC=1;break;//led4
			case 5:LSA=1;LSB=1;LSC=0;break;//led5
			case 6:LSA=0;LSB=1;LSC=0;break;//led6
			case 7:LSA=1;LSB=0;LSC=0;break;//led7 
			case 8:LSA=0;LSB=0;LSC=0;break;//led8
		};
		P0=show[y];//选择显示的数字
		delaytime(1);
		P0=0X00;
}



void main(){
	
	Timer0Init();
	while(1){
		display(1,hours/10);
		display(2,hours%10);	
		display(3,11);

		display(4,minutes/10);
		display(5,minutes%10);
		display(6,11);

		display(7,seconds/10);
		display(8,seconds%10);
	}
}

void Timer0() interrupt 1
{//1ms进来一次中断函数 

	TH0=0Xfc;	//给定时器赋初值，定时1ms
	TL0=0X18;
	k++;
	if(k==1000){//一秒钟执行一次
		k=0;
		seconds++; 
		if(seconds==60){//秒
			beep=0;
			beep=1;
			seconds=0;
			minutes++;
			if(minutes==60){//分钟
				minutes=0;
				hours++;
				if(hours==24){//小时
					hours=0;
				}
			}
		}
	}
	
}





/* 138译码器IO口设置，选择点亮哪个数码管
	P0=s[i];
	LSA=0;LSB=0;LSC=0;//led1 
	LSA=1;LSB=0;LSC=0;//led2 
	LSA=0;LSB=1;LSC=0;//led3
	LSA=1;LSB=1;LSC=0;//led4
	LSA=0;LSB=0;LSC=1;//led5
	LSA=1;LSB=0;LSC=1;//led6
	LSA=0;LSB=1;LSC=1;//led7
	LSA=1;LSB=1;LSC=1;//led8
*/



