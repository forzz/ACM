#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
long long dp[70][70],a[70],sum[70];
long long pow(long long n)
{
    long long ans= 1;
    int i;
    for(i = 1; i<=n; i++)
        ans*=2;
    return ans;
}
int main()
{
    int t,i,j,k,s;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(sum,0,sizeof(sum));
        for(i = 1; i<=n; i++)
        {
            scanf("%lld",&a[i]);
            sum[i] = sum[i-1]+a[i];  //求得所有和
        }
        memset(dp,0,sizeof(dp));
        for(s = 0; s<=n; s++)//代表区间长度
        {
            for(i = 1; i<=n && i+s<=n; i++) //起点
            {
                j = i+s;
                if(s<=19)//小于20层,全压缩
                    dp[i][j] =a[i]*pow(j-i)*2;
                else//多于20，全不压缩
                    dp[i][j] = (sum[j]-sum[i-1])*2;
                for(k = i+1; k<j; k++)//区间dp
                    dp[i][j] = min(dp[i][j],dp[i][k]+dp[k+1][j]);//表示将i~j的区间分为i~k和k+1~j两部分，找出最优解
            }
        }
        printf("%lld\n",dp[1][n]);
    }
    return 0;
}
