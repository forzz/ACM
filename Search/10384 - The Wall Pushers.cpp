#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
int d[4] = {1,2,4,8};
int dx[4] = {0,-1,0,1};//四种方向
int dy[4] = {-1,0,1,0};
int ans[35];
int g[5][7];
bool f[5][7];
char str[] = "WNES";
int solve(int x, int y)//判断xy是否为出口
{
    if(x == 1 && (g[x][y]&2) == 0)//直接判断能否被整除
        return 1;
    if(x == 4 && (g[x][y]&8) == 0)
        return 3;
    if(y == 1 && (g[x][y]&1) == 0)
        return 0;
    if(y == 6 && (g[x][y]&4) == 0)
        return 2;
    return -1;
}

bool ida_star(int x, int y, int now, int max)//最大深度max，当前深度now
{
    if(now > max)
        return false;
    int num = solve(x, y);//xy编号
    if(num != -1)//xy是外围障碍，已经走出迷宫
    {
        ans[now] = num; //维护结果
        return true;
    }
    for(int i=0;i<4;i++)//四种方向
    {
        int tx = x+dx[i];
        int ty = y+dy[i];
        if((tx>=1 && tx <=4)&&(ty >= 1 && ty <= 6)&&(f[tx][ty] == 0))//在图内且未访问过
        {
            if((g[x][y] & d[i]) == 0)//此点该方向无墙
            {
                f[tx][ty] = 1;
                ans[now] = i;
                if(ida_star(tx, ty, now+1, max))
                    return true;
                f[tx][ty] = 0;//恢复状态
            }
            else if((g[tx][ty]&d[i]) == 0)//此点该方向有墙，下一点该方向无墙
            {
                if((tx+dx[i]>=1) && (tx+dx[i] <=4)&&(ty+dy[i] >= 1)&&(ty+dy[i] <= 6))//下下点是否在图内
                g[tx+dx[i]][ty+dy[i]]+=d[(i+2)%4];//下下点墙变为相反方向
                f[tx][ty] = 1;
                g[tx][ty] += d[i];
                g[x][y] -= d[i];
                ans[now] = i;
                if(ida_star(tx, ty, now+1, max))
                    return true;
                if(tx+dx[i]>=1 && tx+dx[i] <=4
                   && ty+dy[i] >= 1 && ty+dy[i] <= 6)
                    g[tx+dx[i]][ty+dy[i]]-=d[(i+2)%4];
                g[tx][ty] -= d[i];
                g[x][y] += d[i];
                f[tx][ty] = 0;
            }
        }
    }
    return false;
}

int main()
{
    int x,y;
    while(cin>>y>>x && x && y)
    {
        for(int i=1;i<=4;i++)
            for(int j=1;j<=6;j++)
                cin>>g[i][j];
        for(int m=0;;m++) //迭代加深搜索
        {
            memset(f, 0, sizeof(f));
            f[x][y] = 1;
            if(ida_star(x,y,0,m))
            {
                for(int i=0;i<=m;i++)
                    cout<<str[ans[i]];
                cout<<endl;

                break;
            }
        }
    }
    return 0;
}
