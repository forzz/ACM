#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<set>
#include<queue>
#include<vector>
using namespace std;
#define ll long long
ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}
//求一组解(x,y)使得 ax+by = gcd(a,b), 且|x|+|y|最小(注意求出的 x,y 可能为0或负数)。
//下面代码中d = gcd(a,b)
//可以扩展成求等式 ax+by = c,但c必须是d的倍数才有解,即 (c%gcd(a,b))==0
void extend_gcd (ll a , ll b , ll& d, ll &x , ll &y) {
	if(!b){d = a; x = 1; y = 0;}
	else {extend_gcd(b, a%b, d, y, x); y-=x*(a/b);}
}
ll inv(ll a, ll n) { //计算%n下 a的逆。如果不存在逆return -1;
	ll d, x, y;
	extend_gcd(a, n, d, x, y);
	return d == 1 ? (x+n)%n : -1;
}
//n为a,m数组的长度[0,n-1]
//返回一个值x 表示 x==a[i]%m[i] 注意m的数都是互质的
ll china(ll n, ll *a,ll *m) {
	ll M = 1, d, y, x = 0;
	for(ll i = 0; i < n; i++) M *= m[i];
	for(ll i = 0; i < n; i++) {
		ll w = M /m[i];
		extend_gcd(m[i], w, d, d, y);
		x = (x + y*w*a[i]) % M;
	}
	return (x+M)%M;
}
#define N 10005
ll n,lcm,m,k;
ll A[N];
bool work(){
	if(lcm>n)return false;
	ll u = 0, v = A[0];
	for(ll i = 1; i < k; i++) {//合并同余方程(v和u是第一个方程 a和b是第二个方程)
		ll x, y, a = v, b = -A[i], c = -u-i, d;     //c代表当前c的总值
		extend_gcd(a,b,d,x,y);
		if(c%d)return false;
		ll t = b/d;
		x = x*c/d;
		x = (x%t+t)%t;  //求得新的x
		if(x<0)x-=t;
		u += v*x;//维护u
		v = v / gcd(v,A[i])*A[i];//这是新的除数lcm
	}
	if(u == 0) u += lcm;
	if(u+k-1>m)return false;
	for(ll i = 0; i < k; i++)
		if(gcd(lcm, u+i)!=A[i])return false;
	return true;
}
int main(){
	ll i;
	while(cin>>n>>m>>k) {
		for(i=0;i<k;i++)cin>>A[i];
		lcm = 1;
		for(i=0;i<k;i++) //求出行数
			lcm = lcm / gcd(lcm,A[i]) *A[i];
		work()?puts("YES"):puts("NO");
	}
	return 0;
}
