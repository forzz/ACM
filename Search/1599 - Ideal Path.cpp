#include<queue>
#include<cstdio>
#include<cstring>
#include<utility> //pair头文件
using namespace std;
#define MAXN 100000
struct node
{
	int v, c;//v代表边edge[u]的另一端，c代表该边的颜色
	node *next;
}edge[MAXN * 4 + 10];   //edge按顺序保存每一条边的信息
node *adj[MAXN + 10];   //保存邻接点信息
node *ecnt; //ecnt是当前边列表的末尾
inline void addedge(const int &u, const int &v, const int &c)
{ //尾插法
	node *p = ++ecnt;   //p保存的是edge末尾的地址
	p->v = v;
	p->c = c;  //数据保存到edge中
	p->next = adj[u];//adj[u]是所有以u为起点的边的链表，头插法插入p，可以少记录adj的尾节点
	adj[u] = p;
}
int d[MAXN + 10], path[MAXN + 10]; //d保存节点到终点的距离    path保存最小颜色字典序
bool vis[MAXN + 10];  //标记是否访问
queue<int>q;
int n, m;
void bfs1(int s)   //
{
	memset(d, 0xff, sizeof(d));
	d[s] = 0 ;//终点长度为1
	q.push(s);
	while (!q.empty())
	{
		int u = q.front();//刚开始时u是终点n
		q.pop();
		for (node *p = adj[u]; p; p = p->next)//扫描终点n连接的所有边
		{
			int v = p->v;
			if (d[v]==-1) //之前没有访问过v，如果之前访问过，那么之前那次得到的d小于等于这次的d（队列）
			{
				d[v] = d[u] + 1; //距离加1
				q.push(v); //放入队列
			}
		}
	}
}
queue<pair<int, int> >q2;
void bfs2(int s)
{
	memset(path, 0x3f, sizeof(path));
	memset(vis, 0, sizeof(vis));
	q2.push(make_pair(s, 0));
	path[0] = 0;
	while (!q2.empty())
	{
		int u = q2.front().first;
		int cy = q2.front().second;//颜色
		q2.pop();
		if (path[d[1] - d[u]] != cy || vis[u]) continue;
		vis[u] = true;//访问过结点u
		for (node *p = adj[u]; p; p = p->next)//扫描所有从u出发的边,找颜色值最小的边
		{
			int v = p->v;
			int c = p->c;
			if (d[u] != d[v] + 1 || path[d[1] - d[v]] <= c) continue;//如果从u到v的距离不是恰好减少1 或者 虽满足条件1但颜色值大于目前的最小值，忽略
			path[d[1] - d[v]] = c;//标记结点1到v的颜色最小值
		}
		for (node *p = adj[u]; p; p = p->next)//将上一次扫描得到的边压入队列
		{
			int v = p->v;
			int c = p->c;
			if (d[u] != d[v] + 1 || path[d[1] - d[v]] != c) continue;//如果满足u到v距离恰好减少1且颜色值最小
			q2.push(make_pair(v, c));//将满足条件的路径入列
		}
	}
	int i;
	printf("%d\n", d[1]);  //d[1]保存了最少经过了几条边
	for (i = 1; i<=d[1]; i++)
		printf("%d%c", path[i],i==d[1]?'\n':' ');
}

int main()
{
	int u, v, w, i;
	while (scanf("%d%d", &n, &m) == 2)
	{
		memset(adj, 0, sizeof(adj));  //把所有相邻边信息清除
		ecnt = edge;
		for (i = 1; i <= m; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);//u为起点
			addedge(v, u, w);//v为起点
		}   //无向图
		bfs1(n);//从终点n开始逆向bfs，统计所有点到终点的最短距离
		bfs2(1);//从起点开始正向bfs，找颜色序列字典序最小的路径
	}
	return 0;
}
/*
0x7FFFFFFF 二进制表示就是除了首位是 0，其余都是1就是说，这是最大的整型数 int（因为第一位是0表示他是正数）
除了要满足加上一个常数依然是无穷大之外，我们的常量还应该满足“无穷大加无穷大依然是无穷大”，
至少两个无穷大相加不应该出现灾难性的错误，这一点上0x7fffffff依然不能满足我们。
最精巧的无穷大常量取值是0x3f3f3f3f，0x3f3f3f3f的十进制是1061109567，也就是10^9级别的（和0x7fffffff一个数量级），
而一般场合下的数据都是小于10^9的，所以它可以作为无穷大使用而不致出现数据大于无穷大的情形。
所以当我们把无穷大加上一个数据时，它并不会溢出（这就满足了“无穷大加一个有穷的数依然是无穷大”），
事实上0x3f3f3f3f+0x3f3f3f3f=2122219134，这非常大但却没有超过32-bit int的表示范围，
memset是按字节操作的，它能够对数组清零是因为0的每个字节都是0，
0x3f3f3f3f的每个字节都是0x3f！所以要把一段内存全部置为无穷大，我们只需要memset(a,0x3f,sizeof(a))。



当初始化一个字节单位的数组时，可以用memset把每个数组单元初始化成任何你想要的值。
在初始化int类型时，则需要注意：
1.   将内存初始化为0
memset(ptr,0,sizeof(ptr));
2.  将内存初始化为-1
memset(ptr,0xff,sizeof(ptr));  （-1相同，二进制同一个数）
　　因为按照字节进行填充，那么value值为0xff，将会把内存的每个字节都填充为0xff，则int值的区域为全1，那么int值就是-1。
3.  将内存初始化为极大值
memset(ptr,0x3f,sizeof(ptr));
　　这段初始化代码初始出来的int值大小是1061109567
如果要将int内存区域统一初始化为1，那memset就无能为力了。
*/
