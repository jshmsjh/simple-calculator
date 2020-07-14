//表格功能
//以表格的形式输出两个函数的值，自变量组成等差数列
#include <stdio.h>

//定义函数 y1 
double y_1(double x,double f)
{
  	f = x*x; //此处输入f(X)
    return f;
}

//定义函数 y2 
double y_2(double x,double g)
{
  	g = x/2; //此处输入g(x) 
    return g;
}

//表格函数 
double chart(double f, double g)
{	
        double x;double xt;double d;
	printf("请输入表格自变量的起点x、终点xt、步长d\n");
	scanf("%lf%lf%lf", &x,&xt,&d);
	printf("x\t \t \t  f(x)\t \t \t  g(x)\n");
	for(x; x <= xt; x = x + d)
	{	
		printf("%lf\t \t |%lf\t \t |%lf\n", x, y_1(x,f), y_2(x,g));
	}
	return 0; 
}

int main()
{
	double x,xt,d,f,g;
	printf("%lf",chart(f,g));
	
}
