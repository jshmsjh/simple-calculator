#include <stdio.h>
#include <math.h>

float e[]; //储存上一步的结果

       /*一个向量的计算*/
/*数乘*/
void multi(float k,float e1[],int e1_info)
{
    int i;
    if(e1_info==2)
    {
        e[0]=k*e1[0];
        e[1]=k*e1[1];
        printf("(%f,%f)\n",e[0],e[1]);
    }
    else if(e1_info==3)
    {
        for(i=0;i<=3;i++)
        {
            e[i]=k*e1[i];
        }
        printf("(%f,%f,%f)\n",e[0],e[1],e[2]);
    }
    else
    {
        printf("%s\n","out of range");
    }
}

/*向量的模*/
void module(float e1[],int e1_info)
{
    if(e1_info==2)
    {
        e[0]=sqrt(pow(e1[0],2)+pow(e1[1],2));
        printf("%f\n",e[0]);
    }
    else if(e1_info==3)
    {
        e[0]=sqrt(pow(e1[0],2)+pow(e1[1],2)+pow(e1[2],2));
        printf("%f\n",e[0]);
    }
    else
    {
        printf("%s\n","out of range");
    }
}

/*单位化*/
void unitization(float e1[],int e1_info)
{
    int i;
    if(e1_info==2)
    {
        for(i=0;i<=3;i++)
        {
            e[i]=e1[i]/sqrt(pow(e1[0],2)+pow(e1[1],2));
        }
        printf("(%f,%f)\n",e[0],e[1]);
    }
    else if(e1_info==3)
    {
        for(i=0;i<=3;i++)
        {
            e[i]=e1[i]/sqrt(pow(e1[0],2)+pow(e1[1],2)+pow(e1[2],2));
        }
        printf("(%f,%f,%f)\n",e[0],e[1],e[2]);
    }
    else
    {
        printf("%s\n","out of range");
    }
}



      /*两个向量的计算*/
/*加法*/
void addition(float e1[],float e2[],int e1_info,int e2_info)
{
    if(e1_info==e2_info & e1_info==2)
    {
        int i;
        for(i=0;i<=2;i++)
        {
            e[i]=e1[i]+e2[i];
        }
        printf("(%f,%f)\n",e[0],e[1]);
    }
    else if(e1_info==e2_info & e1_info==3)
    {
        int i;
         for(i=0;i<=3;i++)
        {
            e[i]=e1[i]+e2[i];
        }
        printf("(%f,%f,%f)\n",e[0],e[1],e[2]);
    }
    else if(e1_info != e2_info)
    {
        printf("%s\n","wrong");
    }
    else
    {
        printf("%s\n","out of range");
    }
} 

/*点乘*/
void dot_multi(float e1[],float e2[],int e1_info,int e2_info)
{
    if(e1_info==e2_info & e1_info==2)
    {
        e[0]=e1[0]*e2[0]+e1[1]*e2[1];
        printf("%f\n",e[0]);
    }
    else if(e1_info==e2_info & e1_info==3)
    {
        e[0]=e1[0]*e2[0]+e1[1]*e2[1]+e1[2]*e2[2];
        printf("%f\n",e[0]);
    }
    else if(e1_info != e2_info)
    {
        printf("%s\n","wrong");
    }
    else
    {
        printf("%s\n","out of range");
    }
}

/*叉乘*/
void cross_multi(float e1[],float e2[],int e1_info,int e2_info)
{
    if(e1_info==e2_info & e1_info==3)
    {
        e[0]=e1[1]*e2[2]-e1[2]*e2[1];
        e[1]=e2[0]*e1[2]-e1[0]*e2[2];
        e[2]=e1[0]*e2[1]-e1[1]*e2[0];
        printf("(%f,%f,%f)\n",e[0],e[1],e[2]);
    }
    else
    {
        printf("%s\n","wrong");
    }
}

/*两个向量之间的夹角*/
void angle(float e1[],float e2[],int e1_info,int e2_info)
{
    float cos_e1e2;
    if(e1_info==e2_info & e1_info==2)
    {
        cos_e1e2=(e1[0]*e2[0]+e1[1]*e2[1])/(sqrt(pow(e1[0],2)+pow(e1[1],2))*sqrt(pow(e2[0],2)+pow(e2[1],2)));
        e[0]=acos(cos_e1e2)*180.0/3.1416;
        printf("%f\n",e[0]);
    }
    else if(e1_info==e2_info & e1_info==3)
    {
        cos_e1e2=(e1[0]*e2[0]+e1[1]*e2[1]+e1[2]*e2[2])/(sqrt(pow(e1[0],2)+pow(e1[1],2)+pow(e1[2],2))*sqrt(pow(e2[0],2)+pow(e2[1],2)+pow(e2[2],2)));
        e[0]=acos(cos_e1e2)*180.0/3.1416;
        printf("%f\n",e[0]);
    }
    else if(e1_info != e2_info)
    {
        printf("%s\n","wrong");
    }
    else
    {
        printf("%s\n","out of range");
    }
}


    /*三个向量的计算*/

/*加法*/
void taddition(float e1[],float e2[],float e3[],int e1_info,int e2_info,int e3_info)
{
    int i;
    if(e1_info==e2_info==e3_info & e1_info==2)
    {
        for(i=0;i<=2;i++)
        {
            e[i]=e1[i]+e2[i]+e3[i];
        }
        printf("(%f,%f)\n",e[0],e[1]);
    }
    else if(e1_info==e2_info==e3_info & e1_info==3)
    {
         for(i=0;i<=3;i++)
        {
            e[i]=e1[i]+e2[i]+e3[i];
        }
        printf("(%f,%f,%f)\n",e[0],e[1],e[2]);
    }
    else if(e1_info!=e2_info || e1!=e3_info || e2_info!=e3_info)
    {
        printf("%s\n","wrong");
    }
    else
    {
        printf("%s\n","out of range");
    }
} 

/*叉乘 a×（b×c）*/
void tcross_multi(float e1[],float e2[],float e3[],int e1_info,int e2_info,int e3_info)
{
    if(e1_info==3 & e2_info==3 & e3_info==3)
    {
        int i;
        for(i=0;i<=3;i++)
        {
            e[i]=e2[i]*(e1[0]*e3[0]+e1[1]*e3[1]+e1[2]*e3[2])-e3[i]*(e1[0]*e2[0]+e1[1]*e2[1]+e1[2]*e2[2]);
        }
        printf("(%f,%f,%f)\n",e[0],e[1],e[2]);
    }
    else
    {
        printf("%s\n","wrong");
    }
}


void main(void)
{
    //example
    float e1[]={1,2,5};float e2[]={1,5,8};float e3[]={2,5,3};
    multi(4,e1,3);
    addition(e1,e2,3,3);
    tcross_multi(e1,e2,e3,3,3,3);
}
