/*-----------------Ӧ������---------------------
void main(){
	
	//speed��ֵ���ӵ�ѹ���� �������
	
	while(1){
		cshtm();//���ö�ʱ���ж�
		
		lrmc(1);//���������ת����
		ls(1000);//����������ת��
		
		rrmc(0);//�Ҳ��������ת����
		rs(1000);//�����Ҳ����ת��
	}
	
}
-----------------Ӧ������---------------------*/

#ifndef _CARCON_H_
#define _CARCON_H_
#include<reg52.h> 
typedef unsigned int ui;   //���������ͽ�����������
typedef unsigned char uc;
uc counter;
uc speed=0;//����ͨ��ռ�ձ�
sbit ENA=P1^0;//����PWM�����
sbit ENB=P1^1;//�ҵ��PWM�����

sbit IN1=P1^2;// IN1 IN2 ��������� ��ת ���߷�ת
sbit IN2=P1^3;// IN1=0,IN2=1:�����ת IN1=1,IN2=0�������ת 

sbit IN3=P1^4;//IN3 IN4 �����Ҳ��� ��ת ���߷�ת
sbit IN4=P1^5;//IN3=0,IN4=1:������� IN3=1,IN4=0�������ת 

sbit fttirsr=P3^6;//�ڰ�ѭ�����⴫���� ����
sbit fttirsl=P3^7;//�ڰ�ѭ�����⴫���� ����

sbit irsr=P3^5;//�Һ��⴫����
sbit irsl=P3^4;//����⴫����


void delay(ui m){//��ʱ���� m us 
	ui x;
	while(m--){
		for(x=114;x>0;x--);//ִ��1us
	}
}

void cshtm(){//��ʱ����ʼ���ĺ��� T0��ʱ��/������

/*��ֵa=65536-(f����Ƶ��/12)*t Ϊʱ�� ��λ��΢��us ��aת��Ϊ16���ƣ��ֱ����TH0 ,TL0 �߰�λ�͵Ͱ�λ
���� a=FC18 Ȼ��TH0=0XFC; TL0=0X18;	
*/	TMOD|=0X01;//0000 0001 GATE=0 
	TR0=1;//������ʱ��/������T0 
	TH0=0XFF;//��ʱ����8λ ��ֵ=65536-1000 ����16����,��ʱ �軻��us1ms/1us=1000
	TL0=0X9C;//��ʱ����8λ 
	ET0=1;//�򿪶�ʱ��T0�ж�
	EA=1;//��CPU���ж�
}





void time0() interrupt 1
{//100us����һ���ж�
	ui i;
	TH0=0XFF;//��ֵ=65536-1000 ����16����,��ʱ �軻��us1ms/1us=1000
	TL0=0X9C; 
	//���¸�ֵ
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


void lrmc(ui i){//���������ת����
// lrmc(1),�������ת lrmc(0)�������ת
    if(i==1){
        IN1=0;IN2=1;//�����ת С������
    }
    if(i==0){
        IN1=1;IN2=0;//�����ת С����ǰ��
    }
}

void rrmc(ui i){//�Ҳ�������ת����
// rrmc(1),�Ҳ�����ת rrmc(0)�Ҳ�����ת
    if(i==1){
        IN3=0;IN4=1;//�����ת С������
    }
    if(i==0){
        IN3=1;IN4=0;//�����ת  С����ǰ��
    }
}

void rs(ui i){//�����Ҳ���ת��
    speed=i;
}

void ls(ui i){//����������ת��
    speed=i;
}

void Rredirs(){//�����Ҳ���⴫��������

}
void Lredirs(){//���������⴫��������
    
}

void xRredirs(){//ѭ���Ҳ���⴫��������

}
void xLredirs(){//ѭ�������⴫��������
    
}
#endif