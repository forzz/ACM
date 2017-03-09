#include<stdio.h>
#define N 1000
int n;
int a[15], b[15], c[15];
int main()
{
	int rnd = 0;
	while (scanf("%d",&n),n)
	{
		for (int i = 0; i < n; i++)
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		int t,count;
		for (t = 1; t < N;t++)
		{
			count = 0;  //count代表清醒的人数
			for (int i = 0; i < n;i++)
				if (c[i] <= a[i])//  c[i]代表周期内的第c[i]分钟
					count++;//说明这个人在清醒状态
			if (count == n) break;
			for (int i = 0; i < n; i++)
			{
				if (c[i] == a[i] + b[i] || (c[i] == a[i] && count >= n - count))
			//当到达周期末尾或到达即将睡觉的时候却发现清醒人数不少于睡觉人数时，重新开始计时
					c[i] = 0;
				c[i]++;//每一个人的时间都更新+1
			}
		}
		if (t == N) t = -1;
		printf("Case %d: %d\n", ++rnd, t);
	}
	return 0;
}