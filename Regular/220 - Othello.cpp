#include <cstdio>
#include <queue>
using namespace std;
struct P{
	int x, y;
	P(){};   //默认构造函数
	P(int x, int y) :x(x), y(y){}  //构造函数
};
char board[10][10];
bool currplay;//true黑方下，fasle白方下
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
bool find(int r, int c, bool re)//re为true时吃子，遍历访问每一个能下的位置A
{
	if (board[r][c] != '-') return false;//如果该位置有棋子，直接返回0

	for (int k = 0; k < 8; k++){
		int nx = r + dx[k];  //nx与ny表示这个位置周围的所有可能
		int ny = c + dy[k];
		if (board[nx][ny] == (currplay ? 'W' : 'B')){    //如果A在该方向存在另一方的棋子
			queue<P> q;//此时可能把这个棋子吃掉，此时设队列
			for (; 1 <= nx && nx <= 8 && 1 <= ny && ny <= 8; nx += dx[k], ny += dy[k]){//查找当前方向的下一个位置
				if (board[nx][ny] == '-') break;//黑白棋周围没有棋子不能下
				if (board[nx][ny] == (currplay ? 'W' : 'B')){//如果找到了这个方向的对方的棋
					if (re) q.push(P(nx, ny));//如果是下棋，可能吃掉这个棋，先放入队列
				}
				else if (board[nx][ny] == (currplay ? 'B' : 'W')){//如果找到该方向的己方的棋
					if (re){//如果是下棋
						while (!q.empty()){
							P p = q.front();  //p是队列中的第一个（结构体）
							board[p.x][p.y] = (currplay ? 'B' : 'W');//p代表的位置变成己方的棋子
							q.pop();
						}
					}
					else//不是下棋，返回1，代表这是可以下棋的地方
						return true;
					break;
				}
			}
		}
	}
	return false;
}

bool list()
{
	int num = 0;
	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)//全部遍历，查找每一个位置是否可以下棋
			if (find(i,j,false))//不吃子，因为吃子是之前就已经判断出来了
				printf("%s(%d,%d)", num++ ? " " : "", i, j);//num是格式需要
	if (num) {//如果是第二个以上，需要加换行符
		printf("\n"); return true;
	}
	return false;
}

void move(int r, int c)
{
	if (!find(r, c, false))//如果无法下棋，那么换色
		currplay = !currplay;
	find(r, c, true);

	board[r][c] = currplay ? 'B' : 'W';
	int bnum = 0, wnum = 0;
	for (int i = 1; i <= 8; i++)//统计总棋数
		for (int j = 1; j <= 8; j++){
			if (board[i][j] == 'B') bnum++;
			else if (board[i][j] == 'W') wnum++;
		}
		currplay = !currplay;//换色
		printf("Black - %2d White - %2d\n", bnum, wnum);
}
int main()
{
	int T;     //ca是次数
	char str[5];
	scanf("%d", &T);
	while (T--)
	{
		getchar();
		for (int i = 1; i <= 8; i++){//从1开始存数据
			for (int j = 1; j <= 8; j++){
				scanf("%c", &board[i][j]);
			}
			getchar();
		}
		scanf("%s", str);
		currplay = (str[0] == 'B');  //执棋方
		while (str[0] != 'Q')
		{
			scanf("%s", str); //读入命令
			if (str[0] == 'L'){
				if (!list())
					printf("No legal move.\n");
			}
			else if (str[0] == 'M'){
				int x = str[1] - '0'; int y = str[2] - '0';
				move(x, y);
			}
			else{
				for (int i = 1; i <= 8; i++){
					for (int j = 1; j <= 8; j++)
						printf("%c", board[i][j]);
					printf("\n");
				}
				if (T) printf("\n");
			}
		}
	}
}