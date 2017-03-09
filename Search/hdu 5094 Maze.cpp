#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
const int maxn = 55 ;
const int N = 11 ;
struct node   //bfs保存当前坐标，步数和已掌握的钥匙
{
    int x,y;
    int step,sta;
    node() {}
    node(int _x,int _y,int _step,int _sta): x(_x),y(_y),step(_step),sta(_sta) {} //构造函数
};
bool visited[maxn][maxn][1<<N];
int a[maxn][maxn][maxn][maxn],key[maxn][maxn];
int n,m,p;
void input()
{
    int k,s,x,y,dx,dy,g;
    scanf("%d",&k);
    for(int i=0;i<k;i++)
    {
         scanf("%d %d %d %d %d",&x,&y,&dx,&dy,&g);
         a[x][y][dx][dy]=g;
         a[dx][dy][x][y]=g;
    }
    scanf("%d",&s);
    for(int i=0;i<s;i++)
    {
         scanf("%d %d %d",&x,&y,&g);
         int t=1<<(g-1); //t保存钥匙信息
         if((key[x][y] & t)==0)   key[x][y] = key[x][y] | t;  //如果该位置没该钥匙，补上
    }
}
bool judge(int xx,int yy)
{
    if(xx>=1 && xx<=n && yy>=1 && yy<=m)  return true;
    return false;
}
int bfs()
{
     queue <node> q;
     q.push(node(1,1,0,key[1][1]));
     visited[1][1][key[1][1]]=1;  //标记当前状态
     while(!q.empty())
     {
          node c=q.front(); q.pop();
          if(c.x==n && c.y==m)  return c.step; //找到结果
          for(int i=0;i<4;i++)
          {
               int xx=c.x+d[i][0],yy=c.y+d[i][1],sp = c.sta | key[xx][yy];//sp表示当前拥有的钥匙
               int t=a[c.x][c.y][xx][yy];
               int w=1<<(t-1); //w表示门的类型（压缩状态）
               if(judge(xx,yy) && ((t==-1) || (t!=0 && (c.sta & w))) && !visited[xx][yy][sp])
               {
                   visited[xx][yy][sp]=1;
                   q.push(node(xx,yy,c.step+1,sp));
               }
          }
     }
     return -1;
}
int main()
{
    while(scanf("%d %d %d",&n,&m,&p)!=EOF)
    {
        memset(visited,0,sizeof(visited));
        memset(a,-1,sizeof(a));
        memset(key,0,sizeof(key));
        input();
        printf("%d\n",bfs());
    }
    return 0;
}
