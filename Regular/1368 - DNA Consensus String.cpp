﻿#include<cstdio>
#include<cstring>


char DNA[51][1010],s[1100];
int pos[4]= {0,2,6,19},m,n,d[1100];
int main()
{
	int t,pd[26];
	scanf("%d",&t);
	while(t--)
	{
		memset(s,0,sizeof(s));
		memset(d,0,sizeof(d));
		scanf("%d %d",&m,&n);
		for(int i = 0; i < m; i++)
			scanf("%s",DNA[i]);
		for(int j = 0; j < n; j++)    //先列后行，顺序遍历
		{
			memset(pd,0,sizeof(pd));
			for(int i = 0; i < m; i++)
			{
				pd[DNA[i][j]-'A']++;   //pd代表的是每个字符出现的次数
			}
			int max = 0;
			for(int i = 0; i < 4; i++)
			{
				if(max < pd[pos[i]])   //找到最大值，将其下标记作max
				{
					max = pd[pos[i]];
					s[j] = pos[i]+'A';  //s是目标字符串
				}
			}
			d[j] = max;
		}
		puts(s);
		int temp=0;
		for(int i = 0; i < n; i++)
			temp += d[i];
		printf("%d\n",m*n-temp);//这是用一个减法求出来的
	}
	return 0;
}