//进行积分运算 
//分别使用矩形法、梯形法、辛普生法、高斯法
#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
#include <time.h>
#define N       3  


//输入需要计算的函数
double fun(double x)
{
    return x*2; //此处输入f（x） 
}


//矩形法 
double integral(double (*fun)(double), double xmin, double xmax, int n)
{
    printf("请依次输入积分下限、上限、积分区间分成的份数\n");
	scanf("%lf%lf%d", &xmin, &xmax, &n);
	
    double ans = 0;
    double i;
    double len = (xmax - xmin) / n;
	
    for (i = xmin; i < xmax; i += len)
    {
        ans += len * (*fun)(i);
    }
    
    printf("%lf\n", ans);
    return 0;
}
//梯形法 
double integral(double (*fun)(double), double xmin, double xmax, int n)
{  
	printf("请依次输入积分下限、上限、积分区间分成的份数\n");
	scanf("%lf%lf%d", &xmin, &xmax, &n);
	
    double h, s;  
    int i = 0;  
    h = (xmax-xmin)/n;  
    s = 0.5*(fun(xmin)+fun(xmin+h))*h;  
    
    for (i=1; i<n; i++)  
    {  
        s = s + 0.5 * (fun(xmin+i*h) + fun(xmin+(i+1)*h))*h;  
    }  
    
    return s;     
}   
//辛普生法 S[n]=(4*T[2*s]-T[s])/3，其中T[2s],T[s]为梯形法计算结果
double integral(double (*fun)(double), double xmin, double xmax, int n)
{  
    printf("请依次输入积分下限、上限、积分区间分成的份数\n");
	scanf("%lf%lf%d", &xmin, &xmax, &n);
	
    double s;  
    s = (4*T(xmin, xmax, 2*n) - T(xmin, xmax, n))/3;  
    return s;     
}  
//矩形法 梯形法 辛普生法example 
int main()
{
	double xmin, xmax;
    int n;
    printf("%lf\n", integral(fun, xmin, xmax, 1000));
    return 0;
} 


// 上方为三种方法和主函数 以下为高斯法和其主函数 


//高斯法  
double Gass(double (*func)(double x), double a, double b, int n)  
{  
    printf("积分下限:\n");  
    scanf("%lf", &a);  
    printf("积分上限:\n");  
    scanf("%lf", &b);  
    printf("分隔数目（1-5）:\n");  
    scanf("%d", &n); 
    int i = 0;  

    //高斯点及其求积系数列表  
    float x1[1]={0.0};                                                    
    float A1[1]={2};  
    float x2[2]={-0.5573503,0.5573503};                                  
    float A2[2]={1,1};  
    float x3[3]={-0.7745967,0.0,0.7745967};                               
    float A3[3]={0.555556,0.888889,0.555556};  
    float x4[4]={0.3399810,-0.3399810,0.8611363,-0.8611363};              
    float A4[4]={0.6521452,0.6521452,0.3478548,0.3478548};  
    float x5[5]={0.0,0.5384693,-0.5384693,0.9061799,-0.9061799};         
    float A5[5]={0.5688889,0.4786287,0.4786287,0.2369269,0.2369269};     
    
	float *p, *t;  //不同的分隔选择 1-5 
    switch (n)  
    {  
        case 1:            
            p = x1;  
            t = A1;  
            break;  
        case 2:            
            p = x2;  
            t = A2;  
            break;  
        case 3:            
            p = x3;  
            t = A3;  
            break;  
        case 4:            
            p = x4;  
            t = A4;  
            break;  
        case 5:            
            p = x5;  
            t = A5;  
            break;  
        default :     
            printf("intput wrong");  
    }  
    float g = 0;  
    
	for (i=0; i<n; i++)  
    {  
        g += (*func)((b-a)*p[i]/2+(a+b)/2)*t[i];  
    }   
    g *= (b-a)/2;  
      
    return g;  
}
//高斯法 example
int main()  
{      
    double a, b;  
    int n;  
    printf("%0f\n",Gass(fun, a, b, 1000));   
    return 0;  
}  
