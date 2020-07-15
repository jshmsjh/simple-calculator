#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <reg51.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
	
#define uchar unsigned char
#define uint  unsigned int
/*12864端口定义*/
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P3^5;            //寄存器选择输入 
sbit LCD_RW  =  P3^6;            //液晶读/写控制
sbit LCD_EN  =  P3^4;            //液晶使能控制
sbit LCD_PSB =  P3^1;            //串/并方式控制
sbit wela    =  P2^6;
sbit dula    =  P2^7;
sbit key1=P3^0;                   //按键
sbit key2=P3^1;
sbit key3=P3^2;

#endif