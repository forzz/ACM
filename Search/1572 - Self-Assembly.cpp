#include<cstdio>
#include<cstring>
using namespace std;
#define N 52
int g[N][N];
int c[N];
int id(char a1, char a2)//给每个标号分配一个id
{
	return (a1 - 'A') * 2 + (a2 == '+' ? 0 : 1); //*2就可以保证不会出现不一样的符号id重复
}
void connect(char a1, char a2, char b1, char b2)//将输入的正方形转化为有向图
{ //每个正方形相当于一个边，把两个符号直接内部连接起来
	if (a1 == '0' || b1 == '0')return;    //若拼接在一起 A+与A- 二进制id除第一位以外都是一样的
	int u = id(a1, a2) ^ 1, v = id(b1, b2);//因为id(a1,a2)^1一定能够和id(a1,a2)拼接在一起，因此意味着id(a1,a2)^1可以和id(b1,b2)拼接在一起
	g[u][v] = 1;
}
bool toposort(int u)
{
	c[u] = -1;   //访问标志
	for (int v = 0; v < N;v++)
	if (g[u][v]) //存在小于关系
	{
		if (c[v] < 0)return true;//存在有向环，返回true
		else if (!c[v] && toposort(v))return true; //c[v]为0才dfs
	}
	c[u] = 1;
	return false;//不存在有向环
}
bool cycle()
{
	memset(c, 0, sizeof(c));
	for (int i = 0; i < N;i++)     //双层遍历
	if (!c[i]) //若i没被访问，那么再次访问
	if (toposort(i))return true;//存在有向环，返回true
	return false;
}
int main()
{
	int n;
	while (~scanf("%d", &n)&&n)
	{
		memset(g, 0, sizeof(g));
		while (n--)
		{
			char s[10];
			scanf("%s", s); //读取每个矩形的描述，假设按顺时针方向读取，各种组合全部遍历
			for (int i = 0; i < 4;i++)
			for (int j = 0; j < 4;j++)
			if (i != j)
				connect(s[i * 2], s[i * 2 + 1], s[j * 2], s[j * 2 + 1]);
			/*
			0 1 2 3  上右     0 1 4 5 上下   0 1 6 7 上左
			2 3 0 1  右上     2 3 4 5 右下   2 3 6 7 右左
			………………………………
			*/
		}
		printf("%s\n", cycle() ? "unbounded":"bounded");
	}
	return 0;
}
