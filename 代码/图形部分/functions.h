#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

extern int   flag_1;
extern int   flag_2;
extern int   flag_3;
//extern double v[100],res;
//extern char s[100],ss[100],res_str[100],ch;
extern int i,j,k;
extern int  playflag;
void delay(int ms);//��ʱ������
void lcd_wdat(uchar dat);//д��ʾ���ݵ�LCD 
unsigned char Lcd_ReadData();//��LCD�ж�������
void Lcd_PutPixel(uchar x,uchar y);//��LCDָ������д��һ������,������ɫ�����֣�0����ף�����ʾ����1����ڣ�����ʾ��
void Lcd_HoriLine(uchar x,uchar y,uchar Length);//��LCDָ��λ�û�һ������ΪLength��ָ����ɫ��ˮƽ��
void Lcd_VertLine(uchar x,uchar y,uchar Length);//��LCDָ��λ�û�һ������ΪLength��ָ����ɫ�Ĵ�ֱ��
void coordinates();//��������
void Lcd_Line(uchar x1,uchar y1,uchar x2,uchar y2);//�ڣ�x1,y1���루x2,y2������仭��
void drawcurve(uchar num);//����1,����2
void Lcd_Circle(uchar x,uchar y,uchar r);//�ԣ�x,y��ΪԲ�ģ�rΪ�뾶��Բ
void Lcd_Clear(uchar Mode);//���Lcdȫ����ModeΪ0�����κ���ʾ;����ȫ�������ʾ
void waitkey1();//�ȴ�һ���������������ģʽ
void waitkey2();//�ȴ�һ������������ͼ��ģʽ
void waitkey3();//�ȴ�һ���������������˵�
void lcd_init();//  LCD��ʼ���趨
void lcd_pos(uchar X,uchar Y);// �趨��ʾλ�� 
void Draw_PM(const uchar *ptr);//������Һ����Ļ�ϻ�ͼ
void play();//����������ʾ����
//double get_num(int l,int r);//��ȡ����x.xxxx�ĸ�����
//double calc();//����
//void sendstr(char *str);	   //�����ַ���


#endif