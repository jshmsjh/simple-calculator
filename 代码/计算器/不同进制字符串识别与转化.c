/*  BaseConversion.c
    ����ת��
	���ߣ���һ��
*/

#include <BaseConversion.h>
#include <math.h>
#include <stdio.h> 




/*��������Underten_To_Ten
 *˵���� ʮ���½����ַ���תʮ�������֣�������
 *���룺 xΪ�����ַ���  pΪ�����ֵĽ���
 *�����
 *���أ� �����ֵ�10������
 *���ã�
 *������ 
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


/*��������SixteenStr_To_TenNum
 *˵����  ʮ�������ַ���תʮ��������(������
 *���룺  a Ϊʮ�������ַ���
 *�����
 *���أ�  ʮ������
 *���ã�
 *������
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
			printf("��������ȷ��ʮ��������!\n");
			return;
		}
	}
	
	if (flag == 1)
	{
		sum = -sum;
	}
	
	return sum;
}

/*��������TenStr_To_TenNum
 *˵����  ʮ�����ַ���תʮ��������(������
 *���룺  
 *�����
 *���أ�  ʮ������
 *���ã�
 *������
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
			printf("��������ȷ��ʮ������!\n");
			return;
		}
	}
	
   
    if(flag == 1)
    {
        sum = -sum;
    }
    return sum;
}



/*��������TwoStr_To_TenNum
 *˵����  �������ַ���תʮ��������
 *���룺  
 *�����
 *���أ�  ʮ������
 *���ã�
 *������
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
			printf("��������ȷ��ʮ������\n");
			return(0);
		}
	}
	
	if (flag == 1)
	{
		sum = -sum;
	}
  
    return sum;
}


/*��������TenNum_To_TwoStr
 *˵����  ʮ��������ת�������ַ���
 *���룺  
 *�����  ���������ַ��������� TwoStrRes[]
 *���أ�  �������ַ�������
 *���ã�
 *������
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

		for(int i=count-1;i>=0;i--)//������������� 
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

		for (int i = count - 1; i >= 0; i--)//������������� 
		{

			TwoStrRes[k] = num[a[i]];  k++;

		}
		
		TwoStrRes[k] = '\0';
		k--;
	}

	
	return k;

}

/*��������TenNum_To_SixteenStr
 *˵����  ʮ��������תʮ�������ַ���
 *���룺  
 *�����  ��ʮ�������ַ��������� SixteenStrRes[]
 *���أ�  ʮ�������ַ�������
 *���ã�
 *������
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

/*��������TenNum_To_EightStr
 *˵����  ʮ��������ת�˽����ַ���
 *���룺  
 *�����  ���˽����ַ��������� EightStrRes[]
 *���أ�  �˽����ַ�������
 *���ã�
 *������
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



