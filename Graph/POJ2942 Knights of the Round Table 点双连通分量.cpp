
#include <iostream>
using namespace std;
#define N 1005
#define min(a,b) (a<b?a:b)
int n, m;
int size, id, scc;
int color[N], head[N];
int low[N], dfn[N], block[N];
int stack[N], temp[N], top, cnt; // temp 是一个临时的栈，存储点双连通分支
bool map[N][N], expell[N], instack[N];  // expell[i]==true表示i需要被驱逐
struct { int v, next; } edge[N*1000];
bool odd_cycle ( int u, int clr )
//求奇圈时可以用到这样一个性质，一个图是二分图当且仅当图中不存在奇圈。
//那么我们只需判断一个图是否是二分图就可以判断此图存在奇圈，可以用交替染色。
{//二分图染色后，只要有一个点和它的相邻节点的颜色相同，就找到了奇环。
	color[u] = clr;// 把顶点染成1或-1
	for ( int i = head[u]; i; i = edge[i].next )
	{
		int v = edge[i].v;
		if ( block[v] == scc )
		{
			if ( color[v] && color[v] == color[u] )
				return true;
			if ( !color[v] && odd_cycle (v, -clr) )
				return true;
		}
	}
	return false;
}
void Tarjan ( int u, int father )//father 是u的父节点
{
//对于点双连通分支，实际上在求割点的过程中就能顺便把每个点双连通分支求出。建立一个栈，存储当前双连通分支，在搜索图时
//每找到一条树枝边或反向边(连到树中祖先的边），就把这条边加入栈中。如果遇到某树枝边（ u,v) 满足dfn(u)<=low(v)，说明u是
//一个割点，此时把边从栈顶一个个取出，直到遇到了边(u,v)，取出的这些边与其关联的点，组成一个点双连通分支。割点可以属于
//多个点双连通分支，其余点和每条边只属于且属于一个点双连通分支。
	int v, t;
	stack[++top] = u;
	instack[u] = true;
	dfn[u] = low[u] = ++id;
	for ( int i = head[u]; i; i = edge[i].next )// 遍历入栈节点的边
	{
		v = edge[i].v;
		if ( v == father ) continue;//连到父节点的回边不考虑。
		if ( ! dfn[v] )//v未进栈
		{
			Tarjan ( v, u );
			low[u] = min ( low[u], low[v] );
			if ( low[v] >= dfn[u] )  // u是割点
			{
				scc++;
				do {
					t = stack[top--];
					instack[t] = false;
					block[t] = scc;
					temp[++cnt] = t; //出栈的同时把所有的点记录在temp中，即用temp来储存双连通分支内所有的点
				} while ( t != v ); //注意不要把u出栈，因为一个割点可能属于不同的双联通分支
				temp[++cnt] = u; // 割点u属于不同的双联通分支，所以它必然也属于temp
				memset(color,0,sizeof(color)); // 所有颜色置为0
			    if ( cnt >= 3 && odd_cycle(u,1) )
//当temp中存在奇圈，那么temp中的所有人都可以留下。将这些边所连接的点都标记下，最后输出的是没被标记的点的个数
				{
					while ( cnt != 0 )
						expell[temp[cnt--]] = false;
				}
				else cnt = 0;
			}
		}
		else if ( instack[v] )
// 如果新搜索到的节点已经被搜索过而且现在在栈中(该节点的开始时间肯定比当前点早，而且没更新过low，所以用dfn更新)
			low[u] = min ( low[u], dfn[v] );
	}
}
void initial()   //初始化
{
	top = cnt = 0;
	size = id = scc = 0;
	memset(map,0,sizeof(map));
	for ( int i = 1; i <= n; i++ )
	{
		expell[i] = true;
		instack[i] = false;
		dfn[i] = low[i] = block[i] = head[i] = 0;
	}
}
void add ( int u, int v )//头插法建立邻接表
{
	size++;
	edge[size].v = v;
	edge[size].next = head[u];
	head[u] = size;
}
int main()
{
	int u, v, i, j;
	while ( scanf("%d%d",&n,&m) && (m+n) )
	{
		initial();//初始化
		while ( m-- )//先建立一张图，将憎恨关系标记下来
		{
			scanf("%d%d",&u,&v);
			map[u][v] = map[v][u] = true;
		}
		for ( i = 1; i <= n; i++ )//构建其补图，相连表示这两个骑士没有憎恨关系（可以坐在一起）
			for ( j = i+1; j <= n; j++ )
				if ( ! map[i][j] )
					add(i,j), add(j,i);
//如果有一个环，且其中骑士的个数为奇数个，那么这些骑士一定可以参加一次会议
//将每次参加会议的所有人看做一个点双联通分量，那么每个点都至少有两个点与他相邻，问题就转化为求点-双连通分量。
//接下来需要保证双联通分量中存在奇圈。因为只要点双连通分量中存在奇圈，那么这个分量中所有的点都可以出现在奇圈上。
		for ( i = 1; i <= n; i++ )
			if ( ! dfn[i] ) Tarjan(i,-1);
		int res = 0;
		for ( i = 1; i <= n; i++ )
		    if ( expell[i] ) res++;
		printf("%d\n", res );
	}
	return 0;
}
