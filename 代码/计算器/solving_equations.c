#include <stdio.h>
#include <math.h>

/*一元一次方程*/
void one_one(float a,float b)
{
    float x;
    x=(-b)/a;
    printf("x=%f\n",x);
}

/*一元二次方程*/
void one_two(float a,float b,float c)
{
    float x1;float x2;
    float delta;
    delta=b*b-4*a*c;
    if(delta>0)
    {
        x1=(-b+sqrt(delta))/(2*a);
        x2=(-b-sqrt(delta))/(2*a);
        printf("x1=%f,x2=%f\n",x1,x2);
    }
    else if(delta==0)
    {
        x1=(-b)/(2*a);
        printf("x1=x2=%f\n",x1);
    }
    else
    {
        float p=-b/(2*a);
        float q=sqrt(-delta)/(2*a);
        printf("x1=%f+%fi,x2=%f-%fi\n",p,q,p,q);
    }
}

/*一元三次方程*/
void one_three(float a,float b,float c,float d)                   //ax3+bx2+cx+d=0
{
    float p=(3*a*c-b*b)/(3*a*a);
    float q=(27*a*a*d-9*a*b*c+2*b*b*b)/(27*a*a*a);
    float w_real=-0.5;
    float w_imag=sqrt(3)/2;
    float w2_real=-0.5;
    float w2_imag=(-sqrt(3))/2;
    float s;float t;float delta;
    delta=pow(q/2,2)+pow(p/3,3);
    printf("%f\n",delta);
    delta=sqrt(pow(q/2,2)+pow(p/3,3));
    if((delta-q/2)<0)
    {
        if((-delta-q/2)<0)
        {
            s=-pow(q/2-delta,1.0/3);
            t=-pow(q/2+delta,1.0/3);
        }
        else
        {
            s=-pow(q/2-delta,1.0/3);
            t=pow(-q/2-delta,1.0/3);
        }
    }
    else
    {
        if((-delta-q/2)<0)
        {
            s=pow(-q/2+delta,1.0/3);
            t=-pow(q/2+delta,1.0/3);
        }
        else
        {
            s=pow(-q/2+delta,1.0/3);
            t=pow(-q/2-delta,1.0/3);
        }
    }
    if( delta<0 || abs(delta)<(1e-5))                                    //有三个实数解
    {
        float x1=s+t-b/(3*a);
        float x2=w_real*s+w2_real*t-b/(3*a);
        float x3=w2_real*s+w_real*t-b/(3*a);
        printf("x1=%f,x2=%f,x3=%f\n",x1,x2,x3);
    }
    else                                           //有一个实数解，两个复数
    {
        float x1=s+t-b/(3*a);
        float x2_real=w_real*s+w2_real*t-b/(3*a);
        float x2_imag=w_imag*s+w2_imag*t;
        float x3_real=w2_real*s+w_real*t-b/(3*a);
        float x3_imag=w2_imag*s+w_imag*t;
        printf("x1=%f,x2=%f+%f*i,x3=%f+%f*i\n",x1,x2_real,x2_imag,x3_real,x3_imag);
    }
}

/*一元四次方程*/
void one_four(float a,float b,float c,float d,float e)
{
    float b1=-c/a;
    float c1=(b*d)/(a*a)-(4*e)/a;
    float d1=(4*c*e-d*d)/(a*a)-(b*b*e)/(a*a*a);
    float y;
    float p=(3*c1-b1*b1)/3;                       //求y的实数根
    float q=(27*d1-9*b1*c1+2*b1*b1*b1)/27;
    float delta=sqrt(pow(q/2,2)+pow(p/3,3));
    float s;float t;
    if((delta-q/2)<0)
    {
        if((-delta-q/2)<0)
        {
            s=-pow(q/2-delta,1.0/3);
            t=-pow(q/2+delta,1.0/3);
        }
        else
        {
            s=-pow(q/2-delta,1.0/3);
            t=pow(-q/2-delta,1.0/3);
        }
    }
    else
    {
        if((-delta-q/2)<0)
        {
            s=pow(-q/2+delta,1.0/3);
            t=-pow(q/2+delta,1.0/3);
        }
        else
        {
            s=pow(-q/2+delta,1.0/3);
            t=pow(-q/2-delta,1.0/3);
        }
    }
    if( delta<0 || abs(delta)<(1e-5))        
    {
        y=s+t-b1/3;
    }
    else         
    {
        y=s+t-b1/3;
    }
    float m=b/(2*a)-sqrt((b*b)/(4*a*a)-c/a+y);
    float n1=0.5*y+sqrt(0.25*y*y-c/a);
    float n2=0.5*y-sqrt(0.25*y*y-c/a);
    float x1;float x2;float x3;float x4;
    float de1;float de2;
    de1=m*m-4*n1;
    de2=m*m-4*n2;
    if(de1>0)
    {
        x1=(-m+sqrt(de1))/2;
        x2=(-m-sqrt(de1))/2;
        printf("x1=%f,x2=%f,",x1,x2);
    }
    else if(de1==0)
    {
        x1=(-m)/2;
        printf("x1=x2=%f,",x1);
    }
    else
    {
        float r1=-m/2;
        float r2=sqrt(-de1)/2;
        printf("x1=%f+%fi,x2=%f-%fi,",r1,r2,r1,r2);
    }
    if(de2>0)
    {
        x3=(-m+sqrt(de2))/2;
        x4=(-m-sqrt(de2))/2;
        printf("x3=%f,x4=%f\n",x3,x4);
    }
    else if(de2==0)
    {
        x3=(-m)/2;
        printf("x3=x4=%f\n",x3);
    }
    else
    {
        float r1=-m/2;
        float r2=sqrt(-de2)/2;
        printf("x3=%f+%fi,x4=%f-%fi\n",r1,r2,r1,r2);
    }
}

/*二元一次方程*/
void two_one(float a1,float b1,float c1,float a2,float b2,float c2)
{
    float k=a1*b2-a2*b1;
    if(k==0)
    {
        float s1=c1/a1;float s2=c2/a2;
        if(s1==s2)
        {
            float p=-(a1+c1)/b1;
            printf("有无数个解,其中x=%fy,y∈C\n",p);
        }
        else
        {
            printf("%s","方程无解");
        }
    }
    else
    {
        float x;float y;
        x=(c2*b1-c1*b2)/(a1*b2-a2*b1);
        y=(a1*c2-a2*c1)/(a2*b1-a1*b2);
        printf("x=%f,y=%f\n",x,y);
    }
}

/*三次行列式的展开*/
float three(float a1,float b1,float c1,float a2,float b2,float c2,float a3,float b3,float c3)
{
    float D;
    D=a1*b2*c3-a3*b2*c1+a3*b1*c2-a1*b3*c2+a2*b3*c1-a2*b1*c3;
    return D;
}

/*三元一次方程*/
void three_one(float a1,float b1,float c1,float d1,float a2,float b2,float c2,float d2,float a3,float b3,float c3,float d3)
{
    float D;
    D=three(a1,b1,c1,a2,b2,c2,a3,b3,c3);
    float x;float y;float z;
    if(D==0)
    {
        float k1;
        k1=a1*b2-a2*b1;
        if(k1==0)
        {
            float k2;
            k2=a1*b3-a3*b1;
            if(k2==0)
            {
                float s1=(d1-c1)/a1;float s2=(d2-c2)/a2;float s3=(d3-c3)/a3;
                if(s1==s2 & s2==s3)
                {
                    float p1;float p2;float p3;
                    p1=d1/a1;
                    p2=b1/a1;
                    p3=c1/a1;
                    printf("有无数个解，其中x=%f-%fy-%fz,y∈C，z∈C\n",p1,p2,p3);
                }
               else
               {
                   printf("%s","方程无解");
               }
            }
            else
            {
                float s1=(d1-c1)/a1;float s2=(d2-c2)/a2;
                if(s1==s2)
                {
                    float p1;float p2;
                    p1=(b3*d1-b1*d3)/k2;
                    p2=(b1*c3-b3*c1)/k2;
                    float q1;float q2;
                    q1=(d1-a1*p1)/b1;
                    q2=(c1+a1*p2)/b1;
                    printf("有无数个解，其中x=%f+%fz,y=%f-%fz,z∈C\n",p1,p2,q1,q2);
                }
                else
                {
                    printf("%s","方程无解");
                }
            }
        }
        else
        {
            float k2;
            k2=a1*b3-a3*b1;
            if(k2==0)
            {
                float s1=(d1-c1)/a1;
                float s2=(d3-c3)/a3;
                if(s1==s2)
                {
                    float p1;float p2;
                    p1=(b2*d1-b1*d2)/k1;
                    p2=(b1*c2-b2*c1)/k1;
                    float q1;float q2;
                    q1=(d1-a1*p1)/b1;
                    q2=(c1+a1*p2)/b1;
                    printf("有无数个解，其中x=%f+%fz,y=%f-%fz,z∈C\n",p1,p2,q1,q2);
                }
                else
                {
                    printf("%s","方程无解");
                }
            }
            else
            {
                float s1=(d2-c2)/a2;
                float s2=(d3-c3)/a3;
                if(s1==s2)
                {
                    float p1;float p2;
                    p1=(b2*d1-b1*d2)/k1;
                    p2=(b1*c2-b2*c1)/k1;
                    float q1;float q2;
                    q1=(d1-a1*p1)/b1;
                    q2=(c1+a1*p2)/b1;
                    printf("有无数个解，其中x=%f+%fz,y=%f-%fz,z∈C\n",p1,p2,q1,q2);
                }
                else
                {
                    printf("%s","方程无解");
                }
            }
        }
    }
    else if(D!=0)
    {
        float D1;float D2;float D3;
        D1=three(d1,b1,c1,d2,b2,c2,d3,b3,c3);
        D2=three(a1,d1,c1,a2,d2,c2,a3,d3,c3);
        D3=three(a1,b1,d1,a2,b2,d2,a3,b3,d3);
        x=D1/D;
        y=D2/D;
        z=D3/D;
        printf("方程有唯一解，x=%f,y=%f,z=%f\n",x,y,z);
    }
}

/*四元一次方程*/
void four_one(float a1,float b1,float c1,float d1,float e1,float a2,float b2,float c2,float d2,float e2,float a3,float b3,float c3,float d3,float e3,float a4,float b4,float c4,float d4,float e4)
{
    float D;
    D=a1*three(b2,c2,d2,b3,c3,d3,b4,c4,d4)-a2*three(b1,c1,d1,b3,c3,d3,b4,c4,d4)+a3*three(b1,c1,d1,b2,c2,d2,b4,c4,d4)-a4*three(b1,c1,d1,b2,c2,d2,b3,c3,d3);
    float k1=three(a1,b1,c1,a2,b2,c2,a3,b3,c3);
    float k2=three(a1,b1,c1,a2,b2,c2,a4,b4,c4);
    float k3=three(a1,b1,c1,a3,b3,c3,a4,b4,c4);
    float k4=three(a2,b2,c2,a3,b3,c3,a4,b4,c4);
    float s1=(e1-d1)/a1;
    float s2=(e2-d2)/a2;
    float s3=(e3-d3)/a3;
    float s4=(e4-d4)/a4;
    float x;
    float y;
    float z;
    float t;
    if(D==0)
    {
        if(k1==0)
        {
            if(k2==0 & k3==0 & k4==0)
            {
                if(s1==0 & s2==0 & s3==0 & s4==0)
                {
                    float p1=e1/a1;
                    float p2=b1/a1;
                    float p3=c1/a1;
                    float p4=d1/a1;
                    printf("有无数个解，其中x=%f-%fy-%fz-%ft,y∈C,z∈C,t∈C\n",p1,p2,p3,p4);
                }
                else 
                {
                    printf("%s","方程无解");
                }
            }
        }
        else
        {
            if(k2==0)
            {
                float r1=a1*b4-b1*a4;
                float r2=a1*c4-a4*c1;
                if(r1==0 & r2==0)
                {
                    if(s1==s4)
                    {
                        printf("有无数个解");
                    }
                    else
                    {
                        printf("%s","方程无解");
                    }
                }
                else if(r1!=0 || r2!=0)
                {
                    if(s2==s4)
                    {
                        printf("有无数个解");
                    }
                    else
                    {
                        printf("%s","方程无解");
                    }
                }
            }
            else if(k3==0)
            {
                float r1=a1*b4-b1*a4;
                float r2=a1*c4-a4*c1;
                if(r1==0 & r2==0)
                {
                    if(s1==s4)
                    {
                        printf("有无数个解");
                    }
                    else
                    {
                        printf("%s","方程无解");
                    }
                }
                else if(r1!=0 || r2!=0)
                {
                    if(s3==s4)
                    {
                        printf("有无数个解");
                    }
                    else
                    {
                        printf("%s","方程无解");
                    }
                }
            }
        }
    }
    else
    {
        float D1;float D2;float D3;float D4;
        D1=e1*three(b2,c2,d2,b3,c3,d3,b4,c4,d4)-e2*three(b1,c1,d1,b3,c3,d3,b4,c4,d4)+e3*three(b1,c1,d1,b2,c2,d2,b4,c4,d4)-e4*three(b1,c1,d1,b2,c2,d2,b3,c3,d3);
        D2=a1*three(e2,c2,d2,e3,c3,d3,e4,c4,d4)-a2*three(e1,c1,d1,e3,c3,d3,e4,c4,d4)+a3*three(e1,c1,d1,e2,c2,d2,e4,c4,d4)-a4*three(e1,c1,d1,e2,c2,d2,e3,c3,d3);
        D3=a1*three(b2,e2,d2,b3,e3,d3,b4,e4,d4)-a2*three(b1,e1,d1,b3,e3,d3,b4,e4,d4)+a3*three(b1,e1,d1,b2,e2,d2,b4,e4,d4)-a4*three(b1,e1,d1,b2,e2,d2,b3,e3,d3);
        D4=a1*three(b2,c2,e2,b3,c3,e3,b4,c4,e4)-a2*three(b1,c1,e1,b3,c3,e3,b4,c4,e4)+a3*three(b1,c1,e1,b2,c2,e2,b4,c4,e4)-a4*three(b1,c1,e1,b2,c2,e2,b3,c3,e3);
        x=D1/D;y=D2/D;z=D3/D;t=D4/D;
        printf("方程有唯一解，x=%f,y=%f,z=%f,t=%f\n",x,y,z,t);
    }
}



void main(void)
{
    one_one(2,7);
    one_two(1,3,10);
    one_three(1,0,0,-1);
    one_three(1,3,3,1);
    one_three(1,2,-7,4);
    two_one(2,3,0,4,6,0);
    two_one(2,4,7,3,5,0);
    three_one(1,2,3,4,4,5,6,7,3,4,5,7);
    
    one_four(1,4,6,2,5);
}
