#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

int Q[10000];

int main()
{
	int n;
	while (cin >> n && n) {
		for (int i = 0; i <= n; ++ i)//初始化
			Q[i] = i;
		int head = 1,tail = n,first = 1;//Q[0]不存数值
		printf("Discarded cards:");
		while (head < tail) {//head=tail代表只有一张
			if (!first) printf(",");
			printf(" %d",Q[head ++]);
			Q[++ tail] = Q[head ++];
			first = 0;
		}
		printf("\nRemaining card: %d\n",Q[head]);
	}
    return 0;
}
