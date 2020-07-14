	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>
    #define uchar unsigned char
	#define uint unsigned int
	#define ulint unsigned long int


    typedef struct polar_y{
	double magnitude;//与极点的距离
    double angle;//角度
    }POLAR_V;
 
    typedef struct rect_v{
    double x;
    double y;
    }RECT_V;


	//计算排列数A(m,n)=n!/m! 
    int a(int m,int n)
	{
    return (jc(n)/jc(n-m));    
    }

    //计算组合数
    int c(int m,int n)
	{
    return (jc(n))/(jc(m)*jc(n-m));
    } 

	//计算n的阶乘 
    int jc(int n)
	{
      int i,res=1;
      for(i=1;i<=n;i++)
	  {
        res=res*i;
      } 
      return res;
    }

    //生成m到n的随机数
	int getrandom(int Max,int Min)
	{
	  int t=0;
	  srand(time(NULL));
	  t = (rand()%(MAX - MIN)) + MIN;
          return t;
	}

  
    //极坐标转直角坐标
	RECT_V polay_to_rect(POLAR_V pv)
	{
		int PI = 3.1415926;
		RECT_V rv;
		rv.x = pv.magnitude*cos(pv.angle*PI /180);
        rv.y = pv.magnitude*sin(pv.angle*PI /180);
		return rv;
	}

	//直角坐标转极坐标
    POLAR_V rect_to_polar(RECT_V rv)
    {	
		POLAR_V pv;
		pv.magnitude = sqrt(rv.x*rv.x+rv.y*rv.y);//开根
		if(pv.magnitude==0)//位于极点	
			pv.angle=0.0;	
		else		
		    pv.angle=RAD_TO_DEG * atan2(rv.y, rv.x);//atan2()返回弧度值，此为转换为角度的公式
		return pv;
	}
