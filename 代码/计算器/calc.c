#include<math.h>
#include<stdio.h>
#include<string.h>

double v[1000];
char s[1000];
double get_num(int l,int r){
	double res;
	int flagcur,cur1,cur2,cur2len,tmp,f=1,i;
	char ch;
	flagcur=cur1=cur2=cur2len=0;
		for(i=l;i<r;i++){
			ch=s[i];
			if(ch>='0'&&ch<='9'){
				tmp=ch-'0';
				if(flagcur==0) cur1=cur1*10+tmp;
				else{
					cur2=cur2*10+tmp;cur2len++;
				} 
			}else if(s[i]=='.') flagcur=1;
			else if(ch==')'){s[i]='#';break;}
			else if(ch=='-') f=-1;
			s[i]='#';
		}
		res = cur1;
		if(cur2) res=res+cur2*pow(10,-cur2len);
	return f*res;
}
double calc(){
	char ss[1000],ch;
	int q[1000],part1[1000],part2[1000];
	double num1=0,num2=0;
	int flagp;//flag priority
	int flagcur,flag=0,cur1,cur2,cur2len,tmp,curl,curr;
	double curnum1=0,curnum2=0;
	memset(v,0,sizeof(v));
	scanf("%s",&ss);
	int len=strlen(ss),cnt=0,cnt1=0,cnt2=0,flagnum2=0,flag1,flag2,flag3,flag4,l,r,i,j,k;
	for(i=0;i<len;i++) s[i+1]=ss[i];len++;
	//sin,cos,tan,exp,abs,asin,acos,atan,ln,log10,sqrt
	for(i=1;i<len;i++){
		if(s[i]=='s'){
			if(s[i+1]=='i'&&s[i+2]=='n'&&s[i+3]=='('){
				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
				v[i]=sin(get_num(i+4,len));
			}
		}else if(s[i]=='c'){
			if(s[i+1]=='o'&&s[i+2]=='s'&&s[i+3]=='('){
				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
				v[i]=cos(get_num(i+4,len));
			}
		}else if(s[i]=='t'){
			if(s[i+1]=='a'&&s[i+2]=='n'&&s[i+3]=='('){
				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
				v[i]=tan(get_num(i+4,len));
			}
		}else if(s[i]=='e'){
			if(s[i+1]=='x'&&s[i+2]=='p'&&s[i+3]=='('){
				s[i]=s[i+1]=s[i+2]=s[i+3]='#';
				v[i]=exp(get_num(i+4,len));
			}
		}
	}
	
	for(i=0;i<len;i++)//括号的位置 
		if(s[i]==')') {
			cnt++;part2[cnt]=i;
			cnt1=1;
			for(j=i-1;j>=0;j--){
				if(s[j]==')') cnt1++;
				else if(s[j]=='(') cnt1--;
				if(!cnt1){part1[cnt]=j;break;}
			}
		}
	cnt++;part1[cnt]=0;part2[cnt]=len;
	for(k=1;k<=cnt;k++){
		l=part1[k],r=part2[k];
		s[l]=s[r]='#';l++; 
		flagp=1;flag1=flag2=flag3=num1=num2=0;//初始化 
		while(flagp){
		flagp=0;
		for(i=r-1;i>=l;i--){
			if(s[i]=='^'){
				flagp=flag1=1;flagcur=cur1=cur2=cur2len=curl=curr=0;
				for(j=i-1;j>=l;j--)
					if(s[j]=='+'||s[j]=='-'||s[j]=='*'||s[j]=='/'||s[j]=='^'){curl=j+1;break;}
					else if(j==l) curl=j;
				if(s[curl]=='#') curnum1=v[curl];
				else{
					for(j=curl;j<i;j++){
						ch=s[j];
						if(ch>='0' && ch<='9'){
							tmp=ch-'0';
							if(flagcur==0) cur1=cur1*10+tmp;
							else{
								cur2=cur2*10+tmp;cur2len++;
							}
						}else if(ch=='.') flagcur=1;
						s[j]='#';
					}
					curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 符号左的数字
				}
				curr=i+1;flagcur=cur1=cur2=cur2len=0;
				if(s[curr]=='#') curnum2=v[curr];
				else{
					for(j=curr;j<r;j++){
						ch=s[j];
						if(ch>='0' && ch<='9'){
							tmp=ch-'0';
							if(flagcur==0) cur1=cur1*10+tmp;
							else{
								cur2=cur2*10+tmp;cur2len++;
							}
						}else if(ch=='.') flagcur=1;
						else{
						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2符号右的数字
						  break;
						}
						curnum2=cur1+cur2*pow(10,-cur2len);s[j]='#';
					}
				}
				v[curl]=pow(curnum1,curnum2);
				s[i]='#';break;
			}
		}
	}
	flagp=1;curnum1=curnum2=0;
		while(flagp){
		flagp=0;
		for(i=l;i<r;i++){
			if(s[i]=='*' || s[i]=='/'){
				flagp=flag2=1;flagcur=cur1=cur2=cur2len=curl=curr=0;
				for(j=i-1;j>=l;j--)
					if(s[j]=='+'||s[j]=='-'){curl=j+1;break;}
					else if(j==l) curl=j;
				if(s[curl]=='#') curnum1=v[curl];
				else{
					for(j=curl;j<i;j++){
						ch=s[j];
						if(ch>='0' && ch<='9'){
							tmp=ch-'0';
							if(flagcur==0) cur1=cur1*10+tmp;
							else{
								cur2=cur2*10+tmp;cur2len++;
							}
						}else if(ch=='.') flagcur=1;
						s[j]='#';
					}
					curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 符号左的数字
				}
				curr=i+1;flagcur=cur1=cur2=cur2len=0;
				if(s[curr]=='#') curnum2=v[curr];
				else{
					for(j=curr;j<r;j++){
						ch=s[j];
						if(ch>='0' && ch<='9'){
							tmp=ch-'0';
							if(flagcur==0) cur1=cur1*10+tmp;
							else{
								cur2=cur2*10+tmp;cur2len++;
							}
						}else if(ch=='.') flagcur=1;
						else{
						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2符号右的数字
						  break;
						}
						curnum2=cur1+cur2*pow(10,-cur2len);s[j]='#';
					}
				}
				if(s[i]=='*') v[curl]=curnum1*curnum2;
				else v[curl]=curnum1/curnum2;
				s[i]='#';break;
			}
		}
	}
	flagp=1;
	while(flagp){
		flagp=0;
		for(i=l;i<r;i++){
			if(s[i]=='+' || s[i]=='-'){
				flag3=1;//是否存在加减法 
				flagp=1;flagcur=cur1=cur2=cur2len=curl=curr=0;
				curl=l;
				if(i==l && s[i]=='-') {
					curnum1=0;
				}else{
					if(s[curl]=='#') curnum1=v[curl];
					else{
						for(j=curl;j<i;j++){
							ch=s[j];
							if(ch>='0' && ch<='9'){
								tmp=ch-'0'; 
								if(flagcur==0) cur1=cur1*10+tmp;
								else{
									cur2=cur2*10+tmp;cur2len++;
								}
							}else if(ch=='.') flagcur=1;
							s[j]='#';
						}
						curnum1=cur1+cur2*pow(10,-cur2len);//curnum1 符号左的数字
					}
				}
				curr=i+1;flagcur=cur1=cur2=cur2len=0;
				if(s[curr]=='#') curnum2=v[curr];
				else{
					for(j=curr;j<r;j++){
						ch=s[j];
						if(ch>='0' && ch<='9'){
							tmp=ch-'0';
							if(flagcur==0) cur1=cur1*10+tmp;
							else{
								cur2=cur2*10+tmp;cur2len++;
							}
						}else if(ch=='.') flagcur=1;
						else{
						  curnum2=cur1+cur2*pow(10,-cur2len);//curnum2符号右的数字
						  break;
						}
						curnum2=cur1+cur2*pow(10,-cur2len);s[j]='#';
					}
				}
				if(s[i]=='+') curnum1=curnum1+curnum2;
				else curnum1=curnum1-curnum2;
				num1+=curnum1;
				s[i]='#';break;
			}
		}
	}
	if(!flag3 && (flag2 ||flag1)) num1=v[l];
		l--;v[l]=num1;
	}
	flag4=0;
	if(!flag3 && (flag2 || flag1)) num1=v[0];
	if(!flag3 && !flag2 && !flag1){
		flagcur=cur1=cur2=cur2len=0;
		for(i=1;i<len;i++){
			ch=s[i];
			if(ch>='0'&&ch<='9'){
				tmp=ch-'0';
				if(flagcur==0) cur1=cur1*10+tmp;
				else{
					cur2=cur2*10+tmp;cur2len++;
				} 
			}else if(s[i]=='.') flagcur=1;
			else if(s[i]=='#') flag4=1;
		}
		if(!flag4){
			num1 = cur1;
			if(cur2) num1=num1+cur2*pow(10,-cur2len);
		}else num1=v[1];
	}
	printf("%f",num1);
}
int main(){
	calc();
}
