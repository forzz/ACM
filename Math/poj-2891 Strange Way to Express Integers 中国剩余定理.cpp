#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long LL;
const int N = 1005;
LL a[N], m[N];

LL gcd(LL a,LL b)//欧几里得
{
    return b? gcd(b, a % b) : a;
}

void extend_Euclid(LL a, LL b, LL &x, LL &y)  //扩展欧几里得
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    extend_Euclid(b, a % b, x, y);
    LL tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

LL Inv(LL a, LL b)//求a关于b的逆元
{
    LL d = gcd(a, b);
    if(d != 1) return -1;
    LL x, y;
    extend_Euclid(a, b, x, y);
    return (x % b + b) % b;//保证x为非负数
}
/*
对于 x=a1(mod m1)     x=a2(mod m2)   由x=a1+m1*x1=a2+m2*x2
相当于解不定方程：x*m1+y*m2=a2-a1
先求解方程：x*m1+y*m2=a2-a1=gcd(m1,m2)
得出解x，则方程x*m1+y*m2=a2-a1的解x0=x*(a2-a1)/gcd(m1,m2)=x*c/d
令s=m2/d，那么最小解x0为：x0=(x0%s+s)%s即可得出解x=a1+x0*m1
然后将x赋值给a3，lcm(m1,m2)赋值给m3，继续求解。直到最后
*/
bool merge(LL a1, LL m1, LL a2, LL m2, LL &a3, LL &m3)
{
    LL d = gcd(m1, m2);
    LL c = a2 - a1;
    if(c % d) return false;//方程无法合并
    c = (c % m2 + m2) % m2;
    m1 /= d;//全除以d，保证求得x0为最小解（两者互素）
    m2 /= d;
    c /= d;
    c *= Inv(m1, m2);//x0=x*(a2-a1)/gcd(m1,m2)=x*c/d
    c %= m2;
    c *= m1 * d;//m1已经除过d，乘回来
    c += a1;//x=a1+x0*m1
    m3 = m1 * m2 * d;//m1和m2都已经除过1次d，需要再乘1次 这是lcm
    a3 = (c % m3 + m3) % m3;
    return true;
}
LL CRT(LL a[], LL m[], int n)//mi不两两互素，需要每2个同余方程进行合并
{
    LL a1 = a[1];
    LL m1 = m[1];
    for(int i=2; i<=n; i++)
    {
        LL a2 = a[i];
        LL m2 = m[i];
        LL m3, a3;
        if(!merge(a1, m1, a2, m2, a3, m3))//合并同余方程
            return -1;
        a1 = a3;//维护a1和m1
        m1 = m3;
    }
    return (a1 % m1 + m1) % m1;//此时只有一个方程
}
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1; i<=n; i++)
            scanf("%lld%lld",&m[i], &a[i]);
        LL ans = CRT(a, m, n);
        printf("%lld\n",ans);
    }
    return 0;
}
