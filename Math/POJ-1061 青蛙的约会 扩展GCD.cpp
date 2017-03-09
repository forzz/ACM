/*
构造方程 (x + m * s) - (y + n * s) = k * l(k = 0, 1, 2,...)
变形为 (n-m) * s + k * l = x - y。即转化为模板题，a * x + b * y = c，是否存在整数解。
*/
#include <stdio.h>
long long gcd(long long a,long long b)  //辗转相除求最大公约数
{
    return b?gcd(b,a%b):a;
}
void exgcd( long long int a, long long int b, long long int &x, long long int &y )
{
    if( b== 0 )
    {
        x= 1;
        y= 0;
        return;
    }
    exgcd( b, a% b, x, y );
    long long int t= x;
    x= y;
    y= t- a/ b* y;
    return;
}
//1、先计算Gcd(a, b)，若n不能被Gcd(a, b)整除，则方程无整数解；否则，在方程两边同时除以Gcd(a, b)，得到新的不定方程a' * x + b' * y = n'，此时Gcd(a', b')=1;
//2、求出方程a' * x + b' * y = 1的一组整数解x0, y0，则n' * x0,n' * y0是方程a' * x + b' * y = n'的一组整数解；
//3、根据数论中的相关定理，可得方程a' * x + b' * y = n'的所有整数解为：
//x = n' * x0 + b' * k
//y = n' * y0 - a' * k
//(t为整数)
int main(  )
{
    long long int x, y, m, n, l;
    while( scanf( "%lld %lld %lld %lld %lld", &x, &y, &m, &n, &l )!= EOF )
    {
        long long int a= n- m, b= l, c= x- y, p, q;
        long long int d= gcd( a, b );
        if( c% d )//a*x + b*y = c 有解的充要条件：c%gcd(a,b)==0
        {
            puts( "Impossible" );
            continue;
        }
        a/= d, b/= d, c/= d;
        exgcd( a, b, p, q );  //
//此时方程的所有解为：x = c*p - b*k,  x与cp关于b同余那么根据最小整数原理，一定存在一个最小的正整数，
//它是 a 关于m 的逆元，而最小的肯定是在（0 , m）之间的，而且只有一个。 当 m 是负数的时候，我们取 m 的绝对值就行了，
//当 x0 是负数的时候，他模上 m 的结果仍然是负数，我们仍然让对b取模，然后结果再加上b就行了
        p*= c;//将整个方程扩大c倍，让右边为c
        long long int ans= p% b;//求最小解
        while( ans< 0 )
        {
            ans+= b;
        }
        printf( "%lld\n", ans );
    }
}
