#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

extern int   flag_1;
extern int   flag_2;
extern int   flag_3;
//extern double v[100],res;
//extern char s[100],ss[100],res_str[100],ch;
extern int i,j,k;
extern int  playflag;
void delay(int ms);//延时几毫米
void lcd_wdat(uchar dat);//写显示数据到LCD 
unsigned char Lcd_ReadData();//从LCD中读出数据
void Lcd_PutPixel(uchar x,uchar y);//向LCD指定坐标写入一个像素,像素颜色有两种，0代表白（无显示），1代表黑（有显示）
void Lcd_HoriLine(uchar x,uchar y,uchar Length);//向LCD指定位置画一条长度为Length的指定颜色的水平线
void Lcd_VertLine(uchar x,uchar y,uchar Length);//向LCD指定位置画一条长度为Length的指定颜色的垂直线
void coordinates();//画坐标轴
void Lcd_Line(uchar x1,uchar y1,uchar x2,uchar y2);//在（x1,y1）与（x2,y2）两点间画线
void drawcurve(uchar num);//正弦1,余弦2
void Lcd_Circle(uchar x,uchar y,uchar r);//以（x,y）为圆心，r为半径画圆
void Lcd_Clear(uchar Mode);//清除Lcd全屏，Mode为0，无任何显示;否则全屏填充显示
void waitkey1();//等待一个按键，进入计算模式
void waitkey2();//等待一个按键，进入图形模式
void waitkey3();//等待一个按键，返回主菜单
void lcd_init();//  LCD初始化设定
void lcd_pos(uchar X,uchar Y);// 设定显示位置 
void Draw_PM(const uchar *ptr);//在整个液晶屏幕上画图
void play();//串口数据显示函数
//double get_num(int l,int r);//读取类似x.xxxx的浮点数
//double calc();//计算
//void sendstr(char *str);	   //发送字符串


#endif