#include"reg52.h"
#ifndef _I2C_H_//ͷ�ļ���ʼ
#define _I2C_H_//----------51��Ƭ������һ������ʱ��������1us--------
 sbit I2C_SCL=P2^1;//I2c��ʱ����
 sbit I2C_SDA=P2^0;//I2C��������
 /*SCL�͵�ƽ�ڼ� SDA���Է����仯 ��ȡ����
 ����SCL�ڸߵ�ƽ�ڼ� SDA���ܱ仯���͵�ƽ���ǵ͵�ƽ���ߵ�ƽ���Ǹߵ�ƽ*/


//I2C��ʼ
void I2C_start(){
    I2C_SCL=1;//SCLΪ�ߵ�ƽ
    I2C_SDA=1;//SDA�������½���
    I2C_SDA=0;
    I2C_SCL=0;
}

//I2C����
void I2C_stop(){
    I2C_SCL=0;
    I2C_SDA=0;//������������
    I2C_SDA=1;
    I2C_SCL=1;
}


//I2C�����ֽ�
void I2C_SendByte(unsigned char Byte){

    unsigned char i=0;

    for(i;i<8;i++){
        I2C_SDA=Byte&(0x80>>i);//byte���λȡ���� ��ֵ��SDA
        I2C_SCL=1;//  0x80>>i ����iλ
        I2C_SCL=0;
    }
}


//I2C�����ֽ�
unsigned char I2C_ReceiveByte(){

    unsigned char i,Byte=0x00;
    I2C_SDA=1;//�ͷ�����
    for(i=0;i<8;i++){ 
        I2C_SCL=1;//SCL�ߵ�ƽ�ſ��Զ�ȡSDA
        if(I2C_SDA){
            Byte|=(0x80>>i);
        }
        I2C_SCL=0;
    }
    return Byte;
}


//I2C����Ӧ��
void I2C_SendAck(unsigned char AckBit){// bit C51�������������� ֻ�ܴ�һλ0/1

    I2C_SDA=AckBit;
    I2C_SCL=1;
    I2C_SCL=0;
}


//I2C����Ӧ��
unsigned char I2C_ReceiveAck(){
    
    unsigned char AckBit=0;
    I2C_SDA=1;//�ͷ�
    I2C_SCL=1;
    AckBit=I2C_SDA;
    I2C_SCL=0;
    return AckBit;
}






#endif//�ļ�����
