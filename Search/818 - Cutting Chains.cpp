#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
#define INF 0x3f3f3f3f
const int N = 20;
int n, g[N][N], vis[N], cn;
void init() {
	int a, b;
	memset(g, 0, sizeof(g));
	while (~scanf("%d%d", &a, &b) && a != -1 && b != -1) {
		g[a - 1][b - 1] = g[b - 1][a - 1] = 1; //连通块
	}
}
bool two(int s) {//判断剩下的圆环是否存在分支超过两个的
	for (int i = 0; i < n; i++) {//遍历每一个环
		if (s&(1<<i)) continue;//环被拆
		int num = 0;
		for (int j = 0; j < n; j++) {//遍历所有环
			if (s&(1<<j)) continue; //环被拆
			if (g[i][j]) num++;
		}
		if (num > 2) return true;
	}
	return false;
}
bool dfs(int s, int now, int fa) {//利用dfs判断剩下的圆环是否构成了环，同时在找now所在的连通分量
	vis[now] = 1;
	for (int i = 0; i < n; i++) {//遍历每个环
		if (!g[now][i] || (s&(1<<i)) || i == fa) continue;
	//没连通或者已拆或者为上一个节点（上一个节点直接跳过）
		if (vis[i]) return true;//构成环
		if (dfs(s, i, now)) return true;
	}
	return false;
}
bool circle(int s) {//判断剩下的圆环是否连成环
	for (int i = 0; i < n; i++) {//每个环
		if (vis[i] || (s&(1<<i))) continue;//已经访问过的结点和已经打开的结点跳过
		cn++;
		if (dfs(s, i, -1)) return true;
	}
	return false;
}
int cal(int s) {    //计算去掉的圆环个数
	return s == 0 ? 0 : cal(s / 2) + (s&1);
	//取出s的每一位
}
int solve() {
	int ans = INF;//初始化为最大值
	int s = (1<<n);//n个环
	for (int i = 0; i < s; i++) {//二进制保存打开的环，i++就可以取遍所有状态
		cn = 0; memset(vis, 0, sizeof(vis));//每一次都要初始化
		if(two(i) || circle(i)) continue;//如果剩下的圆环有大于两个分支的或形成环的，不合题意，忽略
		if (cal(i) >= cn - 1)        //去掉的圆环个数是否大于等于连通分量的个数-1
			ans = min(cal(i), ans);
	}
	return ans;
}
int main() {
	int cas = 0;
	while (~scanf("%d", &n) && n) {//n个圆环
		init();
		printf("Set %d: Minimum links to open is %d\n", ++cas, solve());
	}
	return 0;
}
