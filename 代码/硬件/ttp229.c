#include <STC8.H>
#include <intrins.h>
  sbit scl=P6^3;
  sbit sdo=P6^2;
//sbit scl=P3^4;
//sbit sdo=P3^5;

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}
void Delay2us()		//@11.0592MHz
{
	unsigned char i;

	i = 3;
	while (--i);
}

void Delay500ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 46;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
void UartInit(void)		//9600bps@24.000MHz
{
	SCON = 0x50;		//8浣嶆暟鎹?鍙彉娉㈢壒鐜?
	AUXR |= 0x40;		//瀹氭椂鍣?鏃堕挓涓篎osc,鍗?T
	AUXR &= 0xFE;		//涓插彛1閫夋嫨瀹氭椂鍣?涓烘尝鐗圭巼鍙戠敓鍣?
	TMOD &= 0x0F;		//璁惧畾瀹氭椂鍣?涓?6浣嶈嚜鍔ㄩ噸瑁呮柟寮?
	TL1 = 0x8F;		//璁惧畾瀹氭椂鍒濆€?
	TH1 = 0xFD;		//璁惧畾瀹氭椂鍒濆€?
	ET1 = 0;		//绂佹瀹氭椂鍣?涓柇
	TR1 = 1;		//鍚姩瀹氭椂鍣?
	ES = 1;
	EA = 1;
	TI = 0;
}
unsigned char ttp229_write(void)
{
	unsigned char i;
	unsigned char temp=0;
	sdo=0;
	Delay10us();
	sdo=1;
	Delay2us();
	temp=0;
	for(i=0;i<=15;i++)
	{
		temp>>=1;
		scl=1;
		if(!sdo)
			temp|=0x80;
		scl=0;
	}        
return temp;
}

int ttp229b2(void){
	int i,num=0;
		if(sdo){
			Delay10us();
			for(i=1;i<=16;i++){
				scl=1;
				Delay2us();
				scl=0;
				if(sdo){
					num = i;
				}
			}
		}
		if(num>=1&&num<=16) return num;
}

void main(void)
{
	int num=0,num1=0;
	unsigned char k1=0x31,k2=0x31;
	UartInit();Delay500ms();
	while(1)
	{
		num = ttp229b2();
		if(num!=num1){SBUF = num;while(!TI);TI=0;num1 = num;}
		if(sdo){SBUF = k1;while(!TI);TI=0;}
  }
}
