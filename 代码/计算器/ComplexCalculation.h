/*     ComplexCalculation.h
       复数运算
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



#if ASSERT_ENABLE
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((mathUint_8 *)__FILE__, __LINE__))
  void assert_failed(mathUint_8* file, mathUint_32 line);
#else
  #define assert_param(expr) ((void)0)
#endif



#endif
