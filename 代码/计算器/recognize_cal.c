#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <stdlib.h>
/*
    函数功能说明：数学函数字符串识别与计算  作者：王一脉
	
	Function_Calculation(char* FormulaInput, float x)    FormulaInput为数学函数字符串    x为变量值
	
	                                                     该函数可识别数学函数，并且将x代入数学函数计算出相应结果
														 
														 使用例子见文末的main1与main2
*/


char  FormulaInput[80];

char  Func_Part[20];   //函数拆分得到的字符串

char  sinx[] = "sinx";

char  cosx[] = "cosx";

char  expx[] = "exp(x)";

char  lnx[] = "ln(x)";

char  x4[] = "x(4)";

char  x3[] = "x(3)";

char  x2[] = "x(2)";

char  x1[] = "x";

float  Part_Calculation(char* Func_Part,float x)
{
	char*a, i = 0, Num[10];

	float coe, res;

	if (strstr(Func_Part, sinx))
	{
		a = strstr(Func_Part, sinx);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * (float)sin((double)x);

		return(res);
	}

	if (strstr(Func_Part, x4))
	{
		a = strstr(Func_Part, x4);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * x * x * x * x;

		return(res);
	}

	if (strstr(Func_Part, x3))
	{
		a = strstr(Func_Part, x3);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * x * x * x ;

		return(res);
	}

	if (strstr(Func_Part, cosx))
	{
		a = strstr(Func_Part, cosx);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * (float)cos((double)x);

		return(res);
	}

	if (strstr(Func_Part, expx))
	{
		a = strstr(Func_Part, expx);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * (float)exp((double)x);

		return(res);
	}

	if (strstr(Func_Part, lnx))
	{
		a = strstr(Func_Part, lnx);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * (float)log((double)x);

		return(res);
	}

	if (strstr(Func_Part, x2))
	{
		a = strstr(Func_Part, x2);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * x * x;

		return(res);
	}

	if (strstr(Func_Part, x1))
	{
		a = strstr(Func_Part, x1);

		*a = 0x00;

		sprintf(Num, "%s", Func_Part);

		coe = atof(Num);

		if (coe == 0)   coe = 1;

		res = coe * x;

		return(res);
	}

	coe = atof(Func_Part);

	return(coe);
}

float Function_Calculation(char* FormulaInput, float x)
{
	int i, j = 0, flag = 1, flag_2 = 1;

	float res = 0 , md = 1, md_2 = 1;

	for (i = 0; i <= 80; i++)
	{
		if (FormulaInput[i] != 0x2B && FormulaInput[i] != 0x2D)
		{
			Func_Part[j] = FormulaInput[i];

			j++;
		}

		if (FormulaInput[i] == 0x2D)
		{
			Func_Part[j] = 0x00;

			j = 0;

			if (flag == 1)
			{
				if (flag_2 == 1)
				{
					res = res + Part_Calculation(Func_Part, x) * md / md_2;           
				}
				if (flag_2 == 0)
				{
					res = res +   md / md_2 / Part_Calculation(Func_Part, x);
				}
			}

			if (flag == 0)
			{
				if (flag_2 == 1)
				{
					res = res - Part_Calculation(Func_Part, x) * md / md_2;
				}
				if (flag_2 == 0)
				{
					res = res - md / md_2 / Part_Calculation(Func_Part, x);
				}
			}

			md = 1;  md_2 = 1;

			flag = 0;  flag_2 = 1;
		}

		if (FormulaInput[i] == 0x2B)
		{
			Func_Part[j] = 0x00;

			j = 0;

			if (flag == 1)
			{
				if (flag_2 == 1)
				{
					res = res + Part_Calculation(Func_Part, x) * md / md_2;       
				}
				if (flag_2 == 0)
				{
					res = res + md / md_2 / Part_Calculation(Func_Part, x);
				}
			}

			if (flag == 0)
			{
				if (flag_2 == 1)
				{
					res = res - Part_Calculation(Func_Part, x) * md / md_2;
				}
				if (flag_2 == 0)
				{
					res = res - md / md_2 / Part_Calculation(Func_Part, x);
				}
			}

			md = 1;  md_2 = 1;

			flag = 1;  flag_2 = 1;
		}

		if (FormulaInput[i] == 0x2A)
		{
			Func_Part[j] = 0x00;

			j = 0;

			if( flag_2 == 1 )   md = md * Part_Calculation(Func_Part, x);       

			if (flag_2 == 0)    md_2 = md_2 * Part_Calculation(Func_Part, x);

			
		}

		if (FormulaInput[i] == 0x2F)
		{
			Func_Part[j] = 0x00;

			j = 0;

			md = md * Part_Calculation(Func_Part, x);
			
			flag_2 = 0;
		}

		if (FormulaInput[i] == 0x00)
		{
			Func_Part[j] = 0x00;

			if (flag == 1)
			{
				if (flag_2 == 1)
				{
					res = res + Part_Calculation(Func_Part, x) * md / md_2;
				}
				if (flag_2 == 0)
				{
					res = res + md / md_2 / Part_Calculation(Func_Part, x);
				}
			}

			if (flag == 0)
			{
				if (flag_2 == 1)
				{
					res = res - Part_Calculation(Func_Part, x) * md / md_2;      
				}
				if (flag_2 == 0)
				{
					res = res - md / md_2 / Part_Calculation(Func_Part, x);
				}
			}

			return(res);
		}
	}
}


void main1()
{
	
	

		char test1[] = "-2x+2x/2x";

		float a;

		int b=4 ;

		a = Function_Calculation(test1, b);

		printf("%f", a);

	

}

void main2()
{
	char test1[] = "2x-5sinx*6cosx/3x(2)*x(3)+2x/ln(x)*exp(x)+1/2";

	float a;

	int b = 4;

	a = Function_Calculation(test1, b);

	printf("%f", a);
}
