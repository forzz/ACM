#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=110;
const int MAXE=210;//两倍
double dist[MAXN];
int tol;//边的总数
int D[MAXE][2];//存边的起点和终点
double C[MAXE][2];//存汇率和手续费
bool Bellman(int start,int n,double V)
{
    for(int i=1;i<=n;i++) dist[i]=0;////这里与bellman的目的刚好相反。初始化为源点到各点距离无穷小
    dist[start]=V;//即bellman本用于找负环，求最小路径，本题是利用同样的思想找正环，求最大路径
    for(int i=1;i<n;i++)//做n-1次（n-1个点）
//Bellman-Ford算法不一定要循环n-1次， n为顶点个数只要在某次循环过程中，考虑每条边后，
//源点到所有顶点的最短路径长度都没有变，那么Bellman-Ford算法就可以提前结束了
    {
        bool flag=false;//优化
        for(int j=0;j<tol;j++)//枚举每条边
        {
            int u=D[j][0];
            int v=D[j][1];
            if(dist[v] < (dist[u]-C[j][1])*C[j][0])//进行比较的是"某点到自身的权值"和"某点到另一点的权值"
            {
                flag=true;//存在可用边，不能提前结束
                dist[v]=(dist[u]-C[j][1])*C[j][0];
            }
        }
        if(!flag)return false;//没有更新，循环提前结束，也表示不存在正环
    }
//做了n-1次的全部边松弛操作之后，就确定了所有点的最短路径值。
//如果做第n次全部边松弛操作的时候，还有点的最短值会被更新，则说明图里是存在正环的。
    for(int j=0;j<tol;j++)
      if(dist[D[j][1]]<(dist[D[j][0]]-C[j][1])*C[j][0])//正环能够无限松弛
        return true;//有正环
    return false;
}
int main()
{
    int n;
    int M;
    int a,b;
    double c,d,e,f;
    int S;
    double V;
    while(scanf("%d%d%d%lf",&n,&M,&S,&V)!=EOF)//存储数据
    {
        tol=0;
        while(M--)
        {
            scanf("%d%d%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
            D[tol][0]=a;
            D[tol][1]=b;
            C[tol][0]=c;
            C[tol][1]=d;
            tol++;
            D[tol][0]=b;
            D[tol][1]=a;
            C[tol][0]=e;
            C[tol][1]=f;
            tol++;
        }
        if(Bellman(S,n,V)) printf("YES\n");//S为源点的钱，n为源点钱的数目
        else printf("NO\n");
    }
    return 0;
}
