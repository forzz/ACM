#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
int Find(const int *b, int n, int k)
{
	int i;
	for(i = 0; i < n; i++)
		if(b[i] == k)
			return i;
	return -1;
}
int main()
{
	int n, m, t_n;//n除以m
	int a[10000];//商
	int b[10000];//余数
	int i, j, flag, cycle;
	while(cin >> n >> m)
	{
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		i = 0;
		t_n = n;
		do
		{
			a[i] = n / m;
			b[i] = n % m;
			n = b[i] * 10;
			i++;
			flag = Find(b, i - 1, b[i - 1]);
		}
		while(flag == -1);

		cycle = i - flag - 1;
		printf("%d/%d = ", t_n, m);
		for(j = 0; j < i; j++)
		{
			if(j == 0)
				printf("%d.", a[j]);
			else
				printf("%d", a[j]);
			if(j == flag)
				printf("(");
			if(j - flag == 50)
			{
				printf("...");
				break;
			}
		}
		printf(")\n   %d = number of digits in repeating cycle\n\n", cycle);
	}
	return 0;
}
