//解比例式
//变量x分别位于两种位置
#include <stdio.h>
#include <math.h>
 
//计算a:b=c:x 
double proportion(double a, double b, double c, double x)
{
	printf("计算比例式a:b=c:x中的x，请依次输入a、b、c\n");
	scanf("%lf%lf%lf", &a, &b, &c) ;
	x = b*c/a;
	printf("x=%lf",x);
} 

//计算a:b=x:c 
double proportion(double a, double b, double c, double x)
{
	printf("计算比例式a:b=x:c中的x，请依次输入a、b、c\n");
	scanf("%lf%lf%lf", &a, &b, &c) ;
	x = a*c/b;
	printf("x=%lf",x);
} 


int main()
{
	double a,b,c,x;
	printf("%lf",proportion(a,b,c,x));
}
