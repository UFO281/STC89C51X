#ifndef _HCSR04_H_//超声波传感器
#define _HCSR04_H_
#include"OLED096.h"
#include<intrins.h>	
sbit Trig = P2^1;
sbit Echo = P2^0;
/*-----------超声波模块HC-SR04,使用例程-----
void main(){

	use_ultrasonic();//只需要调用这个函数就行了
}

-----------超声波模块HC-SR04,使用例程-----*/


unsigned int  time=0;
unsigned long S=0;
bit flag =0;//比特类型数据  只能赋值0或1


//超声波传感器计算函数
void Conut(){

	time=TH0*256+TL0;
	TH0=0;
	TL0=0;
	S=(time*1.7)/100; //计算出来是CM 测量的距离
	if((S>=700)||flag==1){ //超出测量范围显示	 
		flag=0;
		OLED_ShowString(0,2,"Error! so near!");//在0列 2行 显示字符串error!
		OLED_Clear();//清屏
	}
	else{
		
		OLED_ShowString(0,4,"DIST:");//在0列 4行 显示字符串PWM
		OLED_ShowNum(44,4,S,3,16);//显示整数 在35列 4行 16X16字体
		OLED_ShowString(70,4,"CM");//在90列 4行 显示字符串CM 
	}
}



//超声波启动模块
 void  StartModule(){//启动一次模块
	  Trig=1;			                     
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_();//12M晶振 t(时间)=12/f 延时1us
	  _nop_();
	  Trig=0;
}




//定时器0
void Timer0(){
	EA=1;//开启总中断	
	ET0=1;//允许T0中断
	TMOD=0x01;//设T0为方式1，GATE=1；
	TH0=0;
	TL0=0;   
}

void zd0() interrupt 1 		 //T0中断用来计数器溢出,超过测距范围
{
    flag=1;//中断溢出标志							 
}


//只需要在main函数里调用这个函数就行了
//使用超声波传感器 并使用0.96OLED显示
void use_ultrasonic(){

	Timer0();//定时器
	OLED_Init();//初始化OLED
	OLED_Clear();//OLED清除屏幕显示
	while(1)
	{
		 StartModule();//超声波启动模块
	     while(!Echo);		//当RX为零时等待
	     TR0=1;			    //开启计数
	     while(Echo);			//当RX为1计数并等待
	     TR0=0;				//关闭计数
         Conut();//显示计算
		 delay_ms(200);
	}

}

#endif