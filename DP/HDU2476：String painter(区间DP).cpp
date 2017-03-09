#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
const int MAXN=110;
int dp[MAXN][MAXN];
char str1[MAXN],str2[MAXN];
int ans[MAXN];
int main()
{
    while(scanf("%s%s",str1,str2)==2)
    {
        int n=strlen(str1);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++)  //初始化dp（假设每个位置都单独染色）
            for(int j=i;j<n;j++)
                dp[i][j]=j-i+1;
        //先直接DP求出从空白串变成str2
        for(int i=n-2;i>=0;i--)//逆序
            for(int j=i+1;j<n;j++)
            {
                dp[i][j]=dp[i+1][j]+1; //因为染前面肯定是在后面染色之后
                for(int k=i+1;k<=j;k++) //分隔i到j区间，若存在k，则k不需要变。
                    if(str2[i]==str2[k]) //区间dp关键在于断开区间
                        dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k][j]);
            }
        for(int i=0;i<n;i++)//考虑str1，由于从外向内刷，若是最外围相同，不需要变
        {
            ans[i]=dp[0][i];
            if(str1[i]==str2[i])//初始化ans
            {
                if(i==0)ans[i]=0;
                else ans[i]=ans[i-1];
            }
            for(int j=0;j<i;j++)
                ans[i]=min(ans[i],ans[j]+dp[j+1][i]);
        }
        printf("%d\n",ans[n-1]);
    }
    return 0;
}
