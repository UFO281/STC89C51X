//--------------源代码源自B站UP主江科大自化协-------感写UP主！！！-------
#ifndef __LCD1602_H__
#define __LCD1602_H__
#include <REGX52.H>
#define LCD_DataPort P0
//-------------IO口配置--------
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;


//---------------函数定义-----------往下---

void LCD_Delay(){//延时函数   LCD1602延时函数，12MHz调用可延时1ms
	unsigned char i, j;
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}


void LCD_WriteCommand(unsigned char Command){//LCD1602写命令 Command 要写入的命令
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}



void LCD_WriteData(unsigned char Data){//LCD1602写数据  Data 要写入的数据
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_EN=1;
	LCD_Delay();
	LCD_EN=0;
	LCD_Delay();
}



void LCD_SetCursor(unsigned char Line,unsigned char Column){//LCD1602设置光标位置 Line 行位置，范围：1~2 Column 列位置，范围：1~16
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else if(Line==2)
	{
		LCD_WriteCommand(0x80|(Column-1+0x40));
	}
}



void LCD_Init(){// LCD1602初始化函数
	LCD_WriteCommand(0x38);//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);//光标复位，清屏
}



void LCD_ShowChar(unsigned char Line,unsigned char Column,char Char){//在LCD1602指定位置上显示一个字符 
//Line 行位置，范围：1~2 Column 列位置，范围：1~16 Char 要显示的字符

	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}



void LCD_ShowString(unsigned char Line,unsigned char Column,char *String){//在LCD1602指定位置开始显示所给字符串
//Line 起始行位置，范围：1~2 Column 起始列位置，范围：1~16 String 要显示的字符串
	
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}



int LCD_Pow(int X,int Y){//返回值=X的Y次方
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}



void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length){//在LCD1602指定位置开始显示所给数字
//Line 起始行位置，范围：1~2 Column 起始列位置，范围：1~16
//Number 要显示的数字，范围：0~65535 Length 要显示数字的长度，范围：1~5

	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(10,i-1)%10+'0');
	}
}



void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length){
// Line 起始行位置，范围：1~2 Column 起始列位置，范围：1~16
//Number 要显示的数字，范围：-32768~32767  Length 要显示数字的长度，范围：1~5

	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_WriteData('+');
		Number1=Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1=-Number;
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number1/LCD_Pow(10,i-1)%10+'0');
	}
}



void LCD_ShowHexNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{//在LCD1602指定位置开始以十六进制显示所给数字
//Line 起始行位置，范围：1~2 Column 起始列位置，范围：1~16
//Number 要显示的数字，范围：0~0xFFFF Length 要显示数字的长度，范围：1~4
	unsigned char i,SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData(SingleNumber+'0');
		}
		else
		{
			LCD_WriteData(SingleNumber-10+'A');
		}
	}
}



void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{//在LCD1602指定位置开始以二进制显示所给数字 
//Line 起始行位置，范围：1~2 Column 起始列位置，范围：1~16
//Number 要显示的数字，范围：0~1111 1111 1111 1111 Length 要显示数字的长度，范围：1~16
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(Number/LCD_Pow(2,i-1)%2+'0');
	}
}

//---------------函数定义-----------往上---
#endif

/* -------------使用例子-----------
void main(){
// LCD1602  共有2行 16列  个矩阵
	
	LCD_Init();//初始化
	LCD_ShowChar(1,3,'w');//在2行3列的位置显示 w字符 
	LCD_ShowString(1,1,"QQ:281");//在1
	LCD_ShowNum(2,7,45313,5);
	LCD_ShowNum(2,12,40,2);
	LCD_ShowString(2,1,"WLS#:");

	while(1){

	}
}
 -------------使用例子-----------*/





