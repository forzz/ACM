#include <iostream>
#include <cstdio>
#define  ll long long
using namespace std;
ll arr[90];
ll a,b,c,x,sx,ans,count,tmp;
int main(){
    while(scanf("%lld%lld%lld",&a,&b,&c)!=EOF){
        count=0;
        for(ll i=1;i<=81;i++){ //1e9的数每位最大为9，则各位之和最大为81
            sx=1;
            for(ll j=1;j<=a;j++) //枚举每一个i的a次方
                sx*=i;
            x=sx*b+c; //反向计算x
            tmp=x;ans=0;
            while(tmp){ //再反向计算x的各位数之和
                ans+=tmp%10;tmp/=10;
            }
            if(ans==i && x>=1 && x<1e9) //如果相等且x在范围之内，进行计数和存储
                arr[count++]=x;
        }
        if(count==0) printf("0\n"); //判断输出
        else{
            printf("%lld\n",count);
            for(int i=0;i<count-1;i++)
                printf("%lld ",arr[i]);
            printf("%lld\n",arr[count-1]);
        }
    }
    return 0;
}
