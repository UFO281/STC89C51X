/* ------------------PWM调速使用例子--------for-STC51XX/52XX MCU--------
	Timer0();//调用定时器中断	
	while(1){
		speed=25;//占空比为 25%
	}
			
 ------------------PWM调速使用例子----------   */	
#ifndef _PWM_H_
#define _PWM_H_
#include<reg52.h>

sbit ENA=P2^1;//PWM接口
unsigned char counter;
unsigned char speed=0;//设置通电占空比



//定时器初始化的函数 T0定时器/计数器
void Timer0(){
//初值a=65536-(f晶振频率/12)*t 为时间 单位是微妙us 将a转化为16进制，分别存入TH0 ,TL0 高八位和低八位
//例如 a=FC18 然后TH0=0XFC; TL0=0X18;	

	TMOD|=0X01;//0000 0001 GATE=0 
	TR0=1;//启动定时器/计数器T0 
	TH0=0XFF;//定时器高8位 初值=65536-100 换成16进制
	TL0=0X9C;//定时器低8位 
	ET0=1;//打开定时器T0中断
	EA=1;//打开CPU总中断
}


void time0() interrupt 1
{//100us进来一次中断 执行此中断函数

	TH0=0XFF;//初值=65536-100
	TL0=0X9C; 
	counter++;
	counter%=100;// compare=compare%100; 等于0的时候从头再来
	if(counter<speed){
		ENA=1;//高电平导通
	}
	else{
		ENA=0;//低电平不导通
	}	
}



#endif