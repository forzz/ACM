#include <stdio.h>
#include <string.h>
int square1[12][12],square2[12][12];
int judge(int n1,int n)   //n1代表边长 n代表确切行列数
{
	int sum=0;
	for(int i=1;i<=n-n1+1;i++)
	{
		for(int j=1;j<=n-n1+1;j++)
		{                               //每个遍历，以该点为左上角点
			int ok=1,k;
			for(k=j;k<n1+j;k++)//同一行，n1为边长，保证正方形的行是对的
				if(!square1[i][k]||!square1[i+n1][k]) {ok=0;break;}
				for(k=i;k<n1+i;k++)//同一列，保证正方形的列是对的
					if(!square2[k][j]||!square2[k][j+n1]) {ok=0;break;}
				if(ok) sum++;
		}
	}
	return sum;
}
int main(void)
{
	int m,n,game=1;
	while(scanf("%d",&n)==1)  //n*n的网格
	{
		memset(square1,0,sizeof(square1));
		memset(square2,0,sizeof(square2));
		if(game-1) printf("\n**********************************\n\n");//如果是第一次以后 要加星号
		printf("Problem #%d\n\n",game++);
		scanf("%d",&m);
		char ch;
		int i,j;
		while(m--)
		{
			getchar();
			scanf("%c %d %d",&ch,&i,&j);
			if(ch=='H') square1[i][j]=1;//将两种线段分别储存在两个数组当中
			if(ch=='V') square2[j][i]=1;
		}
		int n1=1,ok=0;
		while(n1<n)
		{
			if(judge(n1,n-1))   //n1代表边长，n是确实存在的行列数
			{
				ok=1;
				printf("%d square (s) of size %d\n",judge(n1,n-1),n1);
			}
			n1++;
		}
		if(!ok) printf("No completed squares can be found.\n");
	}
	return 0;
}
