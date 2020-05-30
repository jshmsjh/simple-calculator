/* 
	正态分布要使用积分暂未实现  
*/ 
#include<stdio.h>
#include<math.h>
#define MAXN 10000000
#define LL long long

/*
regression_type
1:单变量统计 2:y=ax+b 3:y=ax^2+bx+c 4:y=a+blnx
5:y=a*e^(bx)  6:a*b^x 7:y=a*x^b     8:y=a+b/x
regression_err
1:输入不合法
*/
int regression_type = 0,regression_err = 0,x_zero = 0,y_zero = 0;
double a,b,c,r,x[100],y[100];

/*
平均值：ave_x,ave_y;项数：n;
求和：sumx,sumx2,sumy,sumy2,sumxy,sumx3,sumx2y,sumx4;
总体方差：o2x,o2y;总体标准差：ox,oy;
样本方差：s2x,s2y;样本标准差：sx,sy;

s:排序后的x,freqs:排序后的freq 
freq:频数,totn:频数和  
*/
int n,totn,freq_on=0,freq[100],freqs[100];
double ave_x,sumx=0,sumx2=0,o2x,ox,s2x,sx,sumx3=0,sumx4=0;
double ave_y,sumy=0,sumy2=0,o2y,oy,s2y,sy,sumxy=0,sumx2y=0;
double minx=MAXN,maxx=0,miny=MAXN,maxy=0,t,s[100];

double min(double a,double b){
	if(a<b) return a;else return b;
}
double max(double a,double b){
	if(a>b) return a;else return b;
}
//相关系数 
void calc_r(int n,double x1[100],double y1[100]){
	int i;
	double tmp=0,tmp1=0,tmp2=0,ave_xx,ave_yy;
	for(i=1;i<=n;i++){
		tmp1 += x1[i];tmp2 += y1[i];
	}
	ave_xx = tmp1/n;ave_yy = tmp2/n;
	tmp1=0;tmp2=0;
	for(i=1;i<=n;i++){
		tmp += (x1[i]-ave_xx)*(y1[i]-ave_yy);
		tmp1 += pow(x1[i]-ave_xx,2);
		tmp2 += pow(y1[i]-ave_yy,2);
	}
	r = tmp/sqrt(tmp1*tmp2);
}
//线性回归 
void linear_regression(int n,double x1[100],double y1[100]){
	int i;
	double fenmu = n*sumx2 - sumx*sumx;
	double fenzi_a = n*sumxy - sumx*sumy;
	double fenzi_b = sumx2*sumy - sumx*sumxy;
	a = fenzi_a/fenmu;b = fenzi_b/fenmu; 
	calc_r(n,x1,y1);
	if(regression_type == 2)
		printf("linear_regression a:%lf b:%lf r:%lf\n",a,b,r);
}
//二次回归 
void secondary_regression(){
	int i;
	double N = 1e-13;
	double m1,m2,m3,z1,z2,z3;
	do{
		m1=a; a=(sumx2y-sumx3*b-sumx2*c)/sumx4; z1=(a-m1)*(a-m1);
		m2=b; b=(sumxy-sumx*c-sumx3*a)/sumx2; z2=(b-m2)*(b-m2);
		m3=c; c=(sumy-sumx2*a-sumx*b)/n; z3=(c-m3)*(c-m3);
	}while((z1>N)||(z2>N)||(z3>N));
	printf("secondary_regression a:%lf b:%lf c:%lf\n",a,b,c);
}
//对数回归 
void logarithmic_regression(){
	if(x_zero) {regression_err = 1;return;}
	int i;
	double tmpa,tmpb,xx[100],yy[100];
	for(i=1;i<=n;i++){
		xx[i] = log(x[i]);
	}
	linear_regression(n,xx,y);
	calc_r(n,xx,y);
	tmpa = a;tmpb = b;
	a = tmpb;b = tmpa;
	printf("logarithmic_regression a:%lf b:%lf r:%lf\n",a,b,r);
}
//e指数回归
void e_index_regression(){
	if(y_zero){regression_err = 1;return;}
	int i;
	double tmpa,tmpb,yy[100];
	for(i=1;i<=n;i++){
		yy[i] = log(y[i]);
	}
	linear_regression(n,x,yy);
	calc_r(n,x,yy);
	tmpa = a;tmpb = b;
	a = exp(tmpb);b = tmpa;
	printf("e_index_regression a:%lf b:%lf r:%lf\n",a,b,r);
} 
//ab指数回归
void ab_index_regression(){
	if(y_zero){regression_err = 1;return;}
	int i;
	double tmpa,tmpb,yy[100];
	for(i=1;i<=n;i++){
		yy[i] = log(y[i]);
	}
	linear_regression(n,x,yy);
	calc_r(n,x,yy);
	tmpa = a;tmpb = b;
	a = exp(tmpb);b = exp(tmpa);
	printf("ab_index_regression a:%lf b:%lf r:%lf\n",a,b,r);
}
//乘方回归 
void multiplier_regression(){
	if(x_zero || y_zero){regression_err = 1;return;}
	int i;
	double tmpa,tmpb,xx[100],yy[100];
	for(i=1;i<=n;i++){
		xx[i] = log(x[i]);
		yy[i] = log(y[i]);
	}
	linear_regression(n,xx,yy);
	calc_r(n,xx,yy);
	tmpa = a;tmpb = b;
	a = exp(tmpb);b = tmpa;
	printf("multiplier_regression a:%lf b:%lf r:%lf\n",a,b,r);
} 
//逆回归
void inverse_regression(){
	if(x_zero)  {regression_err = 1;return;}
	int i;
	double tmpa,tmpb,xx[100];
	for(i=1;i<=n;i++){
		xx[i] = 1/x[i];
	}
	linear_regression(n,xx,y);
	calc_r(n,xx,y);
	tmpa = a;tmpb = b;
	a = tmpb;b = tmpa;
	printf("inverse_regression a:%lf b:%lf r:%lf\n",a,b,r);
} 
void double_variable_stat(){
	int i;
	double tmpx=0,tmpy=0;
	for(i=1;i<=n;i++){
		scanf("%lf",&x[i]);scanf("%lf",&y[i]);
		sumx += x[i];sumy += y[i];
		sumx2 += pow(x[i],2);sumy2 += pow(y[i],2);
		sumx3 += pow(x[i],3);sumxy += x[i]*y[i];
		sumx4 += pow(x[i],4);sumx2y += pow(x[i],2)*y[i];
		minx = min(minx,x[i]);miny = min(miny,y[i]);
		maxx = max(maxx,x[i]);maxy = max(maxy,y[i]);
		if(!x[i]) x_zero = 1;if(!y[i]) y_zero = 1;
	}
	ave_x = sumx/n;ave_y = sumy/n;
	linear_regression(n,x,y);
	for(i=1;i<=n;i++){
		tmpx += pow(x[i]-ave_x,2);
		tmpy += pow(y[i]-ave_y,2);
	}
	if(n>1){s2x = tmpx/(n-1);s2y = tmpy/(n-1);}
	o2x = tmpx/n;o2y = tmpy/n;
	sx = sqrt(s2x);sy = sqrt(s2y);
	ox = sqrt(o2x);oy = sqrt(o2y);
	printf("ave_x:%lf sumx:%lf sumx2:%lf o2x:%lf ox:%lf s2x:%lf\n",ave_x,sumx,sumx2,o2x,ox,s2x);
	printf("sx:%lf n:%d ave_y:%lf sumy:%lf sumy2:%lf o2y:%lf\n",sx,n,ave_y,sumy,sumy2,o2y);
	printf("oy:%lf s2y:%lf sy:%lf sumxy:%lf sumx3:%lf sumx2y:%lf\n",oy,s2y,sy,sumxy,sumx3,sumx2y);
	printf("sumx4:%lf minx:%lf maxx:%lf miny:%lf maxy:%lf\n",sumx4,minx,maxx,miny,maxy);
}
void qsort(int l,int r){
	double mid = s[(l+r)/2];
	int i=l,j=r;
	do{
		while(s[i]<mid) i++;
		while(s[j]>mid) j--;
		if(i<=j){
			double t = s[i];s[i] = s[j];s[j] = t;
			int tt = freqs[i];freqs[i] = freqs[j];freqs[j] = tt;
			i++;
			j--;
		}
	}while(i<=j);
	if(l<j) qsort(l,j);
	if(i<r) qsort(i,r);
}
void gaussian_distribution(){
	
} 
void calc_t(double tt){
	t = (tt - ave_x)/ox;
	printf("%lf",t);
}
void single_variable_stat(){
	int i;
	double tmpx=0;totn=0;freq_on=1;
	for(i=1;i<=n;i++){
		scanf("%lf",&x[i]);freq[i] = 1;
		if(freq_on) scanf("%d",&freq[i]);freqs[i] = freq[i];
		s[i] = x[i];
		sumx += x[i]*freq[i];sumx2 += pow(x[i],2)*freq[i];
		sumx3 += pow(x[i],3)*freq[i];sumx4 += pow(x[i],4)*freq[i];
		minx = min(minx,x[i]);maxx = max(maxx,x[i]);
		totn += freq[i];
	}
	ave_x = sumx/totn;
	for(i=1;i<=n;i++){
		tmpx += pow(x[i]-ave_x,2)*freq[i];
	}
	if(totn>1) s2x = tmpx/(totn-1);
	o2x = tmpx/totn;
	sx = sqrt(s2x);
	ox = sqrt(o2x);
	calc_t(1);
	qsort(1,n);
	int tpos = floor((totn+1)/4),pos=0,tmp=0;//tpos:考虑频数后的位置 
	//Q1
	while(tmp<=tpos){tmp += freqs[++pos];} 
	if(tmp < tpos) pos++;
	if(tmp == tpos && freqs[pos] == 1) pos++;
	double Q1 = s[pos];
	//Med
	tpos = floor((totn+1)/2);pos=0;tmp=0;
	while(tmp<=tpos){tmp += freqs[++pos];}
	tmp -= freqs[pos--];if(tmp < tpos) pos++;
	double Med = s[pos]/2;
	if(freqs[pos] == 1) pos++;Med += s[pos]/2;
	//Q3
	tpos = floor((totn+1)*3/4);pos=0;tmp=0;
	while(tmp<=tpos){tmp += freqs[++pos];}
	tmp -= freqs[pos--];if(tmp < tpos) pos++;
	double Q3 = s[pos];
	printf("n:%d ",totn);
	printf("Q1:%lf Med:%lf Q3:%lf",Q1,Med,Q3);
}
int main(){
	int i;
	printf("regression_type:");
	scanf("%d",&regression_type);
	scanf("%d",&n);
	if(regression_type == 1){
		single_variable_stat();
	}else{
		double_variable_stat();
	}
	return 0;
}
/*
single variable
freq off
1
6
1 2 3 5 4 6
freq on
1
6
1 1
2 2
3 3
6 6
5 9
4 8

double variable
1
6
1 1
2 2
3 3
6 6
5 9
4 8
linear_regression a:1.457143 b:-0.266667 r:0.8231876236
secondary_regression a:-0.357140 b:3.957120 c:-3.599969
logarithmic_regression a:0.234228 b:4.194191 r:0.8392488955
e_index_regression a:0.873580 b:0.412910 r:0.8916799686
ab_index_regression a:0.873580 b:1.511209 r:0.8916799686
multiplier_regression a:3.417108 b:-0.037394 r:0.9398933572
inverse_regression a:8.194719 b:-8.231966 r:-0.778950226

linear_regression
7
21 1.945910
23 2.397895
25 3.044522
27 3.178054
29 4.189655              

e_index_regression
7
21 7
23 11
25 21
27 24
29 66
32 105
35 325
a:0.022710 b:0.269211

secondary_regression
6
1 1
2 2
3 3
6 6
5 9
4 8
a:-0.357140 b:3.957120 c:-3.599969
*/          
