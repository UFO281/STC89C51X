/*-----------------应用例子---------------------
void main(){
	
	//speed数值增加电压增加 电机加速
	
	while(1){
		cshtm();//调用定时器中断
		
		lrmc(1);//左侧电机正反转函数
		ls(1000);//控制左侧侧电机转速
		
		rrmc(0);//右侧侧电机正反转函数
		rs(1000);//控制右侧侧电机转速
	}
	
}
-----------------应用例子---------------------*/

#ifndef _CARCON_H_
#define _CARCON_H_
#include<reg52.h> 
typedef unsigned int ui;   //对数据类型进行声明定义
typedef unsigned char uc;
uc counter;
uc speed=0;//设置通电占空比
sbit ENA=P1^0;//左电机PWM输入口
sbit ENB=P1^1;//右电机PWM输入口

sbit IN1=P1^2;// IN1 IN2 控制左侧电机 正转 或者反转
sbit IN2=P1^3;// IN1=0,IN2=1:电机正转 IN1=1,IN2=0：电机反转 

sbit IN3=P1^4;//IN3 IN4 控制右侧电机 正转 或者反转
sbit IN4=P1^5;//IN3=0,IN4=1:电机正传 IN3=1,IN4=0：电机反转 

sbit fttirsr=P3^6;//黑白循迹红外传感器 右眼
sbit fttirsl=P3^7;//黑白循迹红外传感器 左眼

sbit irsr=P3^5;//右红外传感器
sbit irsl=P3^4;//左红外传感器


void delay(ui m){//延时函数 m us 
	ui x;
	while(m--){
		for(x=114;x>0;x--);//执行1us
	}
}

void cshtm(){//定时器初始化的函数 T0定时器/计数器

/*初值a=65536-(f晶振频率/12)*t 为时间 单位是微妙us 将a转化为16进制，分别存入TH0 ,TL0 高八位和低八位
例如 a=FC18 然后TH0=0XFC; TL0=0X18;	
*/	TMOD|=0X01;//0000 0001 GATE=0 
	TR0=1;//启动定时器/计数器T0 
	TH0=0XFF;//定时器高8位 初值=65536-1000 换成16进制,定时 需换成us1ms/1us=1000
	TL0=0X9C;//定时器低8位 
	ET0=1;//打开定时器T0中断
	EA=1;//打开CPU总中断
}





void time0() interrupt 1
{//100us进来一次中断
	ui i;
	TH0=0XFF;//初值=65536-1000 换成16进制,定时 需换成us1ms/1us=1000
	TL0=0X9C; 
	//重新赋值
	counter++;
	counter%=100;
	if(counter<speed){
		ENA=1;
		ENB=1;
	}
	else{
		ENA=0;
		ENB=0;
	}
	
}


void lrmc(ui i){//左侧电机正反转函数
// lrmc(1),左侧电机正转 lrmc(0)左侧电机反转
    if(i==1){
        IN1=0;IN2=1;//电机正转 小车往后倒
    }
    if(i==0){
        IN1=1;IN2=0;//电机反转 小车往前走
    }
}

void rrmc(ui i){//右侧电机正反转函数
// rrmc(1),右侧电机正转 rrmc(0)右侧电机反转
    if(i==1){
        IN3=0;IN4=1;//电机正转 小车往后倒
    }
    if(i==0){
        IN3=1;IN4=0;//电机反转  小车往前走
    }
}

void rs(ui i){//控制右侧电机转速
    speed=i;
}

void ls(ui i){//控制左侧侧电机转速
    speed=i;
}

void Rredirs(){//避障右侧红外传感器函数

}
void Lredirs(){//避障左侧红外传感器函数
    
}

void xRredirs(){//循迹右侧红外传感器函数

}
void xLredirs(){//循迹左侧红外传感器函数
    
}
#endif