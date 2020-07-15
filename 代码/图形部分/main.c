#include "config.h"
#include "functions.h"


uchar code dis1[] = {"     WELCOME!   "};
uchar code dis2[] = {"按下S2：计算模式"};
uchar code dis3[] = {"按下S3：图形模式"};
uchar code dis4[] = {"请使用串口输入:"};
uchar code dis5[] = {"按下S4：回主界面"};
uchar code dis6[] = {"    计算模式    "};
uchar code dis7[] = {"    图形模式    "};
uchar IRDIS[2];
uchar IRCOM[4];


void delay0(uchar x);  //x*0.14MS
void beep();
void  dataconv();


/*********************************************************/
/*														                           */
/*                         主程序                        */
/*                                                       */
/*********************************************************/

void  main()
 {
//		double res;
//		char res_str[100];


    uchar i;
    delay(10);                 //延时
	 
	  P0 = 0xff;
    P2 = 0xff;         
    
    SCON=0x50;           //设定串口工作方式
    PCON=0x00;           //波特率不倍增		
    TMOD=0x20;           //定时器1工作于8位自动重载模式, 用于产生波特率
    EA=1;
    ES = 1;              //允许串口中断
    TL1=0xfd;
    TH1=0xfd;             //波特率9600
    TR1=1;
	 
    wela=0;
	  dula=0; 
    lcd_init();                //初始化LCD             


	while(1)
	{
  ///////////////////////////////////////////////////////////////
  //	                       主界面                           ///
  ///////////////////////////////////////////////////////////////
    lcd_pos(0,0);             //设置显示位置为第一行的第1个字符
     i = 0;                                                    
    while(dis1[i] != '\0')                                     
     {                         //显示字符                      
       lcd_wdat(dis1[i]);                                      
       i++;                                                    
     }                                                         
    lcd_pos(1,0);             //设置显示位置为第二行的第1个字符
     i = 0;                                                    
    while(dis2[i] != '\0')                                     
     {                                                         
       lcd_wdat(dis2[i]);      //显示字符                      
       i++;                                                    
     }                                                         
 	 lcd_pos(2,0);             //设置显示位置为第三行的第1个字符 
     i = 0;                                                    
    while(dis3[i] != '\0')                                      
     {                                                          
       lcd_wdat(dis3[i]);      //显示字符                      
       i++;                                                    
     }                                                         
	 lcd_pos(3,0);             //设置显示位置为第四行的第1个字符 
     i = 0;                                                    
    while(dis5[i] != '\0')                                     
     {                                                         
       lcd_wdat(dis5[i]);      //显示字符                      
       i++;                                                    
     }                                                         
/////////////////////////////////////////////////////////////////
//                       主循环                               ///
/////////////////////////////////////////////////////////////////
		
			 waitkey1();		
		if(flag_1)                           //按下S2,进入计算模式
			 {
					   Lcd_Clear(0);
					  lcd_pos(0,0);             //设置显示位置为第四行的第1个字符
             i = 0;
             while(dis6[i] != '\0')
            {
             lcd_wdat(dis6[i]);      //显示字符
             i++;
            }
						lcd_pos(1,0);             //设置显示位置为第四行的第1个字符
             i = 0;
             while(dis4[i] != '\0')
            {
             lcd_wdat(dis4[i]);      //显示字符
             i++;
            }
						lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
             i = 0;
             while(dis5[i] != '\0')
            {
             lcd_wdat(dis5[i]);      //显示字符
             i++;
            }       
        waitkey1();						
				//	  play();
		    }

				
			 waitkey2();

//		if(flag_2)                           //按下S3,进入计算模式
//			 {				
//				    lcd_pos(0,0);             //设置显示位置为第四行的第1个字符
//                i = 0;
//              while(dis7[i] != '\0')
//              {
//              lcd_wdat(dis7[i]);      //显示字符
//              i++;
//              }
//						lcd_pos(1,0);             //设置显示位置为第四行的第1个字符
//             i = 0;
//             while(dis4[i] != '\0')
//            {
//             lcd_wdat(dis4[i]);      //显示字符
//             i++;
//            }
//				    lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
//              i = 0;
//              while(dis5[i] != '\0')
//             {
//              lcd_wdat(dis5[i]);      //显示字符
//              i++;
//             }
//						 delay(10);
//						 waitkey2();
//				}
			
			waitkey3();
	}	 
}