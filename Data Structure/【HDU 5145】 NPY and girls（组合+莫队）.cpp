#include <iostream>
#include <cstdio>
#include <algorithm>
#include<cstring>
#define LL long long
using namespace std;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9+7;
int per;
/*
由于数目比较多，可以用乘法逆元搞下(1次除法相当于3次乘法的时间)
乘法逆元：a×b ≡1 (mod m) 称b是a关于m的乘法逆元
由费马小定理 X^(m-1) ≡ 1 (mod m)，X×X^(m-2) ≡ 1(mod m) 所以 X^(m-2) mop m 就是X的乘法逆元。
*/
LL pow_m(LL a,LL b)//快速幂
{
	LL ans = 1;
	while(b)
	{
		if(b&1) ans = (ans*a)%mod;
		b >>= 1;
		a = (a*a)%mod;
	}
	return ans;
}
LL Inv(LL a)//求逆元
{
	return pow_m(a,mod-2);
}

struct Range
{
	int l,r,id;
	bool operator < (const struct Range a)const
	{
		return l/per == a.l/per? r < a.r: l/per < a.l/per;
	}
}rg[30030];
LL ans[30030];
LL inv[30030];
int cla[30030];
int cnt[30030];
int main()
{
	for(int i = 1; i <= 30000; ++i)
		inv[i] = Inv(i);//求i的逆元
	int t,n,q;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&q);
		per = sqrt(n*1.0);//块数
		for(int i = 1; i <= n; ++i)    //保存每个权值
			scanf("%d",&cla[i]);
		for(int i = 0; i < q; ++i)//保存每个区间
		{
			scanf("%d%d",&rg[i].l,&rg[i].r);
			rg[i].id = i;
		}
		sort(rg,rg+q);
		int l = 1, r = 0;
		LL tmp = 1;
		memset(cnt,0,sizeof(cnt));
		for(int i = 0; i < q; ++i)
		{
			while(r < rg[i].r)
			{
				++r;
				cnt[cla[r]]++;
				tmp = tmp*(r-l+1)%mod*inv[cnt[cla[r]]]%mod;//维护区间
			}
			while(l > rg[i].l)
			{
				--l;
				cnt[cla[l]]++;
				tmp = tmp*(r-l+1)%mod*inv[cnt[cla[l]]]%mod;
			}
			while(r > rg[i].r)
			{
				tmp = tmp*cnt[cla[r]]%mod*inv[r-l+1]%mod;
				cnt[cla[r]]--;
				--r;
			}

			while(l < rg[i].l)
			{
				tmp = tmp*cnt[cla[l]]%mod*inv[r-l+1]%mod;
				cnt[cla[l]]--;
				++l;
			}
			ans[rg[i].id] = tmp;
		}
		for(int i = 0; i < q; ++i)
			printf("%lld\n",ans[i]);
	}
	return 0;
}
/*
对于单组询问[L,R] 假设有n中班级 每个班级有c个女生 总共m个女生 那么答案就是
C(m,c1)*C(m-c1,c2)*C(m-c1-c2,c3)*....*C(cn,cn)
因为C(m+1,n+1) = C(m,n)*(m+1/n+1)
同样C(m,n) = C(m+1,n+1)*(n+1/m+1)
*/
