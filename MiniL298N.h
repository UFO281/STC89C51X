#ifndef _MINIL298N_H_ //头文件开始
#define _MINIL298N_H_
#include<reg52.h>  
sbit IN1=P1^0;// IN1 IN2 控制左侧电机 正转 或者反转 待机：INT1=INT2=0; 刹车：INT1=INT2=0;
sbit IN2=P1^1;// 电机正转 : (PWM端口)IN1=1,IN2=0。  电机反转：IN1=0, (PWM端口)IN2=1。 

sbit IN3=P1^2;// IN3 IN4 控制右侧电机 正转 或者反转 停止：INT3=INT4=0; 刹车：INT3=INT4=0;
sbit IN4=P1^3;// (PWM端口)IN3=1,IN4=0:电机正转。IN1=3, (PWM端口)IN4=1：电机反转。

unsigned char counter;
unsigned char speed=0;//设置通电占空比


void delaytime(unsigned int m){//延时 m us 
	unsigned int x;
	while(m--){
		for(x=114;x>0;x--);//执行1us
	}
}


void cshtm(){//定时器初始化的函数 T0定时器/计数器

/*初值a=65536-(f晶振频率/12)*t 为时间 单位是微妙us 将a转化为16进制，分别存入TH0 ,TL0 高八位和低八位
例如 a=FC18 然后TH0=0XFC; TL0=0X18;*/
	TMOD|=0X01;//0000 0001 GATE=0 
	TR0=1;//启动定时器/计数器T0 
	TH0=0XFF;//定时器高8位 初值=65536-1000 换成16进制,定时 需换成us1ms/1us=1000
	TL0=0X9C;//定时器低8位 
	ET0=1;//打开定时器T0中断
	EA=1;//打开CPU总中断
}


/*-----------MiniL298N电机驱动模块使用例子-------------
void main(){

	cshtm();//调用定时器中断	
	IN2=0;//电机正转 在中断函数里 INT1=1了
	while(1){
		speed=30;//占空比为3%
	}
		
}
*/

void time0() interrupt 1
{//100us进来一次中断 执行此中断函数
	
	TH0=0XFF;//初值=65536-100 
	TL0=0X9C; 
	counter++;
	counter%=100;// compare=compare%100; 等于0的时候从头再来
	if(counter<speed){
		IN1=1;
	}
	else{
		IN1=0;
	}
	
}



#endif //头文件结束





