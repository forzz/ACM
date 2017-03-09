#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f
#define MAX_V 200 + 30 + 16
using namespace std;
struct edge// 用于表示边的结构体（终点、容量、反向边）
{
	int to, rev;
	int cap;
	edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev)
	{}
};
vector <edge> G[MAX_V];   // 图的邻接表表示
int level[MAX_V];      // 顶点到源点的距离标号
int iter[MAX_V];       // 当前弧，在其之前的边已经没有用了
// 向图中加入一条从from到to的容量为cap的边
void add_edge(int from, int to, int cap)
{
	G[from].push_back(edge(to, cap, G[to].size()));
	G[to].push_back(edge(from, 0, G[from].size() - 1));
}
void bfs(int s)// 通过BFS计算从源点出发的距离标号
{
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty())
	{
		int v = que.front();
		que.pop();
		for (int i = 0; i < G[v].size(); ++i)
		{
			edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0)
			{
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}
int dfs(int v, int t, int f)// 通过DFS寻找增广路
{
	if (v == t)return f;
	for (int &i = iter[v]; i < G[v].size(); ++i)
	{
		edge &e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to])
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}

	return 0;
}
int max_flow(int s, int t)// 求解从s到t的最大流
{
	int flow = 0;
	while(1)
	{
		bfs(s);
		if (level[t] < 0)
		{
			return flow;
		}
		memset(iter, 0, sizeof(iter));
		int f;
		while ((f = dfs(s, t, INF)) > 0)
		{
			flow += f;
		}
	}
}
int K, C, M, V;
int graph[MAX_V][MAX_V];
bool check(int limit)
{
//每个奶牛最终都只能到达一个挤奶器，每个挤奶器只能有M个奶牛，可把奶牛看做网络流中的流。
//每个奶牛和挤奶器都是一个节点，添加一个源，连边到所有奶牛节点，这些边容量都是1。
//添加一个汇点，每个挤奶器都连边到它。这些边的容量都是M。
	int s = V, t = V + 1;//虚拟源点和虚拟汇点
	for (int i = 0; i < V + 2; i++)
	{
		G[i].clear();
	}
	for (int i = 0; i < K; i++)
	{
		add_edge(i, t, M);
	}
	for (int i = K; i < V; i++)
	{
		add_edge(s, i, 1);
	}
//先假定一个最大距离的的最小值 maxdist, 在上述图中，如果奶牛节点i和挤奶器节点j之间的距离<=
//maxdist,则从i节点连一条边到j节点，表示奶牛i可以到挤奶器j去挤奶。该边容量为1。该图上的最大流如
//果是C(奶牛数），那么就说明假设的 maxdist成立，则减小 maxdist再试总之，要二分 maxdist, 对每
//个maxdist值，都重新构图，看其最大流是否是C，然后再决定减少或增加maxdist
	for (int i = 0; i < K; i++)
	{
		for (int j = K; j < V; j++)
		{
			if (graph[i][j] <= limit)
			{
				add_edge(j, i, 1);
			}
		}
	}
	return max_flow(s, t) == C;
}
int solve()
{	// 图预处理，warshall_floyd最小化两点距离
	for (int k = 0; k < V; ++k)
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
			{
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
// 二分搜索
	int lb = 0, ub = 200 * V;
	while (ub - lb > 1)
	{
		int mid = (ub + lb) >> 1;
		(check(mid) ? ub : lb) = mid;
	}
	return ub;
}
int main()
{
	scanf("%d%d%d", &K, &C, &M);
	V = K + C;
	for (int i = 0; i < K + C; ++i)
	{
		for (int j = 0; j < K + C; ++j)
		{
			int d;
			scanf("%d", &d);
			graph[i][j] = d ? d : INF;
		}
	}
	printf("%d\n", solve());
	return 0;
}
