#include <stdio.h>
#include <math.h>

long double function(long double x)
{
    long double y;
    y = x*x;
    
return y;
}

float djf(float a,float b)
{
    unsigned long long N=1000000;
    int i;
    float result=0;
    for(i=0;i<N;i++)
    {
        float u;
        u=0.5*(a + ((b - a) / N) * i)+0.5*(a + ((b - a) / N) * (i+1));
        result=result + function(u)*(b-a)/N;
    }
    return result;
}

void main()
{
    float x;
    x=djf(0,3);
    printf("%f",x);
}
