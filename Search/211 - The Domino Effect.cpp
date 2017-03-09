#include <stdio.h>
#include <string.h>
const int R = 7;
const int C = 8;
const int N = 30;
const int d[2][2] = {{0, 1}, {1, 0}};
int ans, t[R][C], g[R][C], vis[R][C], rec[N];
bool init() {
	ans = 0;
	memset(rec, 0, sizeof(rec));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) if (scanf("%d", &g[i][j]) != 1) return false;//保证完全读入
	return true;
}
void setInit() {//每个骨牌进行编号
	int c = 1;
	for (int i = 0; i < R; i++)
		for (int j = i; j < R; j++)
			t[i][j] = t[j][i] = c++;
}
void put() { //输出vis数组
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) printf("%4d", vis[i][j]);
		printf("\n");
	}
	printf("\n");
}
void dfs(int x, int y, int c) {
//能保证起点是左上角，固定从左往右dfs，不回头不跳转到下一行，先右后下，可以遍历全部可能
	if (c == 28) {//全部遍历完
		ans++; put();
		return;
	}
	if (vis[x][y]) dfs(x, y + 1, c);//如果已经访问过，跳到下一列
	else {//横竖两种方向
		for (int i = 0; i < 2; i++) {
			int p = x + d[i][0], q = y + d[i][1];
			if (p >= R || q >= C || vis[p][q]) continue;//不越界且未访问
			int k = t[g[x][y]][g[p][q]];//该张牌的编号，
			if (rec[k]) continue;  //rec数组表示k号骨牌是否已匹配过
			vis[x][y] = vis[p][q] = k; rec[k] = 1;  //vis数组直接保存编号 维护rec数组
			dfs(x, y + 1, c + 1);
			vis[x][y] = vis[p][q] = 0; rec[k] = 0; //恢复状态
		}
	}
}

int main() {
	setInit();
	int cas = 0;
	while (init()) {
		if (cas) printf("\n\n\n");//格式
		printf("Layout #%d:\n\n", ++cas);
		for (int i = 0; i < R; i++) {//重新输出一遍
			for (int j = 0; j < C; j++)
				printf("%4d", g[i][j]);
			printf("\n");
		}

		printf("\nMaps resulting from layout #%d are:\n\n", cas);
		dfs(0, 0, 0);
		printf("There are %d solution(s) for layout #%d.\n", ans, cas);
	}
	return 0;
}
