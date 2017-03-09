#include <cstdio>
#include <cstdlib>
#include <cstring>
const int maxn = 30;
int f[maxn], g[maxn][maxn], id[maxn], od[maxn];
int t, n, root;

int Find(int x) {  //并查集判断两个点是否处于一个连通分量中
	if (x != f[x])
		return f[x] = Find(f[x]); //再往上找一次
	return x;
}

int main () {
	scanf("%d", &t);
	while (t--) {
		char word[1001];
		scanf("%d", &n);
		for (int i = 0; i < maxn; i++) { //初始化
			f[i] = i;
			id[i] = 0;   //入度
			od[i] = 0;   //出度
			for (int j = 0; j < maxn; j++)
				g[i][j] = 0;
		}
		for (int i = 0; i < n; i++) {
			scanf("%s", word);
			int a = word[0] - 'a', b = word[strlen(word) - 1] - 'a';
			g[a][b]++;
			od[a]++;
			id[b]++;
			f[Find(a)] = Find(b);  //归到同一并查集中：a的根节点的父节点为b的根节点
			root = Find(b);
		}
		int i, ans = 0, flag = 1, in = 0, on = 0;
		for (i = 0; i < maxn; i++)
		if (id[i] || od[i]) {
			if (Find(f[i]) != root) //不连通
				ans++;
			if (id[i] - od[i] == 1) //某点入度比出度大1
				in++;
			else if (od[i] - id[i] == 1) //某点出度比入度大1
		 		on++;
			else if (abs(id[i] - od[i]) > 1)   //某点度数差大于1
				break;
		}
		if (i < maxn || ans > 0 || in > 1 || on > 1)
			printf("The door cannot be opened.\n");
		else
			printf("Ordering is possible.\n");
	}
	return 0;
}
