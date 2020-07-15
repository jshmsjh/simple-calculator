/*     ComplexCalculation.h
       作者：王一脉 
	   详细说明见相关C文件
*/



#ifndef _COMPLEXCALCULATION_H_
#define _COMPLEXCALCULATION_H_

#define ASSERT_ENABLE 1

#define IS_COMPLEX_DIVISOR_CORRENT(DIVISOR_REAL, DIVISOR_IMAG)        ((DIVISOR_REAL != 0) || (DIVISOR_IMAG != 0)) 

typedef double                    mathDouble;
typedef unsigned char            mathUint_8;
typedef unsigned short int        mathUint_16;
typedef unsigned int            mathUint_32;


typedef struct _ReDefcomplex
{
    mathDouble    Real;
    mathDouble    Imag;
}complexType;


complexType    complexAdd(complexType a, complexType b);

complexType    complexSubtract(complexType minuend, complexType subtrahend);

complexType complexMultiply(complexType a, complexType b);

complexType complexDivision(complexType dividend, complexType divisor);

mathDouble    complexAbs(complexType a);

mathDouble    complexAngle(complexType a);

complexType complexByAbsAngle(mathDouble r, mathDouble theta);

complexType    complexCon(complexType a);




#endif

