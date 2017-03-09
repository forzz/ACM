#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
const int MAXN=255;
const int INF=1000000000;
int cap[MAXN][MAXN],flow[MAXN][MAXN],low[MAXN][MAXN],high[MAXN][MAXN];
//cap[][]网络中的容量,flow[][]流量分配,low[][],high[][]流量上下界
int r[MAXN],c[MAXN],q[MAXN],in[MAXN],out[MAXN],d[MAXN];
//in[u]:u所有入边的流量下界和,out[u]:u所有出边的流量下界和,fa[]:dinic中的层次
bool vist[MAXN];
void Init()
{
    memset(in,0,sizeof(in));
    memset(out,0,sizeof(out));
    memset(low,0,sizeof(low));
    memset(cap,0,sizeof(cap));
    memset(high,0,sizeof(high));
    memset(flow,0,sizeof(flow));
}

bool bfs(int s,int t,int n)//建立层次网络
{
    int i,tmp;
    memset(d,-1,sizeof(d));
    queue<int>Q;
    Q.push(s);
    d[s]=0;
    while(!Q.empty())
    {
        tmp=Q.front();
        Q.pop();
        for(i=0;i<n;i++)
            if(cap[tmp][i]>0&&d[i]==-1)
            {
                d[i]=d[tmp]+1;
                Q.push(i);
            }
    }
    if(d[t]!=-1)return true;
    else return false;
}
int dfs(int k,int t,int n,int sum)//扩展流量
{
    if(k==t)return sum;
    int i,os=sum;
    for(i=0;i<n;i++)
        if(d[i]==d[k]+1&&cap[k][i]>0)
        {
            int a=dfs(i,t,n,min(sum,cap[k][i]));
            cap[k][i]-=a;
            cap[i][k]+=a;
            flow[k][i]+=a;
            flow[i][k]-=a;
            sum-=a;
        }
    return os-sum;
}
int dinic(int s,int t,int n)
{
    int ans=0;
    while(bfs(s,t,n))
        ans+=dfs(s,t,n,INF);
    return ans;
}

void solve(int s,int t,int num,int n,int m)      //num为节点个数,n*m方阵
{
    int i,j,ss,tt,res,sum=0;
    ss=num;
    tt=num+1;
//建立附加网络
    for(i=0;i<num;i++)//都是从0开始枚举
        for(j=0;j<num;j++)
        {
            cap[i][j]=high[i][j]-low[i][j];        //该边容量为上下界流量之差
            out[i]+=low[i][j];                //统计点i所有出边的流量下界之和
            in[j]+=low[i][j];                   //统计点j所有入边的流量下界之和
            sum+=low[i][j];                     //所有边的流量下界之和
        }
    for(i=0;i<num;i++)                   //添加附加源点ss和汇点tt建立附加网络
    {//ss到每个结点的边下界就是该结点入边下界容量和,各点到tt边的下界容量为该结点出边下界容量和。
        cap[ss][i]=in[i];
        cap[i][tt]=out[i];
    }
    cap[t][s]=INF; //在附加网络中连边cap[t][s]=INF，将t和s间连一条无穷容量的边，使之成为无源汇的上下界的流量图。
/*
无源汇带上下界的可行流：
1.记录每个点的D = (每条进入它的弧的下界) 减去 (由它出发的弧的下界)。
如果大于0，得到的就是积累在本节点的流量，于是建立一个汇点，把流导给它。容量为D。
如果小于0，得到的就是本节点所需要进入的流量，建立一个源点s，跟它相连，容量为-D。
2.当然原来容量网络的每条弧保持一样，容量变为上界 减去 下界。
对于构造出来的图我们叫它伴随网络，（当然它的每条弧下界都为0）只有伴随网络的最大流使得从源点S出发，
每条弧都满了（此时连到T的弧也一定会满），原来网络才有可行流。
*/
    res=dinic(ss,tt,num+2);         //对附加网络求解最大流
    if(res!=sum)                     //附加网络的最大流不等于所有下界之和,则无解
    {
        printf("IMPOSSIBLE\n");
        return;
    }
    cap[t][s]=cap[s][t]=0;               //去掉边(t,s)和(s,t)
    res=dinic(s,t,num);                  //在对去边及超级汇源之后的图求解最大流
    for(i=1;i<=n;i++)                           //输出方阵
    {
        printf("%d",flow[i][1+n]+low[i][1+n]);
        for(j=2;j<=m;j++)
            printf(" %d",flow[i][j+n]+low[i][j+n]);
//现在求的流量加上下界流量，因为在第一次求最大流时，下界流量丢失，加回来
        printf("\n");
    }
}
int main()
{//这道题可以转化成容量有下界的最大流问题,将方阵的行从1……n编号,列n+1……n+m编号,添加源点s=0和汇点t=n+m+1.
//这样如果存在最大流，一定是唯一的行和或列和，即符合条件限制。
//那么某行某列的两结点间的边的容量就是该行该列元素上下界容量（即元素的限制）之差。
    int i,j,s,t,u,v,w,m,n,num,ans,ncase;
    char ch;
    scanf("%d",&ncase);
    while(ncase--)
    {
        Init();
        scanf("%d%d",&n,&m);
//将每列看成一个结点，每行看成一个结点，给每行，每列各建立一个节点。
        for(i=1;i<=n;i++)
            scanf("%d",&r[i]);
        for(i=1;i<=m;i++)
            scanf("%d",&c[i]);
//从每个行节点到每个列节点连边，容量为无穷大
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                high[i][j+n]=INF;
        scanf("%d",&ans);
        while(ans--)//建图
        {
            scanf("%d %d %c %d",&u,&v,&ch,&w);
            if(u==0&&v!=0) //行为0，限制列
            {
                if(ch=='=')
                {
                    for(i=1;i<=n;i++)
                        low[i][v+n]=high[i][v+n]=w;
                }
                else if(ch=='<')
                {
                    for(i=1;i<=n;i++)
                        high[i][v+n]=min(high[i][v+n],w-1);
                }
                else if(ch=='>')4>
                {
                    for(i=1;i<=n;i++)
                        low[i][v+n]=max(low[i][v+n],w+1);
                }
            }
            else if(u!=0&&v==0)//列为0，限制行
            {
                if(ch=='=')
                {
                    for(i=1;i<=m;i++)
                        low[u][i+n]=high[u][i+n]=w;
                }
                else if(ch=='<')
                {
                    for(i=1;i<=m;i++)
                        high[u][i+n]=min(high[u][i+n],w-1);
                }
                else if(ch=='>')
                {
                    for(i=1;i<=m;i++)
                        low[u][i+n]=max(low[u][i+n],w+1);
                }
            }
            else if(u==0&&v==0)//行列都为0，限制所有
            {
                for(i=1;i<=n;i++)
                    for(j=1;j<=m;j++)
                    {
                        if(ch=='=')
                            low[i][j+n]=high[i][j+n]=w;
                        else if(ch=='<')
                            high[i][j+n]=min(high[i][j+n],w-1);
                        else if(ch=='>')
                            low[i][j+n]=max(low[i][j+n],w+1);
                    }
            }
            else if(u!=0&&v!=0)//行列都不为0，限制某点
            {
                if(ch=='=')//如果u行v列的数字必须等于w,则边<u,v+n>流量的下界和容量都是w
                    low[u][v+n]=high[u][v+n]=w;
                else if(ch=='<')//如果u行v列的数字必须小于w,则边<u,v+n>容量改为w-1
                    high[u][v+n]=min(high[u][v+n],w-1);
                else if(ch=='>')//如果u行v列的数字必须大于w,则边<u,v+n>流量的下界是w+1
                    low[u][v+n]=max(low[u][v+n],w+1);
            }
        }
        s=0;     //源点
        t=n+m+1; //汇点
        for(i=1;i<=n;i++) //将源点和每一个行节点相连,相连所形成的边的容量和下界置为该行所有数字的和
            low[s][i]=high[s][i]=r[i];
        for(i=1;i<=m;i++)
            low[i+n][t]=high[i+n][t]=c[i];//将每一个列节点和汇点相连,相连所形成的边的容量和下界都置为该列所有数字的和
        solve(s,t,t+1,n,m);
        printf("\n");
    }
    return 0;
}
