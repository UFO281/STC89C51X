/*--------------温度传感器DS18B20使用例子-----使用0.96OLED显示温度---------------
void main(){

	float T;
	unsigned int x;
	DS18B20_convert_T();
	delay_ms(1000);
    OLED_Init();//初始化OLED  
	OLED_Clear();//清屏
	while(1){

		DS18B20_convert_T();//转化温度
		T=DS18B20_read_temp();//读取温度
		if(T<0){ 
			OLED_ShowString(40,1,"-");//在40列 1行 显示字符串 -
			T=-T;
		}
		else{
			OLED_ShowString(40,1,"+");//在40列 1行 显示字符串 +
		}
		x=T*100;
		x=(x%1000)%100;//显示小数点后两位小数
		OLED_ShowString(0,1,"Temp:");//在0列 1行 显示字符串PWM
		OLED_ShowNum(50,1,T,3,16);//显示整数55 在35列 4行 16X16字体
		OLED_ShowString(75,1,".");//在0列 4行 显示字符串 %
		OLED_ShowNum(80,1,x,2,16);//显示整数55 在35列 4行 16X16字体
		OLED_ShowString(100,1,"c");//在0列 4行 显示字符串 %
		delay_ms(500);//延时500ms
		
	}
}
--------------温度传感器DS18B20使用例子-------------------*/

#ifndef _DS18B20_H
#define _DS18B20_H
#include"OLED096.h"
#include"intrins.h"
#define   DS18B20_SKIP_ROM       0xcc  //忽略ROM指令
#define   DS18B20_convert_temp   0x44  //温度转换指令
#define   DS18B20_read_register  0xBE  //读暂存器指令
sbit one_Wire=P3^7;//DS18B20 单总线接口 



//------------------单总线协议区域---------------往下-------------

//单总线初始化
bit One_wire_Init(){//返回值 只返回1位 0/1
    
    unsigned char i;//定义变量要放在语句的最前边 
	unsigned char AckBit;//应答位
	one_Wire=1;
	one_Wire=0;
	_nop_();i = 227;while (--i);//延时500us 如果用函数则不行 因为执行一条语句需要1us 函数跳转也需要时间 i其他语句也需要时间 
	one_Wire=1;//释放总线
	_nop_();i = 29;while (--i);//延时70us
	AckBit=one_Wire;//应答位
	_nop_();i = 227;while (--i);//延时500us 

	return AckBit;

}


//单总线发送一位数据
void oneWire_send_bit(unsigned char Bit){

	unsigned char i;
	one_Wire=0;
	i = 3;while (--i);//延时10us
	one_Wire=Bit;//将数据发送给单总线
	i = 22;while (--i);//延时50us
	one_Wire=1;

}


//单总线接收一位数据
unsigned char oneWire_recive_bit(){

	unsigned char Bit;
	unsigned char i;
	one_Wire=0;//拉低总线
	_nop_();i = 1;while (--i);//延时5us
	one_Wire=1;//释放总线
	_nop_();i = 1;while (--i);//延时5us
	Bit=one_Wire;//采样
	_nop_();i = 20;while (--i);//延时50us
	return Bit;
}


//单总线发送一个字节数据
void oneWire_send_Byte(unsigned char byte){

	unsigned char i;
	for(i=0;i<8;i++){//循环八位 发送一个字节
		oneWire_send_bit(byte&(0x01<<i));//从低位到高位发送出去
	}
}


//单总线接收一个字节数据
unsigned char oneWire_recive_Byte(){

	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++){//循环八位 接收一个字节
		if(oneWire_recive_bit()){
			Byte|=0x01<<i;
		}
	}
	return Byte;
}
//------------------单总线协议区域---------------往上-------------


//--------------------DS18B20使用函数---------------往下-------------

//转换温度
void DS18B20_convert_T(){

	One_wire_Init();//1.初始化 单总线
	oneWire_send_Byte(DS18B20_SKIP_ROM);//2.忽略ROM指令
	oneWire_send_Byte(DS18B20_convert_temp);//3.温度转化指令

}


//读取温度
float DS18B20_read_temp(){

	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	One_wire_Init();
	oneWire_send_Byte(DS18B20_SKIP_ROM);//2.忽略ROM指令
	oneWire_send_Byte(DS18B20_read_register);//3.读暂存器指令
	TLSB=oneWire_recive_Byte();//第一个温度寄存器
	TMSB=oneWire_recive_Byte();//第二个温度寄存器
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;//实际温度
	return T;
}

//--------------------DS18B20使用函数---------------往上-------------


#endif








