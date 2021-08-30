//---------------------MPU6050使用简介---------------
#ifndef __MPU6050_H
#define __MPU6050_H

#include"reg52.h"
#include<math.h>      
#include<stdio.h>   
#include<INTRINS.H>

/*-----------------------MPU6050使用例子---------------------------------
//显示温度
void display_temp()
{ 
	Temp_h=Single_ReadI2C(TEMP_OUT_H); //读取温度
	Temp_l=Single_ReadI2C(TEMP_OUT_L); //读取温度
	Temperature=Temp_h<<8|Temp_l;     //合成温度
	Temperature = 35+ ((double) (Temperature + 13200)) / 280; // 计算出温度
	lcd_printf(dis,Temperature);     //转换数据显示
	DisplayListChar(11,1,dis,4);     //启始列，行，显示数组，显示位数
}

void main()
{ 
	delay(500);		//上电延时		
	InitMPU6050();	//初始化MPU6050
	delay(150);
	while(1)
	{
		GetData(ACCEL_XOUT_H)//显示X轴加速度
		GetData(ACCEL_YOUT_H)//显示Y轴加速度
		GetData(ACCEL_ZOUT_H)//显示Z轴加速度
		GetData(GYRO_XOUT_H)//显示X轴角速度
		GetData(GYRO_YOUT_H)//显示Y轴角速度
		GetData(GYRO_ZOUT_H)//显示Z轴角速度
		delay(500);
	}
}
-----------------------MPU6050使用例子---------------------------------*/


sbit    SCL=P3^7;			//IIC时钟 clock引脚定义
sbit    SDA=P3^6;			//IIC数据 data引脚定义
#define	SMPLRT_DIV		0x19  //陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A  //低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B  //陀螺仪自检及测量范围，典型值：0x18(不自检，2000°/s)
#define	ACCEL_CONFIG	0x1C  //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

//------------这些寄存器用于存放加速度传感器，角速度传感器的测量结果---往下---------


//----------------X,Y,Z轴加速度寄存器---往下-----------
//测量的加速度的结果是一个16位的结果 一个寄存器有8位 所以需要俩寄存器来装加速度结果
//读取到寄存器后 还得再加到一块 计算出来结果
#define	ACCEL_XOUT_H	0x3B //X轴加速度寄存器
#define	ACCEL_XOUT_L	0x3C //X轴加速度寄存器
#define	ACCEL_YOUT_H	0x3D 
#define	ACCEL_YOUT_L	0x3E 
#define	ACCEL_ZOUT_H	0x3F 
#define	ACCEL_ZOUT_L	0x40 
//----------------X,Y,Z轴加速度寄存器----往上----------


//----------------温度寄存器----往下--------
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
//----------------温度寄存器----往上--------


//-----------X,Y,Z轴角速度寄存器---往下-----
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
//-----------X,Y,Z轴角速度寄存器---往上-----

//------------这些寄存器用于存放加速度传感器，角速度传感器的测量结果--往上----------


#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//MPU6050 IC2地址





unsigned char dis[4];//显示数字(-511至512)的字符数组
int	dis_data;//变量
int	Temperature,Temp_h,Temp_l;	//温度及高低位数据



//---------------------函数声明-----往下--------

void  delay(unsigned int k);//延时
//--------------MPU6050操作函数--------------
void  InitMPU6050();//初始化MPU6050
void  Delay5us();
void  I2C_Start();
void  I2C_Stop();
void  I2C_SendACK(bit ack);
bit   I2C_RecvACK();
void  I2C_SendByte(unsigned char dat);
unsigned char I2C_RecvByte();
void  I2C_ReadPage();
void  I2C_WritePage();
void  display_ACCEL_x();
void  display_ACCEL_y();
void  display_ACCEL_z();
unsigned char Single_ReadI2C(unsigned char REG_Address);//读取I2C数据
void  Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);//向I2C写入数据
//--------------MPU6050操作函数--------------

//---------------------函数声明------往上--------




//延时
void delay(unsigned int k)	
{						
	unsigned int i,j;				
	for(i=0;i<k;i++)
	{			
		for(j=0;j<121;j++);
	}						
}


//延时5微秒(51单片机：12M晶振)
void Delay5us()
{
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}


//I2C起始信号
void I2C_Start()
{
    SDA = 1;//拉高数据线
    SCL = 1;//拉高时钟线
    Delay5us();//延时
    SDA = 0;//产生下降沿
    Delay5us();//延时
    SCL = 0;//拉低时钟线
}


//I2C停止信号
void I2C_Stop()
{
    SDA = 0;//拉低数据线
    SCL = 1;//拉高时钟线
    Delay5us();//延时
    SDA = 1;//产生上升沿
    Delay5us();//延时
}


//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
void I2C_SendACK(bit ack)
{
    SDA = ack;//写应答信号
    SCL = 1;//拉高时钟线
    Delay5us();//延时
    SCL = 0;//拉低时钟线
    Delay5us();//延时
}


//I2C接收应答信号
bit I2C_RecvACK()
{
    SCL = 1;//拉高时钟线
    Delay5us(); //延时
    CY = SDA; //读应答信号
    SCL = 0;//拉低时钟线
    Delay5us();//延时
    return CY;
}


//向I2C总线发送一个字节数据
void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for (i=0; i<8; i++)//8位计数器
    {
        dat <<= 1; //移出数据的最高位
        SDA = CY;//送数据口
        SCL = 1; //拉高时钟线
        Delay5us(); //延时
        SCL = 0; //拉低时钟线
        Delay5us();//延时
    }
    I2C_RecvACK();
}


//从I2C总线接收一个字节数据
unsigned char I2C_RecvByte()
{
    unsigned char i;
    unsigned char dat = 0;
    SDA = 1;//使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)//8位计数器
    {
        dat <<= 1;
        SCL = 1;//拉高时钟线
        Delay5us();//延时
        dat |= SDA;//读数据               
        SCL = 0;//拉低时钟线
        Delay5us();//延时
    }
    return dat;
}


//向I2C设备写入一个字节数据
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    I2C_Start();//起始信号
    I2C_SendByte(SlaveAddress);//发送设备地址+写信号
    I2C_SendByte(REG_Address);//内部寄存器地址，
    I2C_SendByte(REG_data);//内部寄存器数据，
    I2C_Stop();//发送停止信号
}


//从I2C设备读取一个字节数据
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	I2C_Start();//起始信号
	I2C_SendByte(SlaveAddress);//发送设备地址+写信号
	I2C_SendByte(REG_Address);//发送存储单元地址，从0开始	
	I2C_Start();//起始信号
	I2C_SendByte(SlaveAddress+1);//发送设备地址+读信号
	REG_data=I2C_RecvByte();//读出寄存器数据
	I2C_SendACK(1);//接收应答信号
	I2C_Stop();//停止信号
	return REG_data;
}


//初始化MPU6050
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}


//合成数据
int GetData(unsigned char REG_Address)
{
	char H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return (H<<8)+L;   //合成数据
}


#endif