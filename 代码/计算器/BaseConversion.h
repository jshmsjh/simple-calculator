/*  BaseConversion.h
    进制转换
*/

#ifndef BASECONVERSION_H
#define BASECONVERSION_H

long Underten_To_Ten( char *x , unsigned char p );

long SixteenStr_To_TenNum(char *a);

long TenStr_To_TenNum( char *a );

long TwoStr_To_TenNum( char *a );

char  TenNum_To_TwoStr( long n );

char  TenNum_To_SixteenStr(long n);

char  TenNum_To_EightStr(long n);

char  TwoStrRes[30];

char  SixteenStrRes[15];

char  EightStrRes[21];

#endif

/*
	读取示例
	
	printf("%s", EightStrRes);

*/
