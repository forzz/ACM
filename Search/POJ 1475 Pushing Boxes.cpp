#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int MAXN = 50;
struct status{//箱节点
	int person_x,person_y;
	int box_x,box_y;
	string ans;
}p,q;
struct node{  //人结点
	int x,y;
	string ans;
}P,Q;
int dx[]={1, -1, 0, 0};
int dy[]={0, 0, 1, -1};
char Pm[]={'s', 'n', 'e', 'w'};
char Pb[]={'S', 'N', 'E', 'W'};
int visP[MAXN][MAXN],visB[MAXN][MAXN];
char G[MAXN][MAXN];
int sx,sy,ex,ey,bx,by;
int r,c;

int check(int x, int y){//判断是否在界内
	if (x >= 0 && x< r && y >= 0 && y < c)
		return true;
	return false;
}

int bfs2(int start_x, int start_y, int end_x, int end_y){//人bfs到xy的最短路
	memset(visP, 0, sizeof(visP));
	P.x = start_x;
	P.y = start_y;
	P.ans = "";
	visP[P.x][P.y] = 1; //起点
	visP[p.box_x][p.box_y] = 1;  //当前箱点不能去
	queue<node> qq;
	qq.push(P);
	while (!qq.empty()){
		P = qq.front();
		qq.pop();
		if (P.x == end_x && P.y == end_y)  //到达目的地
			return true;
		for (int i = 0; i < 4; i++){
			int nx = P.x + dx[i];
			int ny = P.y + dy[i];
			if (check(nx, ny) && G[nx][ny] != '#' && !visP[nx][ny]){
				visP[nx][ny] = 1;//标记当前人的位置
				Q.ans = P.ans + Pm[i];  //记录当前方向
				Q.x = nx;  //维护位置
				Q.y = ny;
				qq.push(Q);
			}
		}
	}
	return false;
}

int bfs(){ //箱bfs
	memset(visB, 0, sizeof(visB));
	p.person_x = sx;
	p.person_y = sy;
	p.box_x = bx;
	p.box_y = by;
	p.ans = "";
	visB[bx][by] = 1;
	queue<status> st;
	st.push(p);
	while (!st.empty()){
		p = st.front();
		st.pop();
		for (int i = 0; i < 4; i++){
			int nx = p.box_x + dx[i];// 箱子的下一个坐标
			int ny = p.box_y + dy[i];
			int tx = p.box_x - dx[i];// 人的当前坐标（下一个人的坐标就是当前箱子的坐标，不需要考虑）
			int ty = p.box_y - dy[i];
			if (check(tx, ty) && G[tx][ty] != '#' && check(nx, ny) &&G[nx][ny] != '#' && !visB[nx][ny]){
				if (bfs2(p.person_x, p.person_y, tx, ty)){ //当前人的位置可以bfs到
					visB[nx][ny] = 1;//标记箱子的位置，人的位置不用标记
					q.person_x = p.box_x;   //维护当前人的坐标
					q.person_y = p.box_y;
					q.box_x = nx;  //维护当前箱的坐标
					q.box_y = ny;
					q.ans = p.ans+P.ans+Pb[i];  //维护路径
					if (nx == ex && ny == ey)
						return true;
					st.push(q);
				}
			}
		}
	}
	return false;
}

int main(){//bfs本来就包含最短路
	int cas = 1;
	while (scanf("%d%d", &r, &c) != EOF && r+c){
		for (int i = 0; i < r; i++){
			scanf("%s", G[i]);
			for (int j = 0; j < c; j++){
				if (G[i][j] == 'S'){
					sx = i;
					sy = j;
				}
				if (G[i][j] == 'T'){
					ex = i;
					ey = j;
				}
				if (G[i][j] == 'B'){
					bx = i;
					by = j;
				}
			}
		}
		printf("Maze #%d\n", cas++);
		if (bfs())
			printf("%s\n", q.ans.c_str());
		else printf("Impossible.\n");
		printf("\n");
	}
	return 0;
}
