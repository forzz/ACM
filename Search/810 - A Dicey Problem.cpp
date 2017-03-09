#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int D[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
const int N = 15;
char str[25];
int n, m, sx, sy, u, f, to[7][7], g[N][N];
int vis[N][N][7][7];
struct State {
	int x, y, u, f;
	int pre;  //记录前一个点的位置
	State() {}
	State(int x, int y, int u, int f, int pre) {//构造函数
		this->x = x;
		this->y = y;
		this->u = u;
		this->f = f;
		this->pre = pre;
	}
} Q[10005];
#define MP(a,b) make_pair(a,b)
typedef pair<int, int> pii;
vector<pii> ans;
void tra(int &vu, int &vf, int d) {
	if (d == 0) {int tmp = vf; vf = 7 - vu; vu = tmp;}  //上滚
	if (d == 1) {int tmp = vu; vu = 7 - vf; vf = tmp;}  //下滚
	if (d == 2) vu = 7 - to[vu][vf];         //左滚
	if (d == 3) vu = to[vu][vf];             //右滚
}//上下滚不需要打表，可以直接判断，左右滚需要依据打表数据
void print(int u) {
	if (u == -1) return;//起点
	print(Q[u].pre);
	ans.push_back(MP(Q[u].x, Q[u].y));
}

void bfs() {
	ans.clear();
	int head = 0, rear = 0;
	Q[rear++] = State(sx, sy, u, f, -1);
	memset(vis, 0, sizeof(vis));
	vis[sx][sy][u][f] = 1;
	while (head < rear) {
		State u = Q[head++];//出队列
		for (int i = 0; i < 4; i++) {//4种方向
			State v = u;
			v.x += D[i][0];
			v.y += D[i][1];
			if (v.x <= 0 || v.x > n || v.y <= 0 || v.y > m) continue;
			if (g[v.x][v.y] != -1 && u.u != g[v.x][v.y]) continue;
	//if(g[v.x][v.y]==-1|| u.u == g[v.x][v.y])  顶面数字与目标格数字相同或目标格为-1时才可以移动。执行下列语句
			if (v.x == sx && v.y == sy) { //到达目的地
				print(head - 1);//放回到队列中
				ans.push_back(MP(sx, sy));//压入终点位置
				int tot = ans.size();
				for (int i = 0; i < tot; i++) {
					if (i % 9 == 0) printf("\n  ");
					printf("(%d,%d)%c", ans[i].first, ans[i].second, i == tot - 1 ? '\n' : ',');
				}
				return;
			}
			tra(v.u, v.f, i);//翻滚
			if (vis[v.x][v.y][v.u][v.f]) continue;//已存在同样状态
			vis[v.x][v.y][v.u][v.f] = 1;  //标记
			v.pre = head - 1;  //记录前一个点的位置
			Q[rear++] = v;
		}
	}
	printf("\n  No Solution Possible\n");
}
int main() {//打表：顶前左（一个正方体知道顶和前，后和底为7-x，左右需要打表）
	to[1][2] = 4; to[1][3] = 2; to[1][4] = 5; to[1][5] = 3;
	to[2][1] = 3; to[2][3] = 6; to[2][4] = 1; to[2][6] = 4;
	to[3][1] = 5; to[3][2] = 1; to[3][5] = 6; to[3][6] = 2;
	to[4][1] = 2; to[4][2] = 6; to[4][5] = 1; to[4][6] = 5;
	to[5][1] = 4; to[5][3] = 1; to[5][4] = 6; to[5][6] = 3;
	to[6][2] = 3; to[6][3] = 5; to[6][4] = 2; to[6][5] = 4;
	while (~scanf("%s", str) && strcmp(str, "END")) {
		printf("%s", str);
		scanf("%d%d%d%d%d%d", &n, &m, &sx, &sy, &u, &f);//行 列 起点x和y 顶 前
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &g[i][j]);//迷宫
		bfs();
	}
	return 0;
}
