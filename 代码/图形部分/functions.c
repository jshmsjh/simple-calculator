#include "config.h"
#include "functions.h"
#include <math.h>


//double v[100],res;
//char s[100],ss[100],res_str[100],ch;
//int i,j,k;


#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

int  playflag=0;
uchar buf,m,count;
//uchar temp;
int flag_1=0;
int flag_2=0;
int flag_3=0;


uchar data  RXDdata[ ] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
                          0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20 };

/*******************************************************************/
/*                                                                 */
/*  延时函数                                                       */
/*                                                                 */
/*******************************************************************/
void delay(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<250;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}		
/*******************************************************************/
/*                                                                 */
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*                                                                 */
/*******************************************************************/
bit check_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }

 /***********************************
从LCD中读出数据
************************************/
unsigned char Lcd_ReadData(void)
{
	unsigned char Temp;
	while(check_busy());
 	P0=0xff;
 	LCD_RS=1;
	LCD_RW=1;
	LCD_EN=1;
	_nop_();
   	Temp=P0;
   	LCD_EN=0;
   	return Temp;
}
 
/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/
void lcd_wcmd(uchar cmd)
{                          
   while(check_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void lcd_wdat(uchar dat)
{                          
   while(check_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}

/**************************************
为加速逻辑运算而设置的掩码表，这是以牺牲空间而换取时间的办法
***************************************/
code unsigned int MaskTab[]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
							 0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};

/*****************************************
清除Lcd全屏，如果清除模式Mode为0，则为全屏清除为颜色0（无任何显示）
否则为全屏清除为颜色1(全屏填充显示)
******************************************/
void Lcd_Clear(unsigned char Mode)
{
	unsigned char x,y,ii;
	unsigned char Temp;
	if(Mode%2==0)
		Temp=0x00;
	else
		Temp=0xff;
	lcd_wcmd(0x36);//扩充指令 绘图显示
	for(ii=0;ii<9;ii+=8)   
		for(y=0;y<0x20;y++)     
			for(x=0;x<8;x++)
			{ 	
				EA=0;
				lcd_wcmd(y+0x80);        //行地址
				lcd_wcmd(x+0x80+ii);     //列地址     
				lcd_wdat(Temp); //写数据 D15－D8 
				lcd_wdat(Temp); //写数据 D7－D0 
				EA=1;
			}
	lcd_wcmd(0x30);
}							 
							 
/***************************************
向LCD指定坐标写入一个像素,像素颜色有两种，0代表白（无显示），1代表黑（有显示）
****************************************/
void Lcd_PutPixel(unsigned char x,unsigned char y)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64)//如果超出范围
		return;
	w=15-x%16;//确定对这个字的第多少位进行操作
	x=x/16;//确定为一行上的第几字

	if(y<32) //如果为上页
		z=0x80;
	else     //否则如果为下页
		z=0x88;

	y=y%32;
	EA=0;
	lcd_wcmd(0x36);
	lcd_wcmd(y+0x80);        //行地址
	lcd_wcmd(x+z);     //列地址 
	Temp=Lcd_ReadData();//先空读一次
	Temp=(unsigned int)Lcd_ReadData()<<8;//再读出高8位
	Temp|=(unsigned int)Lcd_ReadData();//再读出低8位
	EA=1;

	Temp|=MaskTab[w];//在此处查表实现加速

	EA=0;
	lcd_wcmd(y+0x80);        //行地址
	lcd_wcmd(x+z);     //列地址
    lcd_wdat(Temp>>8);//先写入高8位，再写入低8位
    lcd_wdat(Temp&0x00ff);
	lcd_wcmd(0x30);
	EA=1;
}

/***************************************
向LCD指定位置画一条长度为Length的指定颜色的水平线
****************************************/
void Lcd_HoriLine(unsigned char x,unsigned char y,unsigned char Length)
//确定初始坐标（x,y）和长度，以及颜色
{
	unsigned char i;
	if(Length==0)
		return;
	for(i=0;i<Length;i++)
	{
		Lcd_PutPixel(x+i,y);
	}
}

/***************************************
向LCD指定位置画一条长度为Length的指定颜色的垂直线
****************************************/
void Lcd_VertLine(unsigned char x,unsigned char y,unsigned char Length)
//确定初始坐标（x,y）和长度，以及颜色
{
	unsigned char i;
	if(Length==0)
		return;
	for(i=0;i<Length;i++)
	{
		Lcd_PutPixel(x,y+i);
	}
}
/*******************************************
画坐标轴
********************************************/
void coordinates()
{
//		 Lcd_HoriLine(0,0,127);//边框
//		 Lcd_HoriLine(0,63,127);
//		 Lcd_VertLine(0,0,63);
//		 Lcd_VertLine(127,0,63);
		 Lcd_HoriLine(0,31,128);//X轴
		 Lcd_VertLine(63,0,64);//Y轴
	
		 Lcd_PutPixel(62,1);//Y轴箭头
		 Lcd_PutPixel(61,2);
		 Lcd_PutPixel(64,1);
		 Lcd_PutPixel(65,2);
	
		 Lcd_PutPixel(126,30);//X轴箭头
		 Lcd_PutPixel(125,29);
		 Lcd_PutPixel(126,32);
		 Lcd_PutPixel(125,33);
	
		 Lcd_PutPixel(123,35);//X字样
		 Lcd_PutPixel(127,35);
		 Lcd_PutPixel(124,36);
		 Lcd_PutPixel(126,36);
		 Lcd_PutPixel(125,37);
		 Lcd_PutPixel(124,38);
		 Lcd_PutPixel(126,38);
		 Lcd_PutPixel(123,39);
		 Lcd_PutPixel(127,39);
		 
		 Lcd_PutPixel(67,1);//Y字样
		 Lcd_PutPixel(71,1);
		 Lcd_PutPixel(68,2);
		 Lcd_PutPixel(70,2);
		 Lcd_PutPixel(69,3);
		 Lcd_PutPixel(69,4);
		 Lcd_PutPixel(69,5);		 
	
}

/*******************************************
向LCD指定起始坐标和结束坐标之间画一条直线
********************************************/
//需要同时给定两个点的坐标，然后调用put_pixel函数
void Lcd_Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	unsigned int x,y; 
	unsigned int d_x,d_y;//d_x=x2-x1;d_y=y2-y1;
	int err=0;
	unsigned char temp=0;
	
	if(y2<y1)//互换值，确保y2更小
	{
		x=x1;
		y=y1;
		x1=x2;
		y1=y2;
		x2=x;
		y2=y;
	}
	d_y=y2-y1;
	if (d_y==0)//当y2==y1时
	{
		if (x1>x2) //确保x1较小
		{
			x=x1;
			x1=x2;
			x2=x;
		}
		for (x=x1;x<=x2;x++) 
			Lcd_PutPixel(x,y1);
      //从x1到x2范围内放置像素
	}

	else //当y2!=y1时
	{
		if(x2>=x1)
		{
			temp=1;
			d_x=x2-x1;
		}
		else 
			d_x=x1-x2;
		x=x1;
		y=y1;
		Lcd_PutPixel(x,y);

		if(temp&&(d_y<=d_x)) //如果x2>x1且y2-y1<=abs(x1-x2);
			while(x!=x2)
			{
				if(err<0)
				{
					x=x+1;
					err=err+(y2-y);
				}
				else 
				{
					x=x+1;
					y=y+1;
					err=err+(y2-y)-(x2-x);
				}
				Lcd_PutPixel(x,y);
			}

		else if(temp&&(d_y>d_x))
			while(y!=y2)
			{
				d_x=x2-x;
				d_y=y2-y; 
				if(err<0)
				{
					x=x+1;
					y=y+1;
					err=err+d_y-d_x;
				}
				else 
				{
					y=y+1;
					err=err-d_x;
				}
				Lcd_PutPixel(x,y);

			}

		else if(!temp&&(d_y<=d_x))
			while(x!=x2)
			{
				d_x=x-x2;
				d_y=y2-y; 
				if(err<0)
				{
					x=x-1;
					err=err+d_y;
				}
				else 
				{
					x=x-1;
					y=y+1;
					err=err+d_y-d_x;
				}
				Lcd_PutPixel(x,y);
			}

		else if(!temp &&(d_y>d_x))
			while(y!=y2)
			{
				d_x=x-x2;
				d_y=y2-y; 
				if(err<0)
				{
					x=x-1;
					y=y+1;
					err=err+d_y-d_x;
				}
				else 
				{
					y=y+1;
					err=err-d_x;
				}
				Lcd_PutPixel(x,y);
			}
	}
}


/****************************************
对称法画圆的8个镜像点
*****************************************/
void CircleDot(unsigned char x,unsigned char y,char xx,char yy)//内部函数，对称法画圆的8个镜像点
{
	Lcd_PutPixel((x+yy),(y+xx));//第 1 个 8 分圆
	Lcd_PutPixel((x+xx),(y+yy));//第 2 个 8 分圆
	Lcd_PutPixel((x-xx),(y+yy));//第 3 个 8 分圆
	Lcd_PutPixel((x-yy),(y+xx));//第 4 个 8 分圆
	Lcd_PutPixel((x-yy),(y-xx));//第 5 个 8 分圆
	Lcd_PutPixel((x-xx),(y-yy));//第 6 个 8 分圆
	Lcd_PutPixel((x+xx),(y-yy));//第 7 个 8 分圆
	Lcd_PutPixel((x+yy),(y-xx));//第 8 个 8 分圆
}

/******************************************
向LCD指定圆心坐标画一个半径为r的指定颜色的圆
*******************************************/
void Lcd_Circle(unsigned char x,unsigned char y,unsigned char r)//中点法画圆
{//中点法画圆
	unsigned char xx,yy;
	char deltax,deltay,d;
	xx=0;
	yy=r;
	deltax=3;
	deltay=2-r-r;
	d=1-r;
	
	CircleDot(x,y,xx,yy);//对称法画圆的8个镜像点
	while (xx<yy)
	{
		if (d<0)
		{
			d+=deltax;
			deltax+=2;
			xx++;
		}
		else
		{
			d+=deltax+deltay;
			deltax+=2;
			deltay+=2;
			xx++;
			yy--;
		}
		CircleDot(x,y,xx,yy);//对称法画圆的8个镜像点
	}
}
/****************************************
画正弦,余弦，y=x,圆
*****************************************/
void drawcurve(uchar num)
{
	uchar x0,y0,i,x1,y1;
	
	Lcd_Clear(0);
	coordinates();
	
	switch(num)
	{
		case 1: 
			      x0=0;
		        y0=31;
		        for(i=0;i<127;i++)
	           {
		           x1=i;
		           y1=31-(sin(i*0.1)*31);
		           Lcd_Line(x0,y0,x1,y1);
		           x0=i;
		           y0=y1;
	           }
						 break;
		case 2: 
			      x0=0;
		        y0=0;
			      for(i=0;i<127;i++)
	           {
	            	x1=i;
	             	y1=31-(cos(i*0.1)*31);
	            	Lcd_Line(x0,y0,x1,y1);
	            	x0=i;
	            	y0=y1;
	           }
						 break;
		case 3:Lcd_Line(31,63,95,0);break;//y=x
		case 4:Lcd_Line(31,0,95,63);break;//y=-x
		case 5:Lcd_Line(31,0,63,31);Lcd_Line(63,31,95,0);break;//y=|x|				 
		case 6:Lcd_Circle(63,31,31);break;
		case 7:
			      x0=29;
		        y0=0;
			      for(i=0;i<67;i++)
	           {
							  x1=31+i; 
							  if(i<32)
								{y1=31-2.7*pow((32-i)/10,2);}
								else
							  {y1=31-2.7*pow((i-32)/10,2);}
	            	Lcd_Line(x0,y0,x1,y1);
	            	x0=31+i;
	            	y0=y1;
	           }
						 break;
		case 8:
			      x0=29;
		        y0=63;
			      for(i=0;i<65;i++)
	           {
							  x1=31+i; 
							  if(i<32)
								{y1=31+0.95*pow((32-i)/10,3);}
								else
							  {y1=31-0.95*pow((i-32)/10,3);}
	            	Lcd_Line(x0,y0,x1,y1);
	            	x0=31+i;
	            	y0=y1;
	           }
						 break;						 
		default:break;
	}
}
	


 /*等待一个按键*/
void waitkey1()
{
	repeat:  
  	if (key1==1) goto repeat;
	else
	  flag_1=~flag_1;
	  lcd_wcmd(0x01);      //清除LCD的显示内容
	  delay(100);
}

 /*等待一个按键*/
void waitkey2()
{
	repeat:  
  	if (key2==1) goto repeat;
	else
	  flag_2=~flag_2;
	  lcd_wcmd(0x01);      //清除LCD的显示内容
	  delay(100);
}
 /*等待一个按键*/
void waitkey3()
{
	repeat:  
  	if (key3==1) goto repeat;
	else
	  flag_3=~flag_3;
	  lcd_wcmd(0x01);      //清除LCD的显示内容
	  delay(100);
}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //并口方式
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
	  //lcd_wcmd(0x0F);        //开光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}

/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   lcd_wcmd(pos);     //显示地址
}

/*******************************************
函数名称:Draw_PM
功    能:在整个液晶屏幕上画图
参    数:无
返回值  :无
********************************************/
void Draw_PM(const uchar *ptr)
{
    uchar i,j,k;
    wela=0;
	dula=0; 
	lcd_wcmd(0x34);        //打开扩展指令集
	i = 0x80;            
	for(j = 0;j < 32;j++)   //上半屏
	{
        lcd_wcmd(i++);
        lcd_wcmd(0x80);
  		for(k = 0;k < 16;k++)
  		{
  		    lcd_wdat(*ptr++);
  		}
	}
	i = 0x80;
 	for(j = 0;j < 32;j++)   //下半屏
	{
 	    lcd_wcmd(i++);
        lcd_wcmd(0x88);	   
  		for(k = 0;k < 16;k++)
  		{
   		    lcd_wdat(*ptr++);
   		} 
	}  
    lcd_wcmd(0x36);        //打开绘图显示
	lcd_wcmd(0x30);        //回到基本指令集
}




/*********************************************************

  串口数据显示函数

*********************************************************/
void  play()
{
	 uchar j;
	 j = 0;
	
   if(playflag)
   { 
     lcd_wcmd(0x01);      //清除LCD的显示内容
		 delay(5);
		 
		 lcd_pos(0,0);           //设置位置为第一行
		 
     for(m=0;m<16;m++)
     {
       lcd_wdat(RXDdata[m]);  //显示字符 
	     delay(5);
     }
		 
     playflag=0;              
     count=0x00;

     for(m=0;m<16;m++)      
     {
	 	  RXDdata[m]=0x20;         //清显存单元    
		  delay(5);
	   }
   }               
}

/*********************************************************

  发送数据函数

*********************************************************/
void senddata(uchar dat)
{
		 SBUF = dat;
     while(!TI);
     TI = 0;
}

//double get_num(int l,int r)//读取类似x.xxxx的浮点数
//{
//	double res;
//	int i,flagcur,cur1,cur2,cur2len,tmp,f=1;
//	char ch;
//	flagcur=cur1=cur2=cur2len=0;
//		for(i=l;i<r;i++){
//			ch=s[i];
//			if(ch>='0'&&ch<='9'){
//				tmp=ch-'0';
//				if(flagcur==0) cur1=cur1*10+tmp;
//				else{
//					cur2=cur2*10+tmp;cur2len++;
//				} 
//			}else if(s[i]=='.') flagcur=1;
//			else if(ch==')'){s[i]='#';break;}
//			else if(ch=='-') f=-1;
//			s[i]='#';
//		}
//		res = cur1;
//		if(cur2) res=res+cur2*pow(10,-cur2len);
//	return f*res;
//}

//double calc(){//计算部分
//	char ss[1000],ch;
//	int part1[1000],part2[1000];
//	double num1=0,num2=0;
//	int flagp;//flag priority
//	int flagcur,flag=0,cur1,cur2,cur2len,tmp,curl,curr;
//	double curnum1=0,curnum2=0;
//	//scanf("%s",&ss);
//	int len,cnt=0,cnt1=0,cnt2=0,flagnum2=0,flag1,flag2,flag3,flag4,l,r;
//	len=strlen(ss);
//	for(i=0;i<len;i++) s[i+1]=ss[i];len++;
//	for(i=1;i<len;i++){
//		if(s[i]=='s'){
//			if(s[i+1]=='i'&&s[i+2]=='n'&&s[i+3]=='('){
//				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
//				v[i]=sin(get_num(i+4,len));
//			}
//		}else if(s[i]=='c'){
//			if(s[i+1]=='o'&&s[i+2]=='s'&&s[i+3]=='('){
//				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
//				v[i]=cos(get_num(i+4,len));
//			}
//		}else if(s[i]=='t'){
//			if(s[i+1]=='a'&&s[i+2]=='n'&&s[i+3]=='('){
//				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
//				v[i]=tan(get_num(i+4,len));
//			}
//		}else if(s[i]=='e'){
//			if(s[i+1]=='x'&&s[i+2]=='p'&&s[i+3]=='('){
//				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
//				v[i]=exp(get_num(i+4,len));
//			}
//		}
//	}
//	
//	for(i=0;i<len;i++)//括号的位置 
//		if(s[i]==')') {
//			cnt++;part2[cnt]=i;
//			cnt1=1;
//			for(j=i-1;j>=0;j--){
//				if(s[j]==')') cnt1++;
//				else if(s[j]=='(') cnt1--;
//				if(!cnt1){part1[cnt]=j;break;}
//			}
//		}
//	cnt++;part1[cnt]=0;part2[cnt]=len;
//	for(k=1;k<=cnt;k++){
//		l=part1[k],r=part2[k];
//		s[l]=s[r]='#';l++; 
//		flagp=1;flag1=flag2=flag3=num1=num2=0;//初始化 
//		while(flagp){
//		flagp=0;
//		for(i=r-1;i>=l;i--){
//			if(s[i]=='^'){
//				flagp=flag1=1;flagcur=cur1=cur2=cur2len=curl=curr=0;
//				for(j=i-1;j>=l;j--)
//					if(s[j]=='+'||s[j]=='-'||s[j]=='*'||s[j]=='/'||s[j]=='^'){curl=j+1;break;}
//					else if(j==l) curl=j;
//				if(s[curl]=='#') curnum1=v[curl];
//				else{
//					for(j=curl;j<i;j++){
//						ch=s[j];
//						if(ch>='0' && ch<='9'){
//							tmp=ch-'0';
//							if(flagcur==0) cur1=cur1*10+tmp;
//							else{
//								cur2=cur2*10+tmp;cur2len++;
//							}
//						}else if(ch=='.') flagcur=1;
//						s[j]='#';
//					}
//					curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 符号左的数字
//				}
//				curr=i+1;flagcur=cur1=cur2=cur2len=0;
//				if(s[curr]=='#') curnum2=v[curr];
//				else{
//					for(j=curr;j<r;j++){
//						ch=s[j];
//						if(ch>='0' && ch<='9'){
//							tmp=ch-'0';
//							if(flagcur==0) cur1=cur1*10+tmp;
//							else{
//								cur2=cur2*10+tmp;cur2len++;
//							}
//						}else if(ch=='.') flagcur=1;
//						else{
//						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2符号右的数字
//						  break;
//						}
//						curnum2=cur1+cur2*pow(10,-cur2len);s[j]='#';
//					}
//				}
//				v[curl]=pow(curnum1,curnum2);
//				s[i]='#';break;
//			}
//		}
//	}
//	flagp=1;curnum1=curnum2=0;
//		while(flagp){
//		flagp=0;
//		for(i=l;i<r;i++){
//			if(s[i]=='*' || s[i]=='/'){
//				flagp=flag2=1;flagcur=cur1=cur2=cur2len=curl=curr=0;
//				for(j=i-1;j>=l;j--)
//					if(s[j]=='+'||s[j]=='-'){curl=j+1;break;}
//					else if(j==l) curl=j;
//				if(s[curl]=='#') curnum1=v[curl];
//				else{
//					for(j=curl;j<i;j++){
//						ch=s[j];
//						if(ch>='0' && ch<='9'){
//							tmp=ch-'0';
//							if(flagcur==0) cur1=cur1*10+tmp;
//							else{
//								cur2=cur2*10+tmp;cur2len++;
//							}
//						}else if(ch=='.') flagcur=1;
//						s[j]='#';
//					}
//					curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 符号左的数字
//				}
//				curr=i+1;flagcur=cur1=cur2=cur2len=0;
//				if(s[curr]=='#') curnum2=v[curr];
//				else{
//					for(j=curr;j<r;j++){
//						ch=s[j];
//						if(ch>='0' && ch<='9'){
//							tmp=ch-'0';
//							if(flagcur==0) cur1=cur1*10+tmp;
//							else{
//								cur2=cur2*10+tmp;cur2len++;
//							}
//						}else if(ch=='.') flagcur=1;
//						else{
//						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2符号右的数字
//						  break;
//						}
//						curnum2=cur1+cur2*pow(10,-cur2len);s[j]='#';
//					}
//				}
//				if(s[i]=='*') v[curl]=curnum1*curnum2;
//				else v[curl]=curnum1/curnum2;
//				s[i]='#';break;
//			}
//		}
//	}
//	flagp=1;
//	while(flagp){
//		flagp=0;
//		for(i=l;i<r;i++){
//			if(s[i]=='+' || s[i]=='-'){
//				flag3=1;//是否存在加减法 
//				flagp=1;flagcur=cur1=cur2=cur2len=curl=curr=0;
//				curl=l;
//				if(i==l && s[i]=='-') {
//					curnum1=0;
//				}else{
//					if(s[curl]=='#') curnum1=v[curl];
//					else{
//						for(j=curl;j<i;j++){
//							ch=s[j];
//							if(ch>='0' && ch<='9'){
//								tmp=ch-'0'; 
//								if(flagcur==0) cur1=cur1*10+tmp;
//								else{
//									cur2=cur2*10+tmp;cur2len++;
//								}
//							}else if(ch=='.') flagcur=1;
//							s[j]='#';
//						}
//						curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 符号左的数字
//					}
//				}
//				curr=i+1;flagcur=cur1=cur2=cur2len=0;
//				if(s[curr]=='#') curnum2=v[curr];
//				else{
//					for(j=curr;j<r;j++){
//						ch=s[j];
//						if(ch>='0' && ch<='9'){
//							tmp=ch-'0';
//							if(flagcur==0) cur1=cur1*10+tmp;
//							else{
//								cur2=cur2*10+tmp;cur2len++;
//							}
//						}else if(ch=='.') flagcur=1;
//						else{
//						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2符号右的数字
//						  break;
//						}
//						curnum2=cur1+cur2*pow(10,-cur2len);s[j]='#';
//					}
//				}
//				if(s[i]=='+') curnum1=curnum1+curnum2;
//				else curnum1=curnum1-curnum2;
//				num1+=curnum1;
//				s[i]='#';break;
//			}
//		}
//	}
//	if(!flag3 && (flag2 ||flag1)) num1=v[l];
//		l--;v[l]=num1;
//	}
//	flag4=0;
//	if(!flag3 && (flag2 || flag1)) num1=v[0];
//	if(!flag3 && !flag2 && !flag1){
//		flagcur=cur1=cur2=cur2len=0;
//		for(i=1;i<len;i++){
//			ch=s[i];
//			if(ch>='0'&&ch<='9'){
//				tmp=ch-'0';
//				if(flagcur==0) cur1=cur1*10+tmp;
//				else{
//					cur2=cur2*10+tmp;cur2len++;
//				} 
//			}else if(s[i]=='.') flagcur=1;
//			else if(s[i]=='#') flag4=1;
//		}
//		if(!flag4){
//			num1 = cur1;
//			if(cur2) num1=num1+cur2*pow(10,-cur2len);
//		}else num1=v[1];
//	}
//	return num1;
//}

//void sendchar(char ch)		//发送字符
//{
//	ES=0; 
//	SBUF=ch;
//	while(!TI);
//	TI=0;
//	ES=1;
//}
//void sendstr(char *str)	   //发送字符串
//{
//  ES=0; 
//  while(*str)
//  {
//    SBUF=*str;
//	while(!TI);
//	TI=0;
//	str++;
//  }
//  ES=1;
//}

/*********************************************************

  串行中断服务函数

*********************************************************/
void  serial() interrupt 4 
{
   ES = 0;                //关闭串行中断
   RI = 0;                //清除串行接受标志位
   buf = SBUF;            //从串口缓冲区取得数据
    				 

//	 if(flag_1)		 
//	 {
	     RXDdata[count]=buf;
       count++;	
//				ss[count]=buf;count++;
//			 	res=calc();
//		    sprintf(res_str,"%.3f",res);
//		    //sendstr(res_str);
//   } 
		playflag=1;
	  play();
	 	
	 if (flag_2)
	 {
      switch(buf)
     {
			 
		  case 0x73:	senddata('s');drawcurve(1);	break;//画sinx
		 	case 0x63:	senddata('c');drawcurve(2);	break;//画cosx
		 	case 0x78:	senddata('x');drawcurve(3);	break;//画y=x
		 	case 0x2D:	senddata('-');drawcurve(4);	break;//画y=-x
		 	case 0x7C:	senddata('|');drawcurve(5);	break;//画y=|x|			
			case 0x6F:	senddata('o');drawcurve(6);	break;//画圆
			case 0x32:	senddata('2');drawcurve(7);	break;//y=x^2
			case 0x33:	senddata('3');drawcurve(8);	break;//y=x^3
			
      default:    senddata(buf);break;  //接受到其它数据，将其发送给计算机         
     }
   }
	 else 
	  {senddata(buf);}


   ES = 1;    //允许串口中断
}