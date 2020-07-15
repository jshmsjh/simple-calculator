/*   ComplexCalculation.c
     ��������
	 ���ߣ���һ��
*/


#include <ComplexCalculation.h>
#include <math.h>
#include <stdio.h>


/*��������complexAdd
 *˵���������ӷ�
 *���룺a,b��������
 *�����
 *���أ�a + b 
 *���ã�
 *������
 */
complexType    complexAdd(complexType a, complexType b)
{
    complexType result;

    result.Real = a.Real + b.Real;
    result.Imag = a.Imag + b.Imag;

    return result;
}

/*��������complexSubtract
 *˵������������
 *���룺minuend��������subtrahend����
 *�����
 *���أ�a �� b 
 *���ã�
 *������
 */
complexType    complexSubtract(complexType minuend, complexType subtrahend)
{
    complexType result;

    result.Real = minuend.Real - subtrahend.Real;
    result.Imag = minuend.Imag - subtrahend.Imag;

    return result;
}

/*��������complexMultiply
 *˵���������˷�
 *���룺a,b��������
 *�����
 *���أ�a * b 
 *���ã�
 *������
 */
complexType complexMultiply(complexType a, complexType b)
{
    complexType result;

    result.Real = a.Real * b.Real - a.Imag * b.Imag;
    result.Imag = a.Imag * b.Real + a.Real * b.Imag;

    return result;
}


/*��������complexDivision
 *˵������������
 *���룺dividend��������divisor����
 *�����
 *���أ�a / b 
 *���ã�
 *������divisor��ʵ�����鲿����ͬʱΪ0
 */
complexType complexDivision(complexType dividend, complexType divisor)
{
    complexType result;

    /*���ԣ���������ʵ�����鲿����ͬʱΪ��*/
    assert_param(IS_COMPLEX_DIVISOR_CORRENT(divisor.Real, divisor.Imag));

    result.Real = (mathDouble)(dividend.Real * divisor.Real + dividend.Imag * divisor.Imag) / \
                  (divisor.Real * divisor.Real + divisor.Imag * divisor.Imag);
    result.Imag = (mathDouble)(dividend.Imag * divisor.Real - dividend.Real * divisor.Imag) / \
                  (divisor.Real * divisor.Real + divisor.Imag * divisor.Imag);
    return result;
}

/*��������complexAbs
 *˵��������ȡģ
 *���룺a����
 *�����
 *���أ�������ģ
 *���ã�
 *������
 */
mathDouble    complexAbs(complexType a)
{
    return (sqrt( pow(a.Real,2) + pow(a.Imag,2) ));
}


/*��������complexCon
 *˵���������Ĺ���
 *���룺a����
 *�����
 *���أ������Ĺ��� 
 *���ã�
 *������
 */
complexType    complexCon(complexType a)
{
	complexType result;

    result.Real = a.Real ;
    result.Imag = -a.Imag ;

    return result;
}


/*��������complexAngle
 *˵��������ȡ���
 *���룺a����
 *�����
 *���أ����������(���ȣ�
 *���ã�
 *������
 */
mathDouble    complexAngle(complexType a)
{
    
    return (atan2(a.Imag, a.Real));
}

/*��������complexByAbsAngle
 *˵����ͨ��ģ����Ǻϳɸ���
 *���룺r ģ�� theta ���
 *�����
 *���أ�����
 *���ã�
 *������
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





