/*   ComplexCalculation.c
     复数运算
	 作者：王一脉
*/


#include <ComplexCalculation.h>
#include <math.h>
#include <stdio.h>


/*函数名：complexAdd
 *说明：复数加法
 *输入：a,b两个复数
 *输出：
 *返回：a + b 
 *调用：
 *其它：
 */
complexType    complexAdd(complexType a, complexType b)
{
    complexType result;

    result.Real = a.Real + b.Real;
    result.Imag = a.Imag + b.Imag;

    return result;
}

/*函数名：complexSubtract
 *说明：复数减法
 *输入：minuend被减数，subtrahend减数
 *输出：
 *返回：a － b 
 *调用：
 *其它：
 */
complexType    complexSubtract(complexType minuend, complexType subtrahend)
{
    complexType result;

    result.Real = minuend.Real - subtrahend.Real;
    result.Imag = minuend.Imag - subtrahend.Imag;

    return result;
}

/*函数名：complexMultiply
 *说明：复数乘法
 *输入：a,b两个复数
 *输出：
 *返回：a * b 
 *调用：
 *其它：
 */
complexType complexMultiply(complexType a, complexType b)
{
    complexType result;

    result.Real = a.Real * b.Real - a.Imag * b.Imag;
    result.Imag = a.Imag * b.Real + a.Real * b.Imag;

    return result;
}


/*函数名：complexDivision
 *说明：复数除法
 *输入：dividend被除数，divisor除数
 *输出：
 *返回：a / b 
 *调用：
 *其它：divisor的实部和虚部不能同时为0
 */
complexType complexDivision(complexType dividend, complexType divisor)
{
    complexType result;

    /*断言，被除数的实部和虚部不能同时为零*/
    assert_param(IS_COMPLEX_DIVISOR_CORRENT(divisor.Real, divisor.Imag));

    result.Real = (mathDouble)(dividend.Real * divisor.Real + dividend.Imag * divisor.Imag) / \
                  (divisor.Real * divisor.Real + divisor.Imag * divisor.Imag);
    result.Imag = (mathDouble)(dividend.Imag * divisor.Real - dividend.Real * divisor.Imag) / \
                  (divisor.Real * divisor.Real + divisor.Imag * divisor.Imag);
    return result;
}

/*函数名：complexAbs
 *说明：复数取模
 *输入：a复数
 *输出：
 *返回：复数的模
 *调用：
 *其它：
 */
mathDouble    complexAbs(complexType a)
{
    return (sqrt( pow(a.Real,2) + pow(a.Imag,2) ));
}


/*函数名：complexCon
 *说明：复数的共轭
 *输入：a复数
 *输出：
 *返回：复数的共轭 
 *调用：
 *其它：
 */
complexType    complexCon(complexType a)
{
	complexType result;

    result.Real = a.Real ;
    result.Imag = -a.Imag ;

    return result;
}


/*函数名：complexAngle
 *说明：复数取相角
 *输入：a复数
 *输出：
 *返回：复数的相角(弧度）
 *调用：
 *其它：
 */
mathDouble    complexAngle(complexType a)
{
    
    return (atan2(a.Imag, a.Real));
}

/*函数名：complexByAbsAngle
 *说明：通过模和相角合成复数
 *输入：r 模， theta 相角
 *输出：
 *返回：复数
 *调用：
 *其它：
 */
complexType complexByAbsAngle(mathDouble r, mathDouble theta)
{
    complexType tmp_1,tmp_2;

    tmp_2.Real = cos(theta);
    tmp_2.Imag = sin(theta);
    tmp_2.Real *= r;
    tmp_2.Imag *= r;

    return tmp_2;
}





