#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
double p[3][1005][1005];//保存三种状态
double f[1005][1005];//从[i][j]点到终点的解
bool vis[1005][1005];
int R, C;
double DP(int x, int y)
{
    if(x==R && y==C) return 0; //到达终点的期望是0步
    if(x>R || y>C) return 0;
    if(vis[x][y]) return f[x][y];
    if(abs(p[0][x][y]-1)<1e-6) //如果永远都传送回原地，那么不用算了
    {
        vis[x][y]=1;
        return f[x][y]=0;
    }
    vis[x][y]=1;
    return f[x][y]=(2+p[1][x][y]*DP(x, y+1)+p[2][x][y]*DP(x+1, y))/(1-p[0][x][y]);
    //dp[i][j] = dp[i + 1][j] * mp[i][j][1] + dp[i][j + 1] * mp[i][j][0] + dp[i][j] * mp[i][j][2] + 2
}

int main()
{
    while(scanf("%d%d", &R, &C)!=EOF)
    {
        for(int i=1; i<=R; i++)
            for(int j=1; j<=C; j++)
                scanf("%lf%lf%lf", &p[0][i][j], &p[1][i][j], &p[2][i][j]);
        memset(f, 0, sizeof(f));
        memset(vis, 0, sizeof(vis));
        printf("%.3lf\n", DP(1, 1));
    }
    return 0;
}
