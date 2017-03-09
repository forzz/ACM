#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=500+10;
const int maxm=500*500+10;
struct Point
{
    double x,y;
}points[maxn];
struct Edge
{
    int u,v;
    double dist;//距离
    Edge(){}
    Edge(int u,int v,double d):u(u),v(v),dist(d){}
    bool operator<(const Edge&rhs)const
    {
        return dist <rhs.dist;
    }
}edges[maxm];

int n;
int fa[maxn];//并查集相关
int findset(int x){ return fa[x]==-1? x: fa[x]=findset(fa[x]); }
double get_dist(int i,int j)//勾股定理求两点之间的直线距离
{
    double x1=points[i].x, y1=points[i].y, x2=points[j].x, y2=points[j].y;
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main()
{
    int T,S; scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&S,&n);
        memset(fa,-1,sizeof(fa));
        for(int i=0;i<n;i++)//记录每个村庄的坐标
            scanf("%lf%lf",&points[i].x,&points[i].y);
        int cnt=0;//边总数
        for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
        {
            edges[cnt++]=Edge(i,j,get_dist(i,j));//预处理求得所有的边
        }
        sort(edges,edges+cnt);//按kruskal算法对边排序

        //添加n-S条有效边后,整个图还剩S个连通分量
        int num=0;  //当前添加的最小生成树边 数目
        double D;
        for(int i=0;i<cnt;i++)
        {
            int u=edges[i].u , v=edges[i].v;
            if(findset(u) != findset(v))//两点没在同一连通分量中
            {
                fa[findset(u)] = findset(v);
                if(++num == n-S) { D=edges[i].dist; break;}
//最小生成树中的最长k-1条长边都去掉后，正好将原树分成了k 个连通分支，在每个连通分支上摆一个卫星设备即可
//一个图的两棵最小生成树，边的权值序列排序后结果相同
            }
        }
        printf("%.2lf\n",D);
    }
    return 0;
}
