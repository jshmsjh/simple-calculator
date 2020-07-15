#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <reg51.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
	
#define uchar unsigned char
#define uint  unsigned int
/*12864�˿ڶ���*/
#define LCD_data  P0             //���ݿ�
sbit LCD_RS  =  P3^5;            //�Ĵ���ѡ������ 
sbit LCD_RW  =  P3^6;            //Һ����/д����
sbit LCD_EN  =  P3^4;            //Һ��ʹ�ܿ���
sbit LCD_PSB =  P3^1;            //��/����ʽ����
sbit wela    =  P2^6;
sbit dula    =  P2^7;
sbit key1=P3^0;                   //����
sbit key2=P3^1;
sbit key3=P3^2;

#endif