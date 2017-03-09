#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#define INF 99999999
using namespace std;
char maze[111][111];
int n,m,k,t;
int ox,oy,fx,fy;
struct node
{
        int x,y,t;
        node() {}
        node(int _x,int _y,int _t): x(_x),y(_y),t(_t) {} //构造函数
};
int vis[111][111][11];  //数组开小了会WA
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
void bfs()
{
        queue<node> q;
        q.push(node(ox,oy,0));
        vis[ox][oy][0]=1;
        while(!q.empty())
        {
                node c=q.front();   q.pop();
                if(c.x==fx&&c.y==fy){
                        cout<<c.t<<endl;
                        return;
                }
                for(int i=0;i<4;i++)
                {
                        int xx=c.x+dx[i];    int yy=c.y+dy[i];     int tt=c.t+1;
                        if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&vis[xx][yy][tt%k]==0)
                        {
                                if(maze[xx][yy]!='#'||(maze[xx][yy]=='#'&&!(tt%k)))
                                        q.push(node(xx,yy,tt));
                                        vis[xx][yy][tt%k]=1;
                        }
                }
        }
            printf("Please give me another chance!\n");
}
int main ()
{
        int T;   cin>>T;
        while(T--)
        {
                memset(vis,0,sizeof(vis));
                memset(maze,-1,sizeof(maze));
                t=0;
                cin>>n>>m>>k;
                for(int i=1;i<=n;i++)
                        for(int j=1;j<=m;j++)
                        {
                                cin>>maze[i][j];
                                if(maze[i][j]=='Y')    {   ox=i; oy=j;  }
                                if(maze[i][j]=='G')    {   fx=i; fy=j;  }
                        }
                bfs();
        }
        return 0;
}
