#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
const int MAXN = 16;
int nxt[15][6] = {// 左上 右上 左 右 左下 右下
	{-1, -1, -1, -1, 2, 3}, {-1, 1, -1, 3, 4, 5}, {1, -1, 2, -1, 5, 6},
	{-1, 2, -1, 5, 7, 8}, {2, 3, 4, 6, 8, 9}, {3, -1, 5, -1, 9, 10},
	{-1, 4, -1, 8, 11, 12}, {4, 5, 7, 9, 12, 13}, {5, 6, 8, 10, 13, 14},
	{6, -1, 9, -1, 14, 15}, {-1, 7, -1, 12, -1, -1}, {7, 8, 11, 13, -1, -1},
	{8, 9, 12, 14, -1, -1}, {9, 10, 13, 15, -1, -1}, {10, -1, 14, -1, -1, -1}
};
struct Statue {
	int st;
	int num;
	int way[2][MAXN];
	int cnt;
	Statue(int _st = (1<<16) - 1, int _num = 15) {   //构造函数
		st = _st;    // _st为二进制全为11
		num = _num;
		cnt = 0;
	}
};
queue<Statue> q;
set<int> s;  //set判重，状态包含的数据多
int n;
int bfs() {
	s.clear();
	while (!q.empty())//初始化q
		q.pop();
	q.push(Statue(((1<<16)-1)^(1<<(n-1)), 14)); //将初始状态放入
	while (!q.empty()) {
		Statue tmp = q.front();
		q.pop();
		for (int i = 0; i < 15; i++) {
			if ((tmp.st>>i)&1) {//如果未空
				for (int j = 0; j < 6; j++) {
					if (nxt[i][j] != -1 && ((tmp.st>>(nxt[i][j]-1))&1)) {//有通路且不空
						int tt = i;
						Statue cur = tmp;//新状态
						while (tt >= 0 && (cur.st>>tt)&1) {//有该洞且洞不空
							cur.st -= (1<<tt);//该洞变空
							cur.num--;  //总数减少1
							tt = nxt[tt][j] - 1;  //沿该方向再进一位
						}
						cur.num++;
						if (tt < 0)//该方向无空洞，不能移动
							continue;
						cur.st |= (1<<tt);//tt位现在是空洞，i洞的球跳到tt洞
						if (!s.count(cur.st)) {//如果是新状态
							s.insert(cur.st);//读入新状态
							cur.way[0][cur.cnt] = i + 1;   //此次起点
							cur.way[1][cur.cnt] = tt + 1;  //此次终点
							cur.cnt++; //路径数++
							if (cur.num == 1 && (cur.st>>(n-1))&1) {//成功
								printf("%d\n%d %d", cur.cnt, cur.way[0][0], cur.way[1][0]);
								for (int i = 1; i < cur.cnt; i++) {
									printf(" %d %d", cur.way[0][i], cur.way[1][i]);
								}
								puts("");
								return 0;
							}
							q.push(cur);
						}
					}
				}
			}
		}
	}
	printf("IMPOSSIBLE\n");
	return 0;
}


int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		bfs();
	}
	return 0;
}
