#ifndef _HCSR04_H_//������������
#define _HCSR04_H_
#include"OLED096.h"
#include<intrins.h>	
sbit Trig = P2^1;
sbit Echo = P2^0;
/*-----------������ģ��HC-SR04,ʹ������-----
void main(){

	use_ultrasonic();//ֻ��Ҫ�����������������
}

-----------������ģ��HC-SR04,ʹ������-----*/


unsigned int  time=0;
unsigned long S=0;
bit flag =0;//������������  ֻ�ܸ�ֵ0��1


//���������������㺯��
void Conut(){

	time=TH0*256+TL0;
	TH0=0;
	TL0=0;
	S=(time*1.7)/100; //���������CM �����ľ���
	if((S>=700)||flag==1){ //����������Χ��ʾ	 
		flag=0;
		OLED_ShowString(0,2,"Error! so near!");//��0�� 2�� ��ʾ�ַ���error!
		OLED_Clear();//����
	}
	else{
		
		OLED_ShowString(0,4,"DIST:");//��0�� 4�� ��ʾ�ַ���PWM
		OLED_ShowNum(44,4,S,3,16);//��ʾ���� ��35�� 4�� 16X16����
		OLED_ShowString(70,4,"CM");//��90�� 4�� ��ʾ�ַ���CM 
	}
}



//����������ģ��
 void  StartModule(){//����һ��ģ��
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
	  _nop_();//12M���� t(ʱ��)=12/f ��ʱ1us
	  _nop_();
	  Trig=0;
}




//��ʱ��0
void Timer0(){
	EA=1;//�������ж�	
	ET0=1;//����T0�ж�
	TMOD=0x01;//��T0Ϊ��ʽ1��GATE=1��
	TH0=0;
	TL0=0;   
}

void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
{
    flag=1;//�ж������־							 
}


//ֻ��Ҫ��main����������������������
//ʹ�ó����������� ��ʹ��0.96OLED��ʾ
void use_ultrasonic(){

	Timer0();//��ʱ��
	OLED_Init();//��ʼ��OLED
	OLED_Clear();//OLED�����Ļ��ʾ
	while(1)
	{
		 StartModule();//����������ģ��
	     while(!Echo);		//��RXΪ��ʱ�ȴ�
	     TR0=1;			    //��������
	     while(Echo);			//��RXΪ1�������ȴ�
	     TR0=0;				//�رռ���
         Conut();//��ʾ����
		 delay_ms(200);
	}

}

#endif