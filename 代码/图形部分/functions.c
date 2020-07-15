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
/*  ��ʱ����                                                       */
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
/*���LCDæ״̬                                                    */
/*lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ�      */
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
��LCD�ж�������
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
/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
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
/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
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
Ϊ�����߼���������õ�����������������ռ����ȡʱ��İ취
***************************************/
code unsigned int MaskTab[]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,
							 0x0100,0x0200,0x0400,0x0800,0x1000,0x2000,0x4000,0x8000};

/*****************************************
���Lcdȫ����������ģʽModeΪ0����Ϊȫ�����Ϊ��ɫ0�����κ���ʾ��
����Ϊȫ�����Ϊ��ɫ1(ȫ�������ʾ)
******************************************/
void Lcd_Clear(unsigned char Mode)
{
	unsigned char x,y,ii;
	unsigned char Temp;
	if(Mode%2==0)
		Temp=0x00;
	else
		Temp=0xff;
	lcd_wcmd(0x36);//����ָ�� ��ͼ��ʾ
	for(ii=0;ii<9;ii+=8)   
		for(y=0;y<0x20;y++)     
			for(x=0;x<8;x++)
			{ 	
				EA=0;
				lcd_wcmd(y+0x80);        //�е�ַ
				lcd_wcmd(x+0x80+ii);     //�е�ַ     
				lcd_wdat(Temp); //д���� D15��D8 
				lcd_wdat(Temp); //д���� D7��D0 
				EA=1;
			}
	lcd_wcmd(0x30);
}							 
							 
/***************************************
��LCDָ������д��һ������,������ɫ�����֣�0����ף�����ʾ����1����ڣ�����ʾ��
****************************************/
void Lcd_PutPixel(unsigned char x,unsigned char y)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64)//���������Χ
		return;
	w=15-x%16;//ȷ��������ֵĵڶ���λ���в���
	x=x/16;//ȷ��Ϊһ���ϵĵڼ���

	if(y<32) //���Ϊ��ҳ
		z=0x80;
	else     //�������Ϊ��ҳ
		z=0x88;

	y=y%32;
	EA=0;
	lcd_wcmd(0x36);
	lcd_wcmd(y+0x80);        //�е�ַ
	lcd_wcmd(x+z);     //�е�ַ 
	Temp=Lcd_ReadData();//�ȿն�һ��
	Temp=(unsigned int)Lcd_ReadData()<<8;//�ٶ�����8λ
	Temp|=(unsigned int)Lcd_ReadData();//�ٶ�����8λ
	EA=1;

	Temp|=MaskTab[w];//�ڴ˴����ʵ�ּ���

	EA=0;
	lcd_wcmd(y+0x80);        //�е�ַ
	lcd_wcmd(x+z);     //�е�ַ
    lcd_wdat(Temp>>8);//��д���8λ����д���8λ
    lcd_wdat(Temp&0x00ff);
	lcd_wcmd(0x30);
	EA=1;
}

/***************************************
��LCDָ��λ�û�һ������ΪLength��ָ����ɫ��ˮƽ��
****************************************/
void Lcd_HoriLine(unsigned char x,unsigned char y,unsigned char Length)
//ȷ����ʼ���꣨x,y���ͳ��ȣ��Լ���ɫ
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
��LCDָ��λ�û�һ������ΪLength��ָ����ɫ�Ĵ�ֱ��
****************************************/
void Lcd_VertLine(unsigned char x,unsigned char y,unsigned char Length)
//ȷ����ʼ���꣨x,y���ͳ��ȣ��Լ���ɫ
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
��������
********************************************/
void coordinates()
{
//		 Lcd_HoriLine(0,0,127);//�߿�
//		 Lcd_HoriLine(0,63,127);
//		 Lcd_VertLine(0,0,63);
//		 Lcd_VertLine(127,0,63);
		 Lcd_HoriLine(0,31,128);//X��
		 Lcd_VertLine(63,0,64);//Y��
	
		 Lcd_PutPixel(62,1);//Y���ͷ
		 Lcd_PutPixel(61,2);
		 Lcd_PutPixel(64,1);
		 Lcd_PutPixel(65,2);
	
		 Lcd_PutPixel(126,30);//X���ͷ
		 Lcd_PutPixel(125,29);
		 Lcd_PutPixel(126,32);
		 Lcd_PutPixel(125,33);
	
		 Lcd_PutPixel(123,35);//X����
		 Lcd_PutPixel(127,35);
		 Lcd_PutPixel(124,36);
		 Lcd_PutPixel(126,36);
		 Lcd_PutPixel(125,37);
		 Lcd_PutPixel(124,38);
		 Lcd_PutPixel(126,38);
		 Lcd_PutPixel(123,39);
		 Lcd_PutPixel(127,39);
		 
		 Lcd_PutPixel(67,1);//Y����
		 Lcd_PutPixel(71,1);
		 Lcd_PutPixel(68,2);
		 Lcd_PutPixel(70,2);
		 Lcd_PutPixel(69,3);
		 Lcd_PutPixel(69,4);
		 Lcd_PutPixel(69,5);		 
	
}

/*******************************************
��LCDָ����ʼ����ͽ�������֮�仭һ��ֱ��
********************************************/
//��Ҫͬʱ��������������꣬Ȼ�����put_pixel����
void Lcd_Line(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2)
{
	unsigned int x,y; 
	unsigned int d_x,d_y;//d_x=x2-x1;d_y=y2-y1;
	int err=0;
	unsigned char temp=0;
	
	if(y2<y1)//����ֵ��ȷ��y2��С
	{
		x=x1;
		y=y1;
		x1=x2;
		y1=y2;
		x2=x;
		y2=y;
	}
	d_y=y2-y1;
	if (d_y==0)//��y2==y1ʱ
	{
		if (x1>x2) //ȷ��x1��С
		{
			x=x1;
			x1=x2;
			x2=x;
		}
		for (x=x1;x<=x2;x++) 
			Lcd_PutPixel(x,y1);
      //��x1��x2��Χ�ڷ�������
	}

	else //��y2!=y1ʱ
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

		if(temp&&(d_y<=d_x)) //���x2>x1��y2-y1<=abs(x1-x2);
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
�ԳƷ���Բ��8�������
*****************************************/
void CircleDot(unsigned char x,unsigned char y,char xx,char yy)//�ڲ��������ԳƷ���Բ��8�������
{
	Lcd_PutPixel((x+yy),(y+xx));//�� 1 �� 8 ��Բ
	Lcd_PutPixel((x+xx),(y+yy));//�� 2 �� 8 ��Բ
	Lcd_PutPixel((x-xx),(y+yy));//�� 3 �� 8 ��Բ
	Lcd_PutPixel((x-yy),(y+xx));//�� 4 �� 8 ��Բ
	Lcd_PutPixel((x-yy),(y-xx));//�� 5 �� 8 ��Բ
	Lcd_PutPixel((x-xx),(y-yy));//�� 6 �� 8 ��Բ
	Lcd_PutPixel((x+xx),(y-yy));//�� 7 �� 8 ��Բ
	Lcd_PutPixel((x+yy),(y-xx));//�� 8 �� 8 ��Բ
}

/******************************************
��LCDָ��Բ�����껭һ���뾶Ϊr��ָ����ɫ��Բ
*******************************************/
void Lcd_Circle(unsigned char x,unsigned char y,unsigned char r)//�е㷨��Բ
{//�е㷨��Բ
	unsigned char xx,yy;
	char deltax,deltay,d;
	xx=0;
	yy=r;
	deltax=3;
	deltay=2-r-r;
	d=1-r;
	
	CircleDot(x,y,xx,yy);//�ԳƷ���Բ��8�������
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
		CircleDot(x,y,xx,yy);//�ԳƷ���Բ��8�������
	}
}
/****************************************
������,���ң�y=x,Բ
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
	


 /*�ȴ�һ������*/
void waitkey1()
{
	repeat:  
  	if (key1==1) goto repeat;
	else
	  flag_1=~flag_1;
	  lcd_wcmd(0x01);      //���LCD����ʾ����
	  delay(100);
}

 /*�ȴ�һ������*/
void waitkey2()
{
	repeat:  
  	if (key2==1) goto repeat;
	else
	  flag_2=~flag_2;
	  lcd_wcmd(0x01);      //���LCD����ʾ����
	  delay(100);
}
 /*�ȴ�һ������*/
void waitkey3()
{
	repeat:  
  	if (key3==1) goto repeat;
	else
	  flag_3=~flag_3;
	  lcd_wcmd(0x01);      //���LCD����ʾ����
	  delay(100);
}
/*******************************************************************/
/*                                                                 */
/*  LCD��ʼ���趨                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD_PSB = 1;         //���ڷ�ʽ
    
    lcd_wcmd(0x34);      //����ָ�����
    delay(5);
    lcd_wcmd(0x30);      //����ָ�����
    delay(5);
    lcd_wcmd(0x0C);      //��ʾ�����ع��
	  //lcd_wcmd(0x0F);        //�����
    delay(5);
    lcd_wcmd(0x01);      //���LCD����ʾ����
    delay(5);
}

/*********************************************************/
/*                                                       */
/* �趨��ʾλ��                                          */
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
   lcd_wcmd(pos);     //��ʾ��ַ
}

/*******************************************
��������:Draw_PM
��    ��:������Һ����Ļ�ϻ�ͼ
��    ��:��
����ֵ  :��
********************************************/
void Draw_PM(const uchar *ptr)
{
    uchar i,j,k;
    wela=0;
	dula=0; 
	lcd_wcmd(0x34);        //����չָ�
	i = 0x80;            
	for(j = 0;j < 32;j++)   //�ϰ���
	{
        lcd_wcmd(i++);
        lcd_wcmd(0x80);
  		for(k = 0;k < 16;k++)
  		{
  		    lcd_wdat(*ptr++);
  		}
	}
	i = 0x80;
 	for(j = 0;j < 32;j++)   //�°���
	{
 	    lcd_wcmd(i++);
        lcd_wcmd(0x88);	   
  		for(k = 0;k < 16;k++)
  		{
   		    lcd_wdat(*ptr++);
   		} 
	}  
    lcd_wcmd(0x36);        //�򿪻�ͼ��ʾ
	lcd_wcmd(0x30);        //�ص�����ָ�
}




/*********************************************************

  ����������ʾ����

*********************************************************/
void  play()
{
	 uchar j;
	 j = 0;
	
   if(playflag)
   { 
     lcd_wcmd(0x01);      //���LCD����ʾ����
		 delay(5);
		 
		 lcd_pos(0,0);           //����λ��Ϊ��һ��
		 
     for(m=0;m<16;m++)
     {
       lcd_wdat(RXDdata[m]);  //��ʾ�ַ� 
	     delay(5);
     }
		 
     playflag=0;              
     count=0x00;

     for(m=0;m<16;m++)      
     {
	 	  RXDdata[m]=0x20;         //���Դ浥Ԫ    
		  delay(5);
	   }
   }               
}

/*********************************************************

  �������ݺ���

*********************************************************/
void senddata(uchar dat)
{
		 SBUF = dat;
     while(!TI);
     TI = 0;
}

//double get_num(int l,int r)//��ȡ����x.xxxx�ĸ�����
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

//double calc(){//���㲿��
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
//	for(i=0;i<len;i++)//���ŵ�λ�� 
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
//		flagp=1;flag1=flag2=flag3=num1=num2=0;//��ʼ�� 
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
//					curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 �����������
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
//						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2�����ҵ�����
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
//					curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 �����������
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
//						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2�����ҵ�����
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
//				flag3=1;//�Ƿ���ڼӼ��� 
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
//						curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 �����������
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
//						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2�����ҵ�����
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

//void sendchar(char ch)		//�����ַ�
//{
//	ES=0; 
//	SBUF=ch;
//	while(!TI);
//	TI=0;
//	ES=1;
//}
//void sendstr(char *str)	   //�����ַ���
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

  �����жϷ�����

*********************************************************/
void  serial() interrupt 4 
{
   ES = 0;                //�رմ����ж�
   RI = 0;                //������н��ܱ�־λ
   buf = SBUF;            //�Ӵ��ڻ�����ȡ������
    				 

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
			 
		  case 0x73:	senddata('s');drawcurve(1);	break;//��sinx
		 	case 0x63:	senddata('c');drawcurve(2);	break;//��cosx
		 	case 0x78:	senddata('x');drawcurve(3);	break;//��y=x
		 	case 0x2D:	senddata('-');drawcurve(4);	break;//��y=-x
		 	case 0x7C:	senddata('|');drawcurve(5);	break;//��y=|x|			
			case 0x6F:	senddata('o');drawcurve(6);	break;//��Բ
			case 0x32:	senddata('2');drawcurve(7);	break;//y=x^2
			case 0x33:	senddata('3');drawcurve(8);	break;//y=x^3
			
      default:    senddata(buf);break;  //���ܵ��������ݣ����䷢�͸������         
     }
   }
	 else 
	  {senddata(buf);}


   ES = 1;    //�������ж�
}