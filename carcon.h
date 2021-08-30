/*-----------------应用例子---------往下------------
void main(){
	
	cshtm();//调用定时器中断
	while(1){
		lrmc(0);//左轮子往前走
		rrmc(0);//右轮子往前走
		rs(100);//控制右侧电机转速
		ls(100);//控制左侧电机转速

		if(irsr==0&&irsl==0){//正前方遇到障碍物
			//irsr:右红外传感器
			//irsl:左红外传感器
			while(1&&irsr==0&&irsl==0){
				lrmc(1);//左轮子往后走
				rrmc(1);//右轮子往后走
				rs(100);//控制右侧电机转速
				ls(100);//控制左侧电机转速
			}
		}
	
		if(irsr==0&&irsl==1){//右侧遇到障碍物
			while(1&&irsr==0&&irsl==1){
				lrmc(1);//左轮子往后走
				rrmc(1);//右轮子往后走
				rs(100);//控制右侧电机转速
				ls(100);//控制左侧电机转速
				delay(300);//300ms
			
				lrmc(0);//左轮子往前走
				rrmc(0);//右轮子往前走
				rs(100);//控制右侧电机转速
				ls(10);//控制左侧电机转速
				delay(500);//100ms
			}	
		}
	
		if(irsr==1&&irsl==0){//左侧侧遇到障碍物
			while(1&&irsr==1&&irsl==0){
				lrmc(1);//左轮子往后走
				rrmc(1);//右轮子往后走
				rs(100);//控制右侧电机转速
				ls(100);//控制左侧电机转速
				delay(300);//300ms

				lrmc(0);//左轮子往前走
				rrmc(0);//右轮子往前走
				rs(10);//控制右侧电机转速
				ls(100);//控制左侧电机转速
				delay(500);//1000ms
			}	
		}
	}
}

-----------------应用例子---------往下-----------*/

#ifndef _CARCON_H_
#define _CARCON_H_
#include<reg52.h> 
typedef unsigned int ui;   //对数据类型进行声明定义
typedef unsigned char uc;

uc counter;
uc speed=0;//设置左侧电机通电占空比
uc sped=0;//设置右侧通电占空比

sbit ENA=P1^5;//左电机PWM输入口
sbit ENB=P1^6;//右电机PWM输入口

sbit IN1=P1^0;// IN1 IN2 控制左侧电机 正转 或者反转
sbit IN2=P1^1;// IN1=0,IN2=1:电机正转 IN1=1,IN2=0：电机反转 

sbit IN3=P1^2;//IN3 IN4 控制右侧电机 正转 或者反转
sbit IN4=P1^3;//IN3=0,IN4=1:电机正传 IN3=1,IN4=0：电机反转 

sbit fttirsr=P3^6;//黑白循迹红外传感器 右眼
sbit fttirsl=P3^7;//黑白循迹红外传感器 左眼

sbit irsr=P3^5;//右红外传感器
sbit irsl=P3^4;//左红外传感器

//延时 m us 
void delay(ui m){
	ui x;
	while(m--){
		for(x=114;x>0;x--);//执行1us
	}
}


//T0定时器/计数器初始化的函数 
void cshtm(){

/*初值a=65536-(f晶振频率/12)*t 为时间 单位是微妙us 将a转化为16进制，分别存入TH0 ,TL0 高八位和低八位
例如 a=FC18 然后TH0=0XFC; TL0=0X18;	*/
	TMOD|=0X01;//0000 0001 GATE=0 
	TR0=1;//启动定时器/计数器T0 
	TH0=0XFF;//定时器高8位 初值=65536-100 
	TL0=0X9C;//定时器低8位 
	ET0=1;//打开定时器T0中断
	EA=1;//打开CPU总中断
}


void time0() interrupt 1
{//100us进来一次中断 执行此中断函数
	ui i;
	TH0=0XFF;//初值=65536-100 
	TL0=0X9C;//重新赋值
	counter++;
	counter%=100;// compare=compare%100; 等于0的时候从头再来
	if(counter<speed){//控制左侧电机
		ENA=1;//高电平导通
	}
	else{
		ENA=0;//低电平不导通
	}
	if(counter<sped){//控制右侧电机
		ENB=1;//高电平导通
	}
	else{
		ENB=0;//低电平不导通
	}
	
}


//左侧电机正反转函数
void lrmc(ui i){
// lrmc(1),左侧电机正转：轮子往后走 lrmc(0)左侧电机反转：轮子往前走
    if(i==1){
        IN1=0;IN2=1;//电机正转 小车往后倒
    }
    if(i==0){
        IN1=1;IN2=0;//电机反转 小车往前走
    }
}


//右侧电机正反转函数
void rrmc(ui i){
// rrmc(1),右侧电机正转：轮子往后走 rrmc(0)右侧电机反转：轮子往前走
    if(i==1){
        IN3=0;IN4=1;//电机正转 小车往后倒
    }
    if(i==0){
        IN3=1;IN4=0;//电机反转  小车往前走
    }
}


//控制右侧电机转速
void rs(ui i){
    sped=i;
}

//控制左侧侧电机转速
void ls(ui i){
    speed=i;
}


//避障右侧红外传感器函数
void Rredirs(){

}


//避障左侧红外传感器函数
void Lredirs(){
    
}


//循迹右侧红外传感器函数
void xRredirs(){

}


//循迹左侧红外传感器函数
void xLredirs(){
    
}

#endif
