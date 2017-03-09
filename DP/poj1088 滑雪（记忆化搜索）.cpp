#include<iostream>
#include<cstdio>
#include<string.h>
#include<algorithm>
const int N=105;
using namespace std;
int a[N][N];
int dp[N][N];//每个值代表一个结果
int dis[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int R,C;
int dfs(int x,int y)
{
    if(dp[x][y]!=0)
        return dp[x][y];//直接返回结果
    int maxx=0,s;
    for(int i=0;i<4;i++)//遍历上下左右4个情况后得到上一步的max
    {
        int dx=x+dis[i][0],dy=y+dis[i][1];
        if(dx>0&&dy>0&&dx<=R&&dy<=C&&a[dx][dy]<a[x][y])//保证存在高度差
        { s=dfs(dx,dy);
        maxx=max(maxx,s);
        }
    }
    dp[x][y]=maxx+1;
    return maxx+1;
}
int main()
{

    while(~scanf("%d%d",&R,&C))
    {
        for(int i=1;i<=R;i++)
          for(int j=1;j<=C;j++)
              scanf("%d",&a[i][j]);
        memset(dp,0,sizeof(dp));
        int maxn=-1;
        for(int i=1;i<=R;i++)
            for(int j=1;j<=C;j++)
                {
                    dp[i][j]=dfs(i,j);
                    maxn=max(maxn,dp[i][j]);
                    }
        printf("%d\n",maxn);
    }
    return 0;
}
