#include"reg52.h"
#ifndef _I2C_H_//头文件开始
#define _I2C_H_//----------51单片机运行一条语句的时间至少是1us--------
 sbit I2C_SCL=P2^1;//I2c的时钟线
 sbit I2C_SDA=P2^0;//I2C的数据线
 /*SCL低电平期间 SDA可以发生变化 读取数据
 但是SCL在高电平期间 SDA不能变化，低电平就是低电平，高电平就是高电平*/


//I2C开始
void I2C_start(){
    I2C_SCL=1;//SCL为高电平
    I2C_SDA=1;//SDA产生个下降沿
    I2C_SDA=0;
    I2C_SCL=0;
}

//I2C结束
void I2C_stop(){
    I2C_SCL=0;
    I2C_SDA=0;//产生个上升沿
    I2C_SDA=1;
    I2C_SCL=1;
}


//I2C发送字节
void I2C_SendByte(unsigned char Byte){

    unsigned char i=0;

    for(i;i<8;i++){
        I2C_SDA=Byte&(0x80>>i);//byte最高位取出来 赋值给SDA
        I2C_SCL=1;//  0x80>>i 右移i位
        I2C_SCL=0;
    }
}


//I2C接收字节
unsigned char I2C_ReceiveByte(){

    unsigned char i,Byte=0x00;
    I2C_SDA=1;//释放总线
    for(i=0;i<8;i++){ 
        I2C_SCL=1;//SCL高电平才可以读取SDA
        if(I2C_SDA){
            Byte|=(0x80>>i);
        }
        I2C_SCL=0;
    }
    return Byte;
}


//I2C发送应答
void I2C_SendAck(unsigned char AckBit){// bit C51中特有数据类型 只能存一位0/1

    I2C_SDA=AckBit;
    I2C_SCL=1;
    I2C_SCL=0;
}


//I2C接收应答
unsigned char I2C_ReceiveAck(){
    
    unsigned char AckBit=0;
    I2C_SDA=1;//释放
    I2C_SCL=1;
    AckBit=I2C_SDA;
    I2C_SCL=0;
    return AckBit;
}






#endif//文件结束
