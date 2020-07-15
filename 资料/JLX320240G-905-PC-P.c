/* 	液晶模块型号：JLX320240G-905-PC-P,带字库并行接口
   	驱动IC是:ST75320
   	版权所有：晶联讯电子：网址  http://www.jlxlcd.cn; 
*/
//#include<STC8Aheader.h>
#include<reg51.h>
#include<intrins.h>
#include<chinese.h>
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long int
	
//========================================================
//sbit RES=P7^3;//复位
//sbit CS1=P7^2;//片选
//sbit A0=P4^2;//RS
//sbit E=P7^1;//使能enable
//sbit RW=P7^0;//读写

//sbit key=P3^2;//按键

//sbit Rom_IN=P7^7;    /*字库IC接口定义:Rom_IN就是字库IC的SI*/
//sbit Rom_OUT=P7^6;   /*字库IC接口定义:Rom_OUT就是字库IC的SO*/
//sbit Rom_CS=P7^5;    /*字库IC接口定义Rom_CS就是字库IC的CS#*/
//sbit Rom_SCK=P7^4;   /*字库IC接口定义:Rom_SCK就是字库IC的SCK*/

sbit RES=P3^1;//复位
sbit CS1=P3^0;//片选
sbit A0=P3^2;//RS
sbit E=P1^1;//使能enable
sbit RW=P1^0;//读写

sbit key=P3^0;//按键

sbit Rom_IN=P2^4;    /*字库IC接口定义:Rom_IN就是字库IC的SI*/
sbit Rom_OUT=P2^5;   /*字库IC接口定义:Rom_OUT就是字库IC的SO*/
sbit Rom_CS=P2^7;    /*字库IC接口定义Rom_CS就是字库IC的CS#*/
sbit Rom_SCK=P2^6;   /*字库IC接口定义:Rom_SCK就是字库IC的SCK*/


/*延时：1毫秒的i倍*/
void delay(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<110;k++);
}

/*延时：1us的i倍*/
void delay_us(int i)               
{
	int j,k;
	for(j=0;j<i;j++);
		for(k=0;k<1;k++);
}





//========================================================
void transfer_command_lcd(int data1)
{
	A0=0;
	E=0;
	RW=0;
	CS1=0;
	E=1;
	//P6=data1;
	P0=data1;
	delay_us(1);
	E=0;
	CS1=1;
}


//========================================================
void transfer_data_lcd(int data1)
{
	A0=1;
	E=0;
	RW=0;
	CS1=0;
	E=1;
	//P6=data1;
	P0=data1;
	delay_us(1);
	E=0;
	CS1=1;
}

/*等待一个按键，我的主板是用P2.0与GND之间接一个按键*/
void waitkey()
{
 repeat:
  	if (key==1) goto repeat;
	else delay(3000);
}

void lcd_address(int y,int x)
{
	transfer_command_lcd(0xb1);
	transfer_data_lcd(y);
	transfer_command_lcd(0x13);
	transfer_data_lcd((x>>8)&0x0001);
	transfer_data_lcd(x);   //
	transfer_command_lcd(0x1d);
}


//========================================================
void clear_screen()
{
	int i,j;
	for(i=0;i<30;i++)
	{
		for(j=0;j<320;j++)	//
		{
			lcd_address(i,j);
			transfer_data_lcd(0x00);
		}
	}
}





//========================================================
void initial_lcd()
{
	RES=1;
	RES=0;
	delay(10);
	RES=1;
	delay(20);

	transfer_command_lcd(0xAE); //Display OFF 显示关
	transfer_command_lcd(0xEA); //Power Discharge Control
	transfer_data_lcd(0x00);  	//Discharge OFF
	transfer_command_lcd(0xA8); //sleep out 开工作模式

	transfer_command_lcd(0xAB); //OSC ON，开内置振荡器
	transfer_command_lcd(0x69); //Temperature Detection ON
	transfer_command_lcd(0x4E); //TC Setting，温度梯度补偿
	transfer_data_lcd(0xff);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x44);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x12);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x11);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x11);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x11);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x22);    //0mV/°C, should be adjusted by customer
	transfer_data_lcd(0x23);    //0mV/°C, should be adjusted by customer

	transfer_command_lcd(0x39); //TC Flag
	transfer_data_lcd(0x00);    //
	transfer_data_lcd(0x00);    //

	transfer_command_lcd(0x2B); //Frame Rate Level
	transfer_data_lcd(0x00);    //

	transfer_command_lcd(0x5F); //Set Frame Frequency
	transfer_data_lcd(0x66);    //fFR=80Hz in all temperature range
	transfer_data_lcd(0x66);    //should be adjusted by customer

	transfer_command_lcd(0xEC); //FR Compensation Temp. Range
	transfer_data_lcd(0x19);    //TA = -15 degree, should be adjusted by customer
	transfer_data_lcd(0x64);    //TB = 60 degree, should be adjusted by customer
	transfer_data_lcd(0x6e);    //TC = 70 degree, should be adjusted by customer

	transfer_command_lcd(0xED); //Temp. Hysteresis Value (thermal sensitivity)
	transfer_data_lcd(0x04);    //Vop threshold: +2°C
	transfer_data_lcd(0x04);    //fFR threshold: +4°C

	transfer_command_lcd(0xA6); //Display Inverse OFF
	transfer_command_lcd(0xA4); //Disable Display All Pixel ON

	transfer_command_lcd(0xC4); //COM Output Status
	transfer_data_lcd(0x02);    //Interlace mode, MY=0

	transfer_command_lcd(0xA1); //Column Address Direction: MX=0

	transfer_command_lcd(0x6D); //Display Area
	transfer_data_lcd(0x07);    //Duty = 1/240 duty
	transfer_data_lcd(0x00);    //Start Group = 1

	transfer_command_lcd(0x84); //Display Data Input Direction: Column

	transfer_command_lcd(0x36); //Set N-Line
	transfer_data_lcd(0x1e);    //N-Line

	transfer_command_lcd(0xE4); //N-Line On

	transfer_command_lcd(0xE7); //LCD Drive Method
	transfer_data_lcd(0x19);    //NLFR=1，并行

//--------正常VOP-----------------//
	transfer_command_lcd(0x81); //Set EV=64h
	transfer_data_lcd(0x46);    //VOP
//	transfer_data_lcd(0x3c);    //VOP
	transfer_data_lcd(0x01);    //

	transfer_command_lcd(0xA2); //BIAS
	transfer_data_lcd(0x0a);    //1/16 BIAS

	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x20);    //AVDD ON
	delay(10);

	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x60);    //AVDD, MV3 & NAVDD ON
	delay(10);

	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x70);    //AVDD, MV3, NAVDD & V3 ON
	delay(10);

	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x78);    //AVDD, MV3, NAVDD, V3 & VPF ON
	delay(10);

	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x7c);    //AVDD, MV3, NAVDD, V3, VPF & VNF ON
	delay(10);

	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x7e);    //VOUT, AVDD, MV3, NAVDD, V3, VPF & VNF ON
	delay(10);
	
	transfer_command_lcd(0x25); //Power Control
	transfer_data_lcd(0x7f);    //VOUT, AVDD, MV3, NAVDD, V3, VPF & VNF ON
	delay(10);

	clear_screen();
	transfer_command_lcd(0xAF); //Display ON
}



void display_string_8x16(uint page,uint column,uchar *text)
{
	uint i=0,j,k,n;
	uchar **ascii_table_8x16;
	while(text[i]>0x00)
	{	
		if((text[i]>=0x20)&&(text[i]<=0x7e))
		{
			j=text[i]-0x20;
			for(n=0;n<2;n++)
			{			
				lcd_address(page+n,column);
				for(k=0;k<8;k++)
				{
					transfer_data_lcd(ascii_table_8x16[j][k+8*n]);/*显示5x7的ASCII字到LCD上，y为页地址，x为列地址，最后为数据*/
				}
			}
			i++;
			column+=8;
			
		}
		else
		i++;
	}
}

//写入一组16x16点阵的汉字字符串（字符串表格中需含有此字）
//括号里的参数：(页，列，汉字字符串）
void display_string_16x16(uchar page,uchar column, uchar *text)
{
	uchar i,j,k;
	uint address;
	uchar **Chinese_text_16x16;
	uchar *Chinese_code_16x16;
	j=0;
	while(text[j]!= '\0')
	{
		i=0;
		address=1;
		while(Chinese_text_16x16[i]> 0x7e)
		{
			if(Chinese_text_16x16[i] == text[j])
			{
				if(Chinese_text_16x16[i+1] == text[j+1])
				{
					address=i*16;
					break;
				}
			}
			i +=2;
		}
		if(column>320)
		{
			column=0;
			page+=2;
		}
		if(address !=1)
		{
			for(k=0;k<2;k++)
			{
				for(i=0;i<16;i++)
				{
					lcd_address(page+k,column+i);
					transfer_data_lcd(Chinese_code_16x16[address]);
					address++;
				}
			}
			j +=2;
		}
		else
		{

			for(k=0;k<2;k++)
			{
				for(i=0;i<16;i++)
				{
					lcd_address(page+k,column+i);
					transfer_data_lcd(0x00);
				}
			}
			j++;
		}
		column+=16;
	}
}


//写入一组16x16点阵的汉字字符串（字符串表格中需含有此字）
//括号里的参数：(页，列，汉字字符串）

void display_string_32x32(uchar page,uchar column, uchar *text)
{
	uchar i,j,k;
	uint address;
	uchar *Chinese_text_32x32;
	uchar *Chinese_code_32x32;
	j=0;
	while(text[j]!= '\0')
	{
		i=0;
		address=1;
		while(Chinese_text_32x32[i]> 0x7e)
		{
			if(Chinese_text_32x32[i] == text[j])
			{
				if(Chinese_text_32x32[i+1] == text[j+1])
				{
					address=i*64;
					break;
				}
			}
			i +=2;
		}
		if(address !=1)
		{
			for(k=0;k<4;k++)
			{
				for(i=0;i<32;i++)
				{
					lcd_address(page+k,column+i);
					transfer_data_lcd(Chinese_code_32x32[address]);
					address++;
				}
			}
			j +=2;
		}
		else
		{

			for(k=0;k<4;k++)
			{
				for(i=0;i<32;i++)
				{
					lcd_address(page+k,column+i);
					transfer_data_lcd(0x00);
				}
			}
			j++;
		}
		column+=32;
	}
}

void test(uchar data1,uchar data2)
{
	int i,j;	
	for(i=0;i<30;i++)
	{
		for(j=0;j<320;j++)
		{
			lcd_address(i,j);
			transfer_data_lcd(data1);
			transfer_data_lcd(data2);
		}
	}
}


//========================================================
void showpic(char *k)
{
	int i,j;
	for(i=0;i<30;i++)
	{
		for(j=0;j<320;j++)	//
		{
			lcd_address(i,j);
			transfer_data_lcd(*k++);
		}
	}
}

/****送指令到晶联讯字库IC***/
void send_command_to_ROM( uchar datu )
{
	uchar i;
	for(i=0;i<8;i++ )
	{
		if(datu&0x80)
			Rom_IN = 1;
		else
			Rom_IN = 0;
			datu = datu<<1;
			Rom_SCK=0;
			delay_us(1);
			Rom_SCK=1;
			delay_us(1);
	}
}

/****从晶联讯字库IC中取汉字或字符数据（1个字节）***/
static uchar get_data_from_ROM( )
{
	uchar i;
	uchar ret_data=0;
	Rom_SCK=1;
	for(i=0;i<8;i++)
	{
		Rom_OUT=1;
		Rom_SCK=0;
		ret_data<<=1;
		if( Rom_OUT )
			ret_data+=1;
		else
			ret_data=ret_data+0;
		Rom_SCK=1;
		delay_us(10);
	}

	return(ret_data);
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_8x16(ulong fontaddr,uint page,uint column)
{
	uchar i,j,disp_data;	
	Rom_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 		 //地址的低8位,共24位
	for(j=0;j<2;j++)
	{
		for(i=0; i<8; i++ )
	  {
		  	lcd_address(page+j,column+i);
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	Rom_CS=1;
}

void get_and_write_12x24(ulong fontaddr,uint page,uint column)
{
	uchar i,j,disp_data;
	Rom_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);						 //地址的低8位,共24位
	for(j=0;j<3;j++)
	{
		for(i=0; i<16; i++ )
	  {
		  	lcd_address(page+j,column+i);
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	Rom_CS=1;
}



void get_and_write_16x32(ulong fontaddr,uint page,uint column)
{
	uchar i,j,disp_data;
	Rom_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	for(j=0;j<4;j++)
	{
		for(i=0; i<16; i++ )
		{
			lcd_address(page+j,column+i);
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	Rom_CS=1;
}


//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_16x16(ulong fontaddr,uint page,uint column)
{
	uchar i,j,disp_data;
	Rom_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	for(j=0;j<2;j++)
	{
		for(i=0; i<16; i++ )
	  {
		  	lcd_address(page+j,column+i);
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	Rom_CS=1;
}

//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_24x24(ulong fontaddr,uint page,uint column)
{
	uchar i,j,disp_data;
	Rom_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	for(j=0;j<3;j++)
	{
		for(i=0; i<24; i++ )
		{
			lcd_address(page+j,column+i);
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	Rom_CS=1;
}


//从指定地址读出数据写到液晶屏指定（page,column)座标中
void get_and_write_32x32(ulong fontaddr,uint page,uint column)
{
	uchar i,j,disp_data;
	Rom_CS = 0;
	send_command_to_ROM(0x03);
	send_command_to_ROM((fontaddr&0xff0000)>>16);	 //地址的高8位,共24位
	send_command_to_ROM((fontaddr&0xff00)>>8);		 //地址的中8位,共24位
	send_command_to_ROM(fontaddr&0xff);				 //地址的低8位,共24位
	for(j=0;j<4;j++)
	{
		for(i=0; i<32; i++ )
	  {
		  	lcd_address(page+j,column+i);
			disp_data=get_data_from_ROM();
			transfer_data_lcd(disp_data);	//写数据到LCD,每写完1字节的数据后列地址自动加1
		}
	}
	Rom_CS=1;
}

//****************************************************************
ulong  fontaddr=0;
void display_GB2312_16x16_string(uint page,uint column,uchar *text)
{
	uchar i= 0,	temp1,temp2;
	temp1=column;
	temp2=page;
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*32);
			fontaddr = (ulong)(fontaddr+0x2c9d0);

			get_and_write_16x16(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=16;	
			
			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=2;
				if (page>29)column=1;			
			}
		}

		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）15x16点的字符在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (ulong)(fontaddr*32);
			fontaddr = (ulong)(fontaddr+0x2c9d0);
	
			get_and_write_16x16(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=16;	
			
			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=2;
				if (page>29)column=1;
			}
		}
			
		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{									
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x1dd780);			

			get_and_write_8x16(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=1;
			column+=8;
			
			if ((temp1<=29&&temp2<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=2;
				if (page>29)column=1;
			}			
		}
			
		else
			i++;
	}		
}


//****************************************************************
void display_GB2312_24x24_string(uint page,uint column,uchar *text)
{
	uchar i= 0,temp1,temp2;
	temp1=column;
	temp2=page;
	
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*72);
			fontaddr = (ulong)(fontaddr+0X068190);

			get_and_write_24x24(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=24;

			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=2;
				if (page>29)column=1;
			}				
		}

		else if(((text[i]>=0xa1) &&(text[i]<=0xa9))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）15x16点的字符在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (ulong)(fontaddr*72);
			fontaddr = (ulong)(fontaddr+0X068190);
	
			get_and_write_24x24(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=24;

			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=2;
				if (page>29)column=1;
			}
		}
			
		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{									
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*48);
			fontaddr = (unsigned long)(fontaddr+0x1dff00);			
			get_and_write_12x24(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=1;
			column+=12;

			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=3;
				if (page>29)column=1;
			}
		}		
		else
			i++;
	}		
}


//****************************************************************
void display_GB2312_32x32_string(uint page,uint column,uchar *text)
{
	uchar i= 0,temp1,temp2;
	temp1=column;
	temp2=page;
	
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）汉字在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (ulong)(fontaddr*128);
			fontaddr = (ulong)(fontaddr+0xedf00);

			get_and_write_32x32(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=32;	
			
			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=4;
				if (page>29)column=1;
			}				
		}

		else if(((text[i]>=0xa1) &&(text[i]<=0xa9))&&(text[i+1]>=0xa1))
		{						
			//国标简体（GB2312）15x16点的字符在晶联讯字库IC中的地址由以下公式来计算：
			//Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0
			//由于担心8位单片机有乘法溢出问题，所以分三部取地址
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (ulong)(fontaddr*128);
			fontaddr = (ulong)(fontaddr+0xedf00);
	
			get_and_write_32x32(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=2;
			column+=32;

			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=4;
				if (page>29)column=1;
			}
		}
			
		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{									
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*64);
			fontaddr = (unsigned long)(fontaddr+0x1e5a50);			

			get_and_write_16x32(fontaddr,page,column);	 //从指定地址读出数据写到液晶屏指定（page,column)座标中
			i+=1;
			column+=16;

			if ((temp2<=29&&temp1<=320)&&column>312)
			{
				//自动换行，当遇到奇数个字母或符号就提前8个点
				//设成符>320时当有奇数个字符时就会显半个汉字,因为一个字符只占8个点（一个字节）
				column=1;
				page+=4;
				if (page>29)column=1;
			}
		}
			
		else
			i++;
	}		
}



//========================================================
void main()
{
	initial_lcd(); 		//对液晶模块进行初始化设置; 
	while(1)
	{
		clear_screen();
		display_GB2312_24x24_string(0,15,"深圳市晶联讯电子有限公司");
		display_GB2312_32x32_string(3,23,"JLX320240G-905-PC");
		display_GB2312_16x16_string(7,0,"1.点阵:320x240、320列、30页、每页8行;");
		display_GB2312_16x16_string(10,0,"2.带16x16简体汉字库及8x16点阵ASCII字符;");
		display_GB2312_24x24_string(13,0,"3.带24x24简体汉字库及12x24   点阵ASCII字符;");
		display_GB2312_32x32_string(20,0,"4.带32x32简体汉字库   16x32点阵ASCII字符");
		waitkey();		
		clear_screen(); 
		display_string_8x16(0,31,"JLX320240G-905");
		display_string_16x16(2,31,"深圳市晶联讯电子有限公司");
		display_string_32x32(4,31,"深圳市晶联讯电子");
		waitkey();
		showpic(bmp1);
		waitkey();
		showpic(bmp2);
		waitkey();
		showpic(bmp3);
		waitkey();
		showpic(bmp8);
		waitkey();
		showpic(bmp9);
		waitkey();
		test(0x55,0xaa);
		waitkey();
		test(0xaa,0x55);
		waitkey();
		test(0xff,0xff);
		waitkey();

	}
}
