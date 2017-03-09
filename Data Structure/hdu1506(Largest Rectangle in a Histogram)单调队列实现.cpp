#include<iostream>
#include<cstdio>
using namespace std;
long long h[100005];
int rt[100005],lt[100005],q[100005];
int main()
{
        //单调序列就是一个原有序列的子集，这个子集保持单调性，但各个元素的次序与最初相同，在把元素放入队列的过程中可以直接求得每个元素与单调队列的关系
	int n,i;
	while(cin>>n&&n)
	{
		for(i=0;i<n;i++)
		{
			cin>>h[i];
			rt[i]=n-1,lt[i]=0;//lt[1~n]一开始要初始化为n-1 rt[1~n]初始化为0 处理极限（就是如果没出过队就是覆盖所有长度）
		}
		int head=0,tail=0;//队列首尾指针，初始为空
		q[0]=0;//队列初始时存入首元素的下标
		for(i=1;i<n;i++)//从左到右延伸（递增序列）一次遍历可求得所有点向右延伸的最大距离
		{
			while(head<=tail&&h[i]<h[q[tail]])//当前结点高度比队列尾小
			{
				rt[q[tail]]=i-1;//tail向右延伸的最大位置
				tail--;//当前尾节点出队列
			}
			q[++tail]=i;//i入队列
		}
		head=0,tail=0;//队列首尾指针，初始为空
		q[0]=n-1;//队列初始时存入末尾元素的下标
		for(i=n-2;i>=0;i--)//从右到左延伸（递增序列）
		{
			while(head<=tail&&h[i]<h[q[tail]])
			{
				lt[q[tail]]=i+1;////向左延伸的最大位置
				tail--;
			}
			q[++tail]=i;//维护一个递增队列
		}
		long long tmp,maxn=0;
		for(i=0;i<n;i++)
		{
			tmp=(rt[i]-lt[i]+1)*h[i];
			if(tmp>maxn) maxn=tmp;
		}
		cout<<maxn<<endl;
	}
	return 0;
}
