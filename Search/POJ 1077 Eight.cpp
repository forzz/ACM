#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
char c;
int a[10][10],b[10],d[1000],deep,stx,sty;
char ans[4]={'u','d','l','r'};
bool ok=0;
map<int,bool> vis;//map判重
int fx[4]={-1,1,0,0};
int fy[4]={0,0,-1,1};
int Abs(int x)//求绝对值
{
	return x<0?-x:x;
}
bool solve()
/*
根据逆序数直接判断有无解，对于一个八数码，依次排列之后，每次是将空位和相邻位进行调换，研究后会发现，每次调换，逆序数增幅都为偶数，
也就是不改变奇偶性，所以只需要根据初始和目标状态的逆序数正负判断即可。
*/
{
	int ret=0;
	for(int i=1;i<=9;i++)
	for(int j=1;j<i;j++)
	{
		if(b[j]>b[i] && b[i])
		ret++;
	}
	return !(ret%2);//求得逆序数
}
int Astar()//曼哈顿距离求估价函数h
{
	int h=0;
	for(int i=1;i<=3;i++)
	for(int j=1;j<=3;j++)
	if(a[i][j]!=0)
	{
		int tx=(a[i][j]-1)/3;//数字a[i][j]最终坐标
		int ty=(a[i][j]-1)%3;
		h+=(Abs(i-tx-1)+Abs(j-ty-1));
	}
	return h;
}
int zt()   //hash当前九宫格
{
	int ztt=0;
	for(int i=1;i<=3;i++)
	for(int j=1;j<=3;j++)
	{
		ztt=ztt*10+a[i][j];
	}
	return ztt;
}
void IDAstar(int x,int y,int step)
{
	if(ok)
	return;
	int h=Astar();
	if(!h && zt()==123456780)  //到达终点
	{
		for(int i=0;i<step;i++)
			cout<<ans[d[i]];//输出路径
		ok=1;
		cout<<endl;
		return;
	}
	if(step+h>deep)
	return;
	int now=zt();
	if(vis[now])
	return;
	vis[now]=1;
	for(int i=0;i<4;i++)
	{
		int nex=x+fx[i],ney=y+fy[i];
		if(nex>=1 && nex<=3 && ney>=1 && ney<=3)
		{
			d[step]=i;//记录方向
			swap(a[x][y],a[nex][ney]);
			IDAstar(nex,ney,step+1);
			swap(a[x][y],a[nex][ney]);  //恢复状态(容易恢复就直接在原图修改)
			d[step]=0;
		}
	}
	return;
}
int main()
{
	char k;
	while(cin>>k)
	{
		ok=0;
		deep=0;
		char c;
		for(int i=1;i<=9;i++)//读入数据
		{
			if (i==1) c=k;
			else
				cin>>c;
			if(c=='x')
			b[i]=0;
			else
			b[i]=c-'0';
		}
		if(!solve())//由逆序数判断是否有解
		{
			cout<<"unsolvable"<<endl;
			continue;
		}
		int ret=1;
		for(int i=1;i<=3;i++) //放入二维数组，记录0位置
		for(int j=1;j<=3;j++)
		{
			a[i][j]=b[ret];
			if(a[i][j]==0)
			{
				stx=i;
				sty=j;
			}
			ret++;
		}
		while(!ok)//迭代加深
		{
			vis.clear();
			IDAstar(stx,sty,0);
			deep++;
		}
	}
	return 0;
}
