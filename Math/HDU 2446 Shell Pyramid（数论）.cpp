#include<cstdio>
#include<cmath>
#define ll unsigned long long
int main(){
	int t;ll n;
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		ll p=(ll)pow(n*6.0,1.0/3);p++; //p为可能堆数的最大值，减少搜索范围
		while((p*p*p-p)>=n*6.0)p--;//确定p为该堆的堆号
		n-=(p*p*p-p)/6;//n为当前堆中的序号
		ll k=(ll)(sqrt(2.0*n));k++;//k为当前堆的数目的最大值
		while(k*(k+1)/2>=n)k--; //k为前一层的层号
		ll j =k+1,c=n-k*(k+1)/2;  //c为列号
		printf("%lld %lld %lld\n",p,j,c);
	}
	return 0;
}
/*
给你一个数n，
每堆的数目1，3，6，....，n*（n+1）/2    n为层数
前n堆的和（1*1+2*2+3*3+...n*n+1+2+3+..+n）/2=（n*n*n+3*n*n+2*n）/6
则前n-1堆的和(n-1)*(n-1)*(n-1)+3*(n-1)*(n-1)+2*(n-1)=（n*n*n-n）/6   n为堆号
所以要求第几堆，我们可以先将(n*6)开三次方，然后比较它与n*n*n-n的关系。
*/
