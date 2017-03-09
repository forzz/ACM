#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N=1005;
const int mod=1000000007;
char str[N];
int dp[N][N],sum[N][N];
int main()
{
	while(scanf("%s",str+2)!=EOF)
	{
		memset(dp,0,sizeof(dp));
		memset(sum,0,sizeof(sum));
		int n=(int)strlen(str+2);
		dp[1][1]=sum[1][1]=1;
		for(int i=2;i<=n+1;i++)//i从第二位开始，i=1时只有dp[1][1]可行，其他为0，给的‘I‘和‘D’也是从第二个开始
		{
			for(int j=1;j<=i;j++)
			{
				if(str[i]=='I'||str[i]=='?') dp[i][j]=(dp[i][j]+sum[i-1][j-1])%mod;//j比j-1要小
				if(str[i]=='D'||str[i]=='?')
				{
					dp[i][j]=(dp[i][j]+((sum[i-1][i-1]-sum[i-1][j-1])%mod+mod)%mod)%mod;
					//sum就是前缀和（前m个数的和）
				}
				sum[i][j]=(dp[i][j]+sum[i][j-1])%mod;//更新前缀和
			}
		}
		printf("%d\n",sum[n+1][n+1]);
	}
	return 0;
}
/*
可以用dp[i][j]表示：处理完第i位，序列末尾位j的序列共有多少个。最后的结果为sigma{dp[N][i]}，1≤i≤N

处理dp[1~i][]的过程中i是依次1~n相加。处理完dp[i-1][]后，加入的数即为i，而dp[i][j]是要将i放进去j换出来，而这里有一种将i放进去j换出来，同时不影响升降顺序的方法是：

将dp[i-1][j]的i-1个数的序列中 ≥j 的数都加1，这样i-1变成了i，j变成了j+1，而j自然就补在后面了。

所以对”ID“序列依次处理即可，初始条件：dp[1][1] = 1; 即只有{1}。

处理‘I’：dp[i][j] = sigma{dp[i-1][x]}，其中1≤x≤j-1，可进一步简化，dp[i][j] = dp[i-1][j-1]+dp[i-1][j-1]

处理‘D’：dp[i][j] = sigma{dp[i-1][x]}，其中j≤x≤i-1，可进一步简化，dp[i][j] = dp[i-1][j+1]+dp[i-1][j]

处理‘?’：dp[i][j] = sigma{dp[i-1][x]}，其中1≤x≤i-1，直接计算
*/
