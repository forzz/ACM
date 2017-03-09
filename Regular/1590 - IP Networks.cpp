#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int zwym_table[9] = {255, 254, 252, 248, 240, 224, 192, 128, 0};   //11111111  11111110   11111100 11111000类似

int main()
{
	int ip[4][1024];
	int m;
	while(scanf("%d",&m)!=EOF)
	{
		memset(ip, 0, sizeof(ip));
		int zwym[4];
		int minip[4];
		for(int i=0; i<m; i++)
			scanf("%d.%d.%d.%d",&ip[0][i], &ip[1][i], &ip[2][i], &ip[3][i]);  //4行n列 按列存储每个ip地址 这样能让每一个元素都可以排序
		for(int i=0; i<4; i++)//每一个小节进行比较
		{
			int dif=0, x, j;  //如果没有，那么dif就是0
			int p,q;
			sort(ip[i], ip[i]+m);//进行排序
			p = ip[i][m-1];
			q = ip[i][0];               //找到最大值和最小值
			for(j=1; j<=8; j++)
			{
				if(p%2!=q%2)//检验最后1位是否相同
					dif = j;   //dif两者不同的位数
				p = p/2;     //除以2相当于右移一位
				q = q/2;
			}
			zwym[i] = zwym_table[dif];
			minip[i] = ip[i][0] & zwym[i]; //minip保存的是从不同的那一位后面全是0，保证minip比所有ip都小
		}
		for(int i=0; i<4; i++) //子网掩码小于255时，其后面全是0，而且ip也全是0，这是最终判断
		{
			if(zwym[i] != 255)
			{
				for(i = i+1; i<4; i++)
				{
					zwym[i] = 0;
					minip[i] = 0;
				}
				break;
			}
		}
		printf("%d.%d.%d.%d\n",minip[0], minip[1], minip[2], minip[3]);
		printf("%d.%d.%d.%d\n",zwym[0], zwym[1], zwym[2], zwym[3]);
	}
	return 0;
}