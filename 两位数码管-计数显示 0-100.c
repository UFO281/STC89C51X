#include"reg52.h"		
typedef unsigned int ui;	  
typedef unsigned char uc;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

unsigned int single_digit=0,timing=0,ten_digit=0;

void delaytime(unsigned int m)  // m代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=m;x>0;x--){
		for(y=114;y>0;y--);//延时1ms
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
	unsigned char show[100]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f, 0x80,0x40,0x5c,0x63,0x76};//显示0~9 10~14: .- 下口 上口
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
		delaytime(5);
		P0=0X00;
}



void main(){
	
	Timer0Init();
	while(1){
		
		display(1,ten_digit);
		display(2,single_digit);
		
	}
}

void Timer0() interrupt 1
{//1ms进来一次中断函数 

	TH0=0Xfc;	//给定时器赋初值，定时1ms
	TL0=0X18;
	timing++;//用与计算 几个ms 加一次 +1ms
	if(timing==500){//500ms 进来一次

		single_digit++;//每500ms  个位数+1

		if(single_digit==10){
			single_digit=0;//个位数加到10了变为零
			ten_digit++;//十位数 +1

			if(ten_digit==10){//十位数加到10了 也变为零
				ten_digit=0;//十位数从零开始
			}
		}
		timing=0;//+到500ms 就从头再来
	}
	
	
}




















/*	P0=s[i];
	LSA=0;LSB=0;LSC=0;//led1 
	LSA=1;LSB=0;LSC=0;//led2 
	LSA=0;LSB=1;LSC=0;//led3
	LSA=1;LSB=1;LSC=0;//led4
	LSA=0;LSB=0;LSC=1;//led5
	LSA=1;LSB=0;LSC=1;//led6
	LSA=0;LSB=1;LSC=1;//led7
	LSA=1;LSB=1;LSC=1;//led8
	*/



