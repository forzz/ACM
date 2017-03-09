#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN=1005;
const int INF=0x3f3f3f3f;
bool vis[MAXN];
double lowc[MAXN];
int pre[MAXN];
double Max[MAXN][MAXN];
bool used[MAXN][MAXN];
double cost [MAXN][MAXN];
struct sa
{
    int x,y,p;
} num[1005];
double Dis(sa a,sa b)//勾股定理求两点距离
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}
double prim(int n)//次小生成树模板（次小生成树可由最小生成树换一条边得到，利用MAX数组）
//不加堆优化的Prim 算法适用于密集图，加堆优化的适用于稀疏图
{
    double ans=0;
    memset(vis,false,sizeof(vis));
    memset(Max,0,sizeof(Max));
    //用一个矩阵max[u][v] 记录 在MST中连结任意两点u,v的唯一的路中权值最大的那条边的权值.
    memset(used,false,sizeof(used));
    vis[0]=true;
    pre[0]=-1;
    for(int i=1; i<n; i++)//预处理，lowc表示每个节点到最小生成树的距离，初始为到节点0的距离
    {
        lowc[i]=cost[0][i];
        pre[i]=0;//顶点i到MST的前驱节点（到树最近的邻接点）
    }
    lowc[0]=0;
    for(int i=1; i<n; i++)//头节点
    {
        double minc=INF*1.0;//这里一定要乘以1.0
        int p=-1;//p记录当前最小的边
        for(int j=0; j<n; j++)//尾节点
            if(!vis[j]&&minc>lowc[j])//查找最小权值
            {
                minc=lowc[j];
                p=j;
            }
        ans+=minc;//维护总权值
        vis[p]=true;//把p加入MST中
        used[p][pre[p]]=used[pre[p]][p]=true;
        for(int j=0; j<n; j++)//遍历p的所有邻接点j
        {
            if(vis[j]&&j!=p)//这里一定要有j！=p （因为p到p是0会构成环）维护MAX数组
                Max[j][p]=Max[p][j]=max(Max[j][pre[p]],lowc[p]);
            if(!vis[j]&&lowc[j]>cost[p][j])//更新邻接点到MST的距离和最近邻接点
            {
                lowc[j]=cost[p][j];
                pre[j]=p;
            }
        }
    }
    return ans;
}
int main()
{
    int n,t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=0; i<n; i++)
        {
            cin>>num[i].x>>num[i].y>>num[i].p;
        }
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                cost[i][j]=cost[j][i]=Dis(num[i],num[j]);//因为给的是点的坐标，所以要在这里处理一下
            }
        }
        double dis=prim(n);
        double sum=-1;
        for(int i=0; i<n; i++)//枚举所有边
            for(int j=i+1; j<n; j++)
            {
                if(used[i][j])//该边就在最小生成树里，则直接减掉
                    sum=max(sum,1.0*(num[i].p+num[j].p)/(dis-cost[i][j]));
                else//该边在最小生成树外，那么减掉的是由该边和最小生成树对应的边构成的环里面除了这条边以外的最大的边
                    sum=max(sum,1.0*(num[i].p+num[j].p)/(dis-Max[i][j]));
            }
        printf("%.2f\n",sum);
    }
    return 0;
}
