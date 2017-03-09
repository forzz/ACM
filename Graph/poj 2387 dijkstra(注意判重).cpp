#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N=1005;
const int M=2005;
const int inf=(1<<29);
int n,m;
int d[N];
struct
{
	int v,w,next;
}edge[2*M];
int edgehead[N];
//head[i]保存的是以i为起点的所有边中编号最大的那个,而把这个当作顶点i的第一条起始边的位置.
int k;
bool vis[N];
void addedge(int u,int v,int w)
{
	edge[k].next=edgehead[u];//表示与第k条边同起点的上一条边的存储位置（头插法）
	edge[k].w=w;            //边权值
	edge[k].v=v;         //表示第k条边的终点
	edgehead[u]=k++;
}
//链式前向星也是一种通过存储边的信息的方式存储图的数据结构，可以静态建立邻接表。它将边存放在数组中，
//把数组中的边按照起点顺序排序，前向星就构造完成了。为了查询方便，经常会有一个数组存储起点为Vi的第一条边的位置。
struct cmp
{
	bool operator ()(const int a,const int b)
	{
		return d[a]>d[b];
	}
};
int dijstra(int s)
{
	priority_queue<int,vector<int>,cmp> que;
	for(int i=1;i<=n;i++)//预处理每个点到源点的距离
		d[i]=inf;
	d[s]=0;
	memset(vis,0,sizeof(vis));
	que.push(1);
	while(!que.empty())
	{
		int u=que.top();
		que.pop();
		if(vis[u])//排除已加入到最短路的顶点
			continue;
		vis[u]=true;
		for(int i=edgehead[u];i;i=edge[i].next)//枚举所有邻接边
		{
			int v=edge[i].v;
			int w=edge[i].w;
			if(!vis[v]&&d[v]>d[u]+w)
			{
				d[v]=d[u]+w;
				que.push(v);
			}
		}
	}
	return d[n];
}
int main()
{
	scanf("%d%d",&m,&n);
	int u,v,w;
	k=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		addedge(u,v,w);
		addedge(v,u,w);
	}
	printf("%d\n",dijstra(1));
	return 0;
}
