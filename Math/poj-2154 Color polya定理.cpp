//欧拉函数:φ(n) = 小于 n 且和 n 互质的正整数(包括1)的个数(n为正整数)      对于素数 p ， φ(p) = p -1
//（1）两个不同素数 p， q， n=p*q，则φ(n) = (p -1) * (q -1)
//（2）p,q是两个互质的正整数， n=pq则:φ(n) = φ(p)φ(q)
//（3）当b是质数， a%b=0，则:φ(ab)=φ(a)b
//（4）(4) 对任意n:φ(n) = n(1-1/p1)(1-1/p2)...(1-1/pn) p是n的质因数
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int euler(int n,int m){ //返回euler(n)
     int res=n,a=n;
     for(int i=2;i*i<=a;i++){
         if(a%i==0){
             res=res/i*(i-1);//先进行除法是为了防止中间数据的溢出
             while(a%i==0) a/=i;
         }
     }
     if(a>1) res=res/a*(a-1);
     return res%m;
}

int mod_exp ( int a, int b, int m )//a^b %m要避免计算中间结果溢出
{
    int ret = 1;
    a = a % m;
    while ( b >= 1 )
    {
        if ( b & 1 )//奇数
            ret = ret * a % m;
        a = a * a % m;//偶数
        b >>= 1;
    }
    return ret;
}

int Polya ( int n, int m )
{//翻转不考虑
    int ret = 0;
    for ( int l = 1; l*l <= n; l++ )//枚举长度
    {
        if ( n % l ) continue;//有长度为l的循环，就会有长度为n/l的循环
        ret = (ret + euler(l,m) * mod_exp(n, n/l-1, m)) % m;
        if ( l * l == n ) break;
        ret = (ret + euler(n/l,m) * mod_exp(n, l-1, m)) % m;//枚举循环长度i，找出相应的i的个数：gcd(n,i)=n/i;
    }
    return ret;
}

int main()
//gcd（i,n)表示了循环节的个数。用L表示循环节的长度L=n/gcd(i,n)，
//如果我们枚举L，求出对于每一个L有多少个i, 使得 L = n / gcd (i,n)， 那么我们实际上也得到了循环节个数为 n / L 的置换个数。
//循环节长度为L的置换有Euler(L)个
{
    int n, m, cs;
    scanf("%d",&cs);
    while ( cs-- )
    {
        scanf("%d%d",&n,&m);
        printf("%d\n",Polya(n,m));
    }
    return 0;
}
/*
正整数的因数分解可将正整数表示为一连串的质因子相乘，质因子如重复可以指数表示。
根据算术基本定理，任何正整数皆有独一无二的质因子分解式。只有一个质因子的正整数为质数。
每个合数都可以写成几个质数（也可称为素数）相乘的形式，这几个质数就都叫做这个合数的质因数。
*/
