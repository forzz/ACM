#include<stdio.h>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 100005;
vector<int> t, tree[maxn];
int tot, T, N, Q, x, y, m[maxn][2], M[maxn][2], dfn[maxn][2], fa[maxn];

void begin()
{
	tot = 0;
	for (int i = 1; i <= N; i++)
	{
		tree[i].clear();
		fa[i] = 0;
		m[i][0] = m[i][1] = 0x7FFFFFFF;
		M[i][0] = M[i][1] = 0x7FFFFFFF;
		dfn[i][0] = dfn[i][1] = 0;
	}
}

void dfs(int x, int xx)
{
	fa[x] = xx;	dfn[x][0] = ++tot;	t.clear();
	for (int i = 0; i < tree[x].size(); i++)
		if (tree[x][i] != xx) t.push_back(tree[x][i]);
	tree[x] = t;
	for (int i = 0; i < tree[x].size(); i++)
	{
		int y = tree[x][i];
		dfs(y, x);
		if (y < m[x][0]) m[x][1] = m[x][0], m[x][0] = y;
		else m[x][1] = min(m[x][1], y);
		y = min(y, M[y][0]);
		if (y < M[x][0]) M[x][1] = M[x][0], M[x][0] = y;
		else M[x][1] = min(M[x][1], y);
	}
	dfn[x][1] = ++tot;
}

int half(int x, int y)
{
	int q = 0, h = tree[y].size() - 1, mid;
	while (true)
	{
		mid = (q + h) >> 1;
		if (dfn[x][0] >= dfn[tree[y][mid]][0] && dfn[x][1] <= dfn[tree[y][mid]][1]) return tree[y][mid];
		if (dfn[x][0] < dfn[tree[y][mid]][0]) h = mid - 1; else  q = mid + 1;
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &Q);
		begin();
		for (int i = 1; i < N; i++)
		{
			scanf("%d%d", &x, &y);
			tree[x].push_back(y);
			tree[y].push_back(x);
		}
		dfs(1, 1);
		while (Q--)
		{
			scanf("%d%d", &x, &y);
			if (dfn[x][0]>dfn[y][0] && dfn[x][1] < dfn[y][1])
			{
				int z = half(x, y);
				if (y != 1)
				{
					if (z == m[y][0]) printf("%d 1\n", min(m[y][1], fa[y]));
					else printf("%d 1\n", min(m[y][0], fa[y]));
				}
				else
				{
					if (tree[y].size() == 1) printf("no answers!\n");
					else
					{
						if (z == m[y][0]) printf("%d ", m[y][1]);
						else printf("%d ", m[y][0]);
						if (min(z, M[z][0]) == M[y][0]) printf("%d\n", M[y][1]);
						else printf("%d\n", M[y][0]);
					}
				}
			}
			else 
			if (dfn[y][0] + 1 == dfn[y][1]) printf("no answers!\n");
			else printf("%d %d\n", m[y][0], M[y][0]);
		}
		printf("\n");
	}
}
