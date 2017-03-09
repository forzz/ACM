#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[16][1600],map[16][16],sta[1600];
// dp[i][j]=max(dp[i][j],dp[i-1][k]+ans[j]); //从最开始到i行j列的最小花费
//即第i行的第j个状态是由第i-1行的第k个状态递推而来，同时加上当前行第j个状态的花费。
int n;
void solve()
{
    int num=(1<<n),ct=0;
    for(int i=0;i<num;i++)//预处理长为n的每一行存在的各种状态，二进制形式保存在sta数组中，接下来只需要遍历状态数即可
        if(  (i&(i<<1))==0 && (i&(i>>1))==0 )  //每个格子的相邻格都为空
            sta[ct++]=i;

    for(int i=1; i<=n; i++)     //枚举行数
        for(int j=0; j<ct; j++) //上一行的状态数
            for(int k=0; k<ct; k++) //当前行的状态数
                if(  !(sta[k]&sta[j])  &&  !(sta[k]&(sta[j]<<1)) &&  !(sta[k]&(sta[j]>>1)) )
                //k周围没有j，满足条件
                {
                    int sum=0;
                    for(int k1=0; k1<n; k1++)//创建辅助变量k1，找到k状态选中的格子，求出sum值
                        if(sta[k]&(1<<k1))
                            sum+=map[i][n-k1-1];
                    dp[i][k]=max(dp[i][k],dp[i-1][j]+sum);
                }
    int ans=0;
    for(int i=0;i<ct;i++)
        ans=max(ans,dp[n][i]);

    printf("%d\n",ans);
}
int main()
{
    char s[100];
    while(gets(s))
    {
        memset(dp,0,sizeof(dp));
        memset(map,0,sizeof(map));
        memset(sta,0,sizeof(sta));
        int t=strlen(s);
        n=0;
        for(int i=0;i<t;i+=3)
            map[1][n++]=(s[i]-'0')*10+s[i+1]-'0';//读入第一行，并且找到n
        for(int i=2;i<=n;i++)
            for(int j=0;j<n;j++)
                scanf("%d",&map[i][j]);
        solve();
        getchar();getchar();
    }
    return 0;
}
