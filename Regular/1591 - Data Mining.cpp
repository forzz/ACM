#include<cstdio>
typedef long long LL;
int main(){
	LL n,sp,sq;
	while(~scanf("%lld%lld%lld",&n,&sp,&sq)){
		LL best=(LL)1<<62,a,b,aa=0,bb=0;
		for(a=0;a<32;++a)
			for(b=0;b<32;++b){
				//偏移量实际地址与其所在段的段地址之间的距离
				//Pofs=(n-1)*sp   n-1偏移量     
				LL cur=(((n-1)*sp+((n-1)*sp<<a))>>b)+sq;
				//q的最后一个元素所占的位置，代表的是空间K
				if(cur>=n*sq&&cur<best) best=cur,aa=a,bb=b;
			}
			printf("%lld %lld %lld\n",best,aa,bb);
	}
	return 0;
}