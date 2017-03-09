#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;
typedef pair<int,int> point;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		set<point> data;
		cin>>n;
		int sum = 0;
		for(int j=0;j<n;j++)
		{
			int x,y;
			cin>>x>>y;
			sum+=x;             //求出所有x的和，本来应该除以n求出平均值，为了保证中点x不是小数乘n
			data.insert(point(x*n,y)); //各个x都乘n，相当于横坐标扩大n倍
		}
		bool flag = true;
		for(auto i=data.begin();i!=data.end();i++)
		{
			point p = *i;
			if(data.find(point(2*sum-p.first,p.second))==data.end())
			{
				flag = false;
				break;
			}
		}
		if(flag==true)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
