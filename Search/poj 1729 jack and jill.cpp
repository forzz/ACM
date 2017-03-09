#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<cmath>
#include<stack>
#include<iostream>
#include<queue>
using namespace std;
struct status
{
    public:
        int hx,hy;
        int Hx,Hy;
        int mindist;
        char moveh,moveH;
        int pre;
        int id;
        bool operator < (const status& r) const
        {
            return this->mindist<r.mindist;
        }
};
int fx[]={0,-1,0,1};
int fy[]={1,0,-1,0};
char mov[]="ENWS";
int g[50][50][50][50];//记录2个人的状态
int n;
int p;
char mp[100][100];
status way[1000000];//记录路径（保存每个节点的编号）因为每个节点会重复到达，不能直接保存路径。
int dist(int x1,int y1,int x2,int y2)//判断两者距离
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
void BFS(int hx,int hy,int Hx,int Hy)
{
    int i,j;
    memset(g,-1,sizeof(g));
    status x,y;
    p=0;
    x.hx=hx,x.hy=hy,x.Hx=Hx,x.Hy=Hy;  //起点信息保存在结构体x中
    x.id=p;
    x.pre=-1;
    int dis=dist(hx,hy,Hx,Hy);
    x.mindist=dis;//记录距离
    way[p++]=x;
    priority_queue<status> que;//优先队列
    que.push(x);
    while(!que.empty())
    {
        y=que.top();
        que.pop();
        if(mp[y.hx][y.hy]=='s'&&mp[y.Hx][y.Hy]=='S')//到达终点
        {
            printf("%.2f\n",sqrt(1.0*y.mindist));
            stack<char> st1,st2;
            while(y.pre!=-1)//读取之前路径
            {
                if(y.moveH!='*') //jack路径
                    st1.push(y.moveH);
                if(y.moveh!='*')  //jill路径
                    st2.push(y.moveh);
                y=way[y.pre];
            }
            while(!st1.empty())  //输出jack路径
            {
                printf("%c",st1.top());
                st1.pop();
            }
            puts("");
            while(!st2.empty())   //输出jill路径
            {
                printf("%c",st2.top());
                st2.pop();
            }
            puts("");
            break;
        }
        for(i=0;i<4;i++)  //jill进行bfs
        {
            int a=y.hx+fx[i];//更新jill信息
            int b=y.hy+fy[i];
            char moveh=mov[i];//方向
            if(mp[y.hx][y.hy]=='s')//到达s时退回更新
                a=y.hx,b=y.hy,moveh='*';//方向重置，不进行移动
            if(a>=0&&a<n&&b>=0&&b<n&&mp[a][b]!='*'&&mp[a][b]!='S'&&mp[a][b]!='H')  //jill符合情况下jack进行bfs
            {
                for(j=0;j<4;j++)
                {
                    int c=y.Hx+fx[j]; //更新jack信息
                    int d=y.Hy+fy[j];
                    char moveH=mov[j];
                    if(mp[y.Hx][y.Hy]=='S')//到达S时退回更新
                        c=y.Hx,d=y.Hy,moveH='*';//方向重置，不进行移动
                    if(c>=0&&c<n&&d>=0&&d<n&&mp[c][d]!='*'&&mp[c][d]!='s'&&mp[c][d]!='h')//jack符合情况下更新当前状态
                    {
                        dis=dist(a,b,c,d);//计算当前距离
                        dis=min(dis,y.mindist);//求最小距离
                        if(dis>g[a][b][c][d]||g[a][b][c][d]==-1)//每一个g保存当前最小双方距离，每个点可以走多次（之前不同的路径会影响最小距离）
                        {
                            x.hx=a,x.hy=b,x.Hx=c,x.Hy=d;//维护x中jack和jill坐标
                            x.id=p;
                            x.mindist=dis;
                            x.pre=y.id;//保存前一步的id
                            x.moveh=moveh;//保存面向
                            x.moveH=moveH;
                            way[p++]=x;//创建新id
                            que.push(x);
                            g[a][b][c][d]=dis;
                        }
                    }
                    if(mp[y.Hx][y.Hy]=='S')  //若jack到达S，只需一次for循环保存当前jill的路径，不需要再次for循环
                        break;
                }
            }
            if(mp[y.hx][y.hy]=='s') //若jill到达s，只需一次for循环保存当前jill的路径，不需要再次for循环
                break;
        }
    }
}
int main()
{
    int i,j,hx,hy,Hx,Hy;
    while(cin>>n,n)
    {
        for(i=0;i<n;i++)
        {
            cin>>mp[i];
            for(j=0;j<n;j++)//提前读出来，作为起点
                if(mp[i][j]=='h')
                    hx=i,hy=j;
                else
                    if(mp[i][j]=='H')
                        Hx=i,Hy=j;
            mp[i][j]='\0';
        }
        BFS(hx,hy,Hx,Hy);
    }
    return 0;
}
