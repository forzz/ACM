#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a[10][10], vis[10][10], n, deep;
//将整个方格分为3个部分，第一部分是和左上角在一个连通块的，标为1，第二部分为和连通块颜色不一样，但是相邻的，标为2，
//可以知道，标为2的部分是我们染色的选择，将连通块染成2的颜色，那样就将这个方块加入到连通块中。
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
bool ok;

int Astar()//估价函数，计算除左上角连通块之外还有多少颜色，即最少要染的次数
{
    int book[10], h = 0;
    memset(book, 0, sizeof(book));
    for(int i = 1; i <= n; i++)
          for(int j = 1; j <= n; j++)
              if(vis[i][j]!=1 && !book[a[i][j]])//与左上角不连通并且当前颜色没被录入
                  book[a[i][j]]++, h++;
    return h;
}

void dfs(int x, int y, int color)//把颜色为color的格子并入左上角连通块，每一次dfs只考虑和左上角连通的格子和与连通格相邻的格子，减少递归
//vis[i][j]为1表示格子与左上角连通,为2表示与连通块相邻的格子,0为其他，
{
    vis[x][y] = 1;
    for(int i = 0; i < 4; i++)
    {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx>=1&&nx<=n&&ny>=1&&ny<=n)
        {
            if(vis[nx][ny] == 1)continue;
            vis[nx][ny] = 2;
            if(a[nx][ny] == color)
                  dfs(nx, ny, color);//继续搜，直到没有相同颜色
        }
    }
}

int fill(int color)//左上角染成color色后把vis[i][j]==2的格子染成color色
{//宁可在每一层递归中多跑两个循环，也要想办法减少无用的递归 ！
    int cnt = 0;
    for(int i = 1; i <= n; i++)
          for(int j = 1; j <= n; j++)
              if(vis[i][j]==2&&a[i][j]==color)  //符合情况进行染色
            {
                cnt++;
                dfs(i, j, color);
            }
    return cnt;
}

void IDAstar(int step)
{
    if(ok)return ;
    int h = Astar();
    if(h == 0)
    {
        cout<<step<<endl;
        ok = true;
        return ;
    }
    if(step+h>deep)return ;
    int tmp[10][10];//备份状态
    memcpy(tmp, vis, sizeof(tmp));
    for(int i = 0; i < 6; i++)//进行染色
    //染什么颜色不需要知道，只需要知道有多少格子与左上角同色，所以不用把颜色保存进状态中，只需要保存vis数组判断格子之间的关系即可
    {
        if(fill(i)==0)continue;//染色无效果 剪枝
        IDAstar(step+1);
        memcpy(vis, tmp, sizeof(vis));//恢复状态
    }
}

int main()
{
    while(scanf("%d", &n)!=EOF && n)
    {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &a[i][j]);
        ok = false;
        deep = 0;
        memset(vis, 0, sizeof(vis));
        dfs(1, 1, a[1][1]);//对左上角预处理
        while(!ok)
        {
            IDAstar(0);
            deep++;//一层一层加深搜索的深度
        }
    }
    return 0;
}
