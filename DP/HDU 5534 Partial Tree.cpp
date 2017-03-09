#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
int t;
int n;
int f[2015];
int dp[2015];
int main()
{
	cin>>t;
	while (t--)
	{
		for (int i=1;i<=2014;i++)
		{
			dp[i]=-99999999;
		}
		cin>>n;
		for (int i=0;i<n-1;i++)
			cin>>f[i];
		for (int i=1;i<n-1;i++)
			f[i]-=f[0];//所有的点全部加入度数1，保证结果成立
		int ans=f[0]*n;
		for (int i=1;i<=n-2;i++)//完全背包
			for (int j=1;j<=i;j++)
			{
				dp[i]=max(dp[i],dp[i-j]+f[j]);
			}
		cout<<dp[n-2]+ans<<endl;
	}
}
