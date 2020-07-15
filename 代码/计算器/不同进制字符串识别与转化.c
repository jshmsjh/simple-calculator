/*  BaseConversion.c
    进制转换
	作者：王一脉
*/

#include <BaseConversion.h>
#include <math.h>
#include <stdio.h> 




/*函数名：Underten_To_Ten
 *说明： 十以下进制字符串转十进制数字（整数）
 *输入： x为数字字符串  p为该数字的进制
 *输出：
 *返回： 该数字的10进制数
 *调用：
 *其它： 
 */
long Underten_To_Ten( char *x , unsigned char p )
{
	long i = TenStr_To_TenNum( x );
	long y = 0;
	unsigned int product = 1;
	char flag = 0;
	

	while(i!=0){

		y=y+(i%10)*product;

		i=i/10;

		product=product*p;

	}
	
	
	return y;
}


/*函数名：SixteenStr_To_TenNum
 *说明：  十六进制字符串转十进制数字(整数）
 *输入：  a 为十六进制字符串
 *输出：
 *返回：  十进制数
 *调用：
 *其它：
 */

long SixteenStr_To_TenNum(char *a)
{
	long sum=0 ;
	int  len=0 , t=0 , i=0, flag=0 ;
	
	len=strlen(a);
	
	if (a[0] == '-')
	{
		flag = 1;
		i++;
	}
	
	for(;i<len;i++)
	{
		if(a[i]>='0'&&a[i]<='9'||a[i]>='a'&&a[i]<='f'||a[i]>='A'&&a[i]<='F')
		{
			if(a[i]>='0'&&a[i]<='9')        t=a[i]-'0';
			
			else if(a[i]>='a'&&a[i]<='f')   t=a[i]-'a'+10;
			
			else                            t=a[i]-'A'+10;
			
			sum=sum*16+t;
		}
		else
		{
			printf("请输入正确的十六进制数!\n");
			return;
		}
	}
	
	if (flag == 1)
	{
		sum = -sum;
	}
	
	return sum;
}

/*函数名：TenStr_To_TenNum
 *说明：  十进制字符串转十进制数字(整数）
 *输入：  
 *输出：
 *返回：  十进制数
 *调用：
 *其它：
 */
 
 long TenStr_To_TenNum( char *a )
{
    long sum = 0;
    int len=0 , t=0 , i=0 , flag=0;
	
	len=strlen(a);
	
   	if( a[0] == '-' )   
	{
		flag=1;
		i++;
	}
	
    for(;i<len;i++)
	{
		if(a[i]>='0' && a[i]<='9')
		{
			sum=sum*10 + (a[i]-'0');
		}
		else
		{
			printf("请输入正确的十进制数!\n");
			return;
		}
	}
	
   
    if(flag == 1)
    {
        sum = -sum;
    }
    return sum;
}



/*函数名：TwoStr_To_TenNum
 *说明：  二进制字符串转十进制数字
 *输入：  
 *输出：
 *返回：  十进制数
 *调用：
 *其它：
 */
 long TwoStr_To_TenNum( char *a )
{
    long sum = 0;
    int len=0 , t=0 , i=0 ,flag=0;
	
	len=strlen(a);
	
	if (a[0] == '-')
	{
		flag = 1;
		i++;
	}

    for( ;i<len;i++)
	{
		if(a[i]>='0' && a[i]<='1')
		{
			sum=sum*2 + (a[i]-'0');
		}
		else
		{
			printf("请输入正确的十进制数\n");
			return(0);
		}
	}
	
	if (flag == 1)
	{
		sum = -sum;
	}
  
    return sum;
}


/*函数名：TenNum_To_TwoStr
 *说明：  十进制数字转二进制字符串
 *输入：  
 *输出：  将二进制字符串保存在 TwoStrRes[]
 *返回：  二进制字符串长度
 *调用：
 *其它：
 */
 


char  TenNum_To_TwoStr( long n )
{

	int i=0,count=0,k=0;

	char a[30];

	char num[2] = { '0','1' };
	if(n>=0)
	{

		while(n!=0)
		{
			a[count]=num[n%2];

			n=n/2;

			count++;

		}

		for(int i=count-1;i>=0;i--)//将数组逆序输出 
		{    
		
		  TwoStrRes[k]=a[i];  k++;	 
	
	    }
		TwoStrRes[k] = '\0';
    }
	else
	{

		n=-n;
		
		TwoStrRes[0] = '-';

		k=1;
		
		while (n != 0)
		{
			a[count] = n % 2;

			n = n / 2;

			count++;

		}

		for (int i = count - 1; i >= 0; i--)//将数组逆序输出 
		{

			TwoStrRes[k] = num[a[i]];  k++;

		}
		
		TwoStrRes[k] = '\0';
		k--;
	}

	
	return k;

}

/*函数名：TenNum_To_SixteenStr
 *说明：  十进制数字转十六进制字符串
 *输入：  
 *输出：  将十六进制字符串保存在 SixteenStrRes[]
 *返回：  十六进制字符串长度
 *调用：
 *其它：
 */


 
char  TenNum_To_SixteenStr( long n )
{
    int  q,count=0,j,k=0;
	int  a[20];  
	char u[6] = { 'A','B','C','D','E','F' };
	char num[10] = { '0','1','2','3','4','5','6','7','8','9' };
	if(n==0)  
	{
		SixteenStrRes[0]='0' ;
		SixteenStrRes[1]='\n';
		return 1;
	}
	if (n > 0)
	{
		while (n != 0)
		{
			a[count] = n % 16;
			n = n / 16;
			count++;
		}
		for (j = count - 1; j >= 0; j--)
		{
			if (a[j] > 9 && a[j] < 16)  SixteenStrRes[k] = u[(a[j] - 10)];

			else    SixteenStrRes[k] = num[a[j]];

			k++;
		}
		SixteenStrRes[k] = '\0';
	}
	else
	{
		n = -n;

		SixteenStrRes[0] = '-';

		k = 1;

		while (n != 0)
		{
			a[count] = n % 16;
			n = n / 16;
			count++;
		}
		for (j = count - 1; j >= 0; j--)
		{
			if (a[j] > 9 && a[j] < 16)  SixteenStrRes[k] = u[(a[j] - 10)];

			else    SixteenStrRes[k] = num[a[j]];

			k++;
		}
		SixteenStrRes[k] = '\0';
		k--;
	}
	
	return k;
}

/*函数名：TenNum_To_EightStr
 *说明：  十进制数字转八进制字符串
 *输入：  
 *输出：  将八进制字符串保存在 EightStrRes[]
 *返回：  八进制字符串长度
 *调用：
 *其它：
 */


 
char  TenNum_To_EightStr( long n )
{
    int  count=0,j,k=0;
	int  a[30];  
	char num[10] = { '0','1','2','3','4','5','6','7','8','9' };
	if(n==0)  
	{
		EightStrRes[0]='0' ;
		EightStrRes[1]='\n';
		return 1;
	}
	if (n > 0)
	{
		while (n != 0)
		{
			a[count] = n % 8;
			n = n / 8;
			count++;
		}
		for (j = count - 1; j >= 0; j--)
		{
			EightStrRes[k] = num[a[j]];

			k++;
		}
		EightStrRes[k] = '\0';
	}
	else
	{
		n = -n;

		EightStrRes[0] = '-';

		k = 1;

		while (n != 0)
		{
			a[count] = n % 8;
			n = n / 8;
			count++;
		}
		for (j = count - 1; j >= 0; j--)
		{
			EightStrRes[k] = num[a[j]];

			k++;
		}
		EightStrRes[k] = '\0';
	    
		k--;
	}
	
	return k;
}



