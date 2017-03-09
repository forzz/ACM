#include <iostream>
#include <cstdio>
#include <cstring>
#include<algorithm>
using namespace std;
const int maxn=88888;
const int maxm=4004000;
int tree[maxm];
int hs[maxm],hn;
int n,m;
int w;
int p[maxn],x[maxn],y[maxn],d[maxn];
inline int lowbit(int x) { return x&(-x); }
void ready(int x,int y)//hs数组保存x，y进入网格后需要改变的所有位置的序号
{
	for(int i=x;i<=w;i+=lowbit(i))
	{
		for(int j=y;j<=w;j+=lowbit(j))
		{
			hs[hn++]=i*w+j;
		}
	}
}

void Add(int x,int y,int v)
{
	for(int i=x;i<=w;i+=lowbit(i))
	{
		for(int j=y;j<=w;j+=lowbit(j))
		{
			int id=lower_bound(hs,hs+hn,i*w+j)-hs;//找到第一个需要增加v的位置
			tree[id]+=v;
		}
	}
}

int Sum(int x,int y)
{
	x=max(x,0); x=min(x,w);
	y=max(y,0); y=min(y,w);

	int ret=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		for(int j=y;j>0;j-=lowbit(j))
		{
			int id=lower_bound(hs,hs+hn,i*w+j)-hs;
			if(hs[id]==i*w+j) ret+=tree[id];
		}
	}
	return ret;
}

int main()
{
	while(scanf("%d",&n)!=EOF&&n)
	{
		scanf("%d",&m);
		w=2*n; hn=0;//为了旋转坐标，网格扩大为2N*2N
		memset(tree,0,sizeof(tree));
		for(int i=0;i<m;i++)//先全部读入预处理
		{
			scanf("%d%d%d%d",p+i,x+i,y+i,d+i);
			if(p[i]==1)   //将坐标旋转45度就可以得到正方形
			{
				int nx=x[i]+y[i];
				int ny=y[i]-x[i]+n;
				ready(nx,ny);
			}
		}
		sort(hs,hs+hn);
		hn=unique(hs,hs+hn)-hs;  //离散化清除多余d，维护hn为hs数组尾节点,然后进入树状数组求sum
		for(int i=0;i<m;i++)
		{
			int nx=x[i]+y[i];
			int ny=y[i]-x[i]+n;
			if(p[i]==1)
			{
				Add(nx,ny,d[i]);
			}
			else if(p[i]==2)//此时d为维度，对
			{
				int x1,y1,x2,y2,x3,y3,x4,y4;
				x1=nx+d[i]; y1=ny+d[i];//右下
				x2=nx-d[i]; y2=ny+d[i]; x2--;//右上
				x3=nx+d[i]; y3=ny-d[i]; y3--;//左下
				x4=nx-d[i]; y4=ny-d[i]; x4--; y4--;//左上
/*
1 x x 1 x
x * * * x
x * # * x
1 * * 1 x
x x x x x
*/
				printf("%d\n",Sum(x1,y1)-Sum(x2,y2)-Sum(x3,y3)+Sum(x4,y4));
			}
		}
	}
    return 0;
}
