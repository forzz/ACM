#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
#define MAXN 75
char s[10], chan[100];
double f1[MAXN][MAXN];//f1[i][j]表示现在是闲家叫牌，闲家点数i、庄家点数j，闲家赢的概率
double f2[MAXN][MAXN];//f2[i][j]表示现在轮到庄家叫牌，闲家点数i、庄家点数j，庄家赢的概率
void cal_f2()           //庄家（更简单）
{
	int i, j, k;
	for (i = 21; i >= 2; i--)
	{
		for (j = 21; j >= 2; j--)//暴力枚举每种情况（每人2张牌，从2开始）
		{
			if (i <= j)     //稳赢（边界条件）
			{
				f2[i][j] = 1;
				continue;
			}
			for (k = 1; k <= 13; k++)   //13种牌枚举
			{
				int t = k;
				if (k >= 10)
					t = 10;
				f2[i][j] += (f2[i][j + t] / (double)13);    //从点数大往点数小dp 边界条件在点数大的那一侧
			}
		}
	}
}

void cal_f1()
{
	int i, j, k;
	for (i = 21; i >= 2; i--)
	{
		for (j = 21; j >= 2; j--)
		{
			for (k = 1; k <= 13; k++)   //13种牌枚举
			{
				int t = k;
				if (k >= 10)
					t = 10;
				f1[i][j] += (f1[i + t][j] / (double)13);//更新状态
			}
			f1[i][j] = max(f1[i][j], 1 - f2[i][j]);//两者取最大
		}
	}
}

void init()
{
	int i;

	chan['A'] = 1;
	chan['J'] = 10;
	chan['Q'] = 10;
	chan['K'] = 10;
	chan['T'] = 10;
	for (i = '1'; i <= '9'; i++)
	{
		chan[i] = i - '0';
	}
	cal_f2();
	cal_f1();   //需要用到庄家的dp结果
}

int main()
{//闲家一直操作到停牌，轮到庄家操作，也是一直叫牌到停牌，然后比大小。
	//freopen("i.txt", "r", stdin);
	//freopen("o.txt", "w", stdout);
	init();
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%s", s);
		int t1 = chan[s[0]] + chan[s[1]];   //t1为闲家初始点数
		int t2 = chan[s[2]] + chan[s[3]];   //t2为庄家初始点数
		if (f1[t1][t2] > 0.5)
			puts("YES");
		else
			puts("NO");
	}
	//system("pause");
	return 0;
}
