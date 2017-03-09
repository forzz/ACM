#include<iostream>
#include<stdio.h>
#include<string.h>
#define MOD 1000000007
#define LL long long
using namespace std;
int k,l,x,y;
LL cnt;
string a;
LL pow(LL a,LL b) //二进制快速幂
{
    LL r=1;
    while(b)
    {
        if(b&1)r*=a,r%=MOD;//b为奇数
        a*=a,a%=MOD;//b为偶数
        b>>=1;
    }
    return r;
}
int main(void)
/*
能被5整除，那么要么是0 要么是5结尾，所以对于只有一个串的时候每次都找0 5结尾的数，它前面的可以选或者不选就是总共2^i种可能。
当有多个串时，第2,3,4，。。。k个串中可能性就是第一个串中对应位置的 i+strlen(str), 第一个串中符合条件的2^i的和为tmp,
那么k个串中符合条件的总和就是 tmp*(1+2^len+2^（2len）+ 2^（3len）....+2^（klen）)，这是个等比数列求和问题，可以化成（1-2^(len*k)）/ (1-2^(len)) %mod
*/
{
    cin>>a>>k;
    l=a.size();
    for(int i=0;i<l;i++)
        if(a[i]=='0' || a[i]=='5')cnt+=pow(2,i),cnt%=MOD;//求得temp
    x=pow(2,l);
    y=pow(x,k);
    x=((1-x)%MOD+MOD)%MOD;//分子
    y=((1-y)%MOD+MOD)%MOD;//分母
    cout<<(cnt*((y*pow(x,MOD-2))%MOD))%MOD<<endl;//ab≡1(mod p)【p是素数】 逆元b就是a^(p-2)
    return 0;
}
