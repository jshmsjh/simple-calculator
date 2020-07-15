# Machine_learning
一个模拟Casio fx991cn x计算机做的学习机部分计算的实现代码，学习过程中做的总结，资历尚浅，如有错误请不吝指出。

# 目录代码介绍

## BaseConversion进制转换
   - Underten_To_Ten(x,p):输入数字字符串和该数字进制（十以下），返回该数字的十进制数
   - Sixteen_To_TenNum(a):输入十六进制字符串，返回该数字的十进制数
   - TenStr_To_TeNum(a):输入十进制字符串，返回十进制数字
   - TwoStr_To_TenNum(a):输入二进制字符串，返回该数字的十进制数
   - TenNum_To_TwoStr(n):输入十进制数字，输出二进制字符串TwoStrRes[]，返回二进制字符串长度
   - TenNum_To_SixteenStr(n):输入十进制数字，输出十六进制字符串SixteenStrRes[]，返回十六进制字符串长度
   - TenNum_To_EightStr(n):输入十进制数字，输出八进制字符串EightStrRes[]，返回八进制字符串长度
   
## ComplexCalculation复数运算
   - complexAdd(a,b):两个复数相加
   - complexSubtract(a,b):两个复数相减
   - complexMultiply(a,b):两个复数相乘
   - complexDivision(a,b):两个复数相除
   - complexAbs(a):一个复数取模
   - complexCon(a):求一个复数的共轭
   - complexAngle(a):求复数的相角（弧度）
   - complexByAbsAngle(r,theta):通过模和相角合成复数
   - assert_failed:打印出错的函数
   
## calc基础计算
   _ 基础计算的整合

## change_code公式转换
   - change(a):输入LaTeX，转换成可以被理解的形式
   
## chart表格功能
   - double y_1:输入一个函数
   - double y_2:输入一个函数
   - chart(x,xt,d,f,g):输入自变量的起点、终点、步长，可以画出表格
   
## diffential微分
   - double f(x,y):输入函数表达式
   - differential(x0):输出该函数的微分
   
## intergral积分
   - double function(x):输入函数表达式
   - djf(a,b):输入上下限，求出该函数的定积分
   
## matrix矩阵
   - Matplus(Mata,Matb,Mata_info,Matb_info):输入两个矩阵以及它们的行列数，输出它们的和
   - MatnumMul(k,Mata,Mata_info):输入数字、一个矩阵及它的行列数，求出数乘的结果
   - T(Mata,Mata_info):输入一个矩阵及它的行列数，求出转置矩阵
   - MatMulti(Mata,Mata_info,Matb,Matb_info):输入两个矩阵及它们行列数，求出矩阵的乘积
   - MatDet(Mata,Mata_info):输入一个矩阵及它的行列数，求出行列式的值
   - MatAdj(Mata,Mata_info):输入一个矩阵及它的行列数，求出它的伴随矩阵
   - MatInv(Mata,Mata_info):输入一个矩阵及它的行列数，求出它的逆矩阵
   
## others
   - gcd(a,b):求两个数的最大公约数
   - lcm(a,b):求两个数的最小公倍数
   - get_prime_list(n):输出这个数的素数表
   - get_prime(x):质因数分解
   
## polar排列组合、极坐标
   - a(m,n):计算排列数
   - c(m,n):计算组合数
   - jc(n):计算n的阶乘
   - getrandom(Max,Min):生成m到n的随机数
   - polay_to_rect(POLAR_V pv):输入极坐标，转换成直角坐标
   - rect_to_polar(RECT_V rv):输入直角坐标，转换成极坐标
   
## proportion解比例式
   - proportion(a,b,c,x):输入a、b、c三个数字，求出a:b=x:c中的x的值
   
## solving_equations解方程
   - one_one(a,b):依次输入一元一次方程的系数，解出X的值
   - one_two(a,b,c):依次输入一元二次方程的系数，解出X的值
   - vone_three(a,b,c,d):依次输入一元三次方程的系数，解出X的值
   - one_four(a,b,c,d,e):依次输入一元四次方程的系数，解出X的值
   - two_one(a1,b1,c1,a2,b2,c2):依次输入二元一次方程的系数，解出X的值
   - three(a1,b1,c1,a2,b2,c2,a3,b3,c3):按照先行后列的方式输入数字，求出行列式的值
   - three_one(a1,b1,c1,a2,b2,c2,a3,b3,c3):依次输入三元一次方程的系数，解出x的值
   - four_one(a1,b1,c1,d1,a2,b2,c2,d2,a3,b3,c3,d3,a4,b4,c4,d4):依次输入四元一次方程的系数，解出x的值
   
## stat统计回归
   - calc_r(n,x1,y1):输入个数n以及两个变量的值，求出相关系数
   - linear_regression(n,x1,y1):线性回归
   - secondary_regression():二次回归
   - logarithmic_regression():对数回归
   - e_index_regression():e指数回归
   - ab_index_regression():ab指数回归
   - multiplier_regeression():乘方回归
   - inverse_regression():逆回归
   - double_variable_stat():双变量统计
   - qsort(l,r):快速排序
   - gaussian_distribution():高斯分布
   - single_variable_stat():单变量统计
   
## vector向量计算
   - multi(k,e1,e1_info):输入一个数，一个向量的坐标以及该向量的维度，求出数乘后的坐标
   - module(e1,e1_info):输入一个向量以及该向量的维度，求出该向量的模
   - unitization(e1,e1_info):输入一个向量以及该向量的维度，求出单位化的坐标
   - addition(e1,e2,e1_info,e2_info):输入两个向量以及它们的维度，求出向量的和
   - dot_multi(e1,e2,e1_info,e2_info):输入两个向量以及它们的维度，求出它们点乘的结果
   - cross_multi(e1,e2,e1_info,e2_info):输入两个向量以及它们的维度，求出它们叉乘的结果
   - angle(e1,e2,e1_info,e2_info):输入两个向量以及它们的维度，求出这两个向量之间的夹角
   - taddition(e1,e2,e3,e1_info,e2_info,e3_info):输入三个向量以及它们的维度，求出这三个向量的和
   - tcross_multi(e1,e2,e3,e1_info,e2_info,e3_info):输入三个向量以及它们的维度，求出叉乘的结果
   
## 函数识别与计算

## 中文拼音输入法
   - 将常用的拼音对应的字建成字符串，利用字母表进行索引
