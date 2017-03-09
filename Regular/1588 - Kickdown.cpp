#include <iostream>
#include <cstring>

using namespace std;

char str1[222];
char str2[222];

int main()
{
	int i,j,len1,len2,x1,x2;
	while(cin>>str1>>str2)
	{
		len1=strlen(str1);
		len2=strlen(str2);
		memset(str1+len1,0,sizeof(str1)-len1);		//输入数据后，将空余的元素（空余的元素！！！）全变成0，方便计算
		memset(str2+len2,0,sizeof(str2)-len2);
		for(i=0;i<len1;i++)		//将字符换算成数字
			str1[i]-=48;
		for(i=0;i<len2;i++)
			str2[i]-=48;
		for(i=0;i<len1;i++)
		{
			for(j=0;j<len2;j++)
				if(str1[i+j]+str2[j]>3)
					break;
			if(j==len2)		//内循环结束后直接跳出
				break;
		}
		x1=len2+i;		//经过一个方向的比较得到一个长度值
		for(i=0;i<len2;i++)
		{
			for(j=0;j<len1;j++)
				if(str2[i+j]+str1[j]>3)
					break;
			if(j==len1)		//内循环结束后直接跳出
				break;
		}
		x2=len1+i;		//经过另一个方向的比较得到的长度值
		cout<<max(max(len1,len2),min(x1,x2))<<endl;		//这个复合取大小值的真心好用，简单粗暴
	}

	return 0;
}