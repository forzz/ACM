#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <queue>
using namespace std;
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		int num, index;
		queue<int> q;
		priority_queue<int> pq;
		cin>>num>>index;
		for(int j=0;j<num;j++)
		{
			int rate;
			cin>>rate;
			pq.push(rate);
			q.push(rate);
		}
		int x = 0;
		while(1)
		{
			if(q.front()==pq.top())//优先队列出队元素不是最先进队的元素，用pop
			{
				if(x==index)//目标元素
				{
					cout<<num-q.size()+1<<endl;//输出完成任务所需时间
					break;
				}
				else
				{
					q.pop();
					pq.pop();
					x++;
				}
			}
			else
			{
				int temp = q.front();//队首元素压入队尾
				q.pop();
				q.push(temp);
				if(x==index)//追踪目标元素，index现在改成了队尾元素所在的位置
				{
					x=0;
					index=q.size()-1;
				}
				else
				{
					x++;
				}
			}
		}
	}
	return 0;
}
