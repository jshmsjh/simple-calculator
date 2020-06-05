//求函数在某一点的微分
#include <stdio.h>
#include <math.h> 

double f(double x,double y)
{  
    y=2*x*x+3;
    return y;
} 

double  differential(double x0)
{  
    long double dx,dy,dd1,dd2,x,y,x0,eps;
    dx=0.5,x0=3,eps=0.000001,dy=0.0;
    dy=f(x0,y)-f(x0+dx,y);
    dd1=dy/dx;
    loop:dx=0.5*dx;
    dy=f(x,y)-f(x+dx,y);
    dd2=dy/dx;
     if (fabs(dd1-dd2)<eps) 
         return dd2;
     else
         {
            dd1=dd2;      
            goto loop;
         } 
}