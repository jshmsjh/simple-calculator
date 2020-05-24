#include<stdio.h>
#include<math.h>
#include<string.h>
#define LL long long

int prime[100010];
//最大公约数 
LL gcd(LL a,LL b){
	if(b==0) return a;
	return gcd(b,a%b);
}

//最小公倍数 
LL lcm(LL a,LL b){
	LL c=gcd(a,b);
	return a*b/c;
}

//计算素数表 
void get_prime_list(int n){
	int i,j,cnt=0;
	int vis[100010];
	memset(vis,0,sizeof(vis));
	for(i=2;i<=n;i++){
		if(!vis[i]) prime[++cnt] = i;
		for(j=1;j<=cnt&&i*prime[j]<=n;j++){
			vis[i*prime[j]] = 1;
			if(i%prime[j] == 0) break;
		}
	}
	for(i=1;i<=cnt;i++) printf("%d ",prime[i]);
}

//质因数分解 
void get_prime(int x){
	int i,cnt=0;
	int res[100010];
	int n = ceil(x);
	for(i=2;i<=n;i++){
		while(!(x%i)){
			res[++cnt] = i;
			x /= i;
		}
	}
	for(i=1;i<=cnt;i++) printf("%d ",res[i]);
} 
int main(){
//	LL a,b;
//	scanf("%lld%lld",&a,&b);
//	LL res = lcm(a,b);
//	printf("%lld",res);
//	get_prime(100);
} 
