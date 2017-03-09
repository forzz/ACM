#include <iostream>
using namespace std;
int main()
{
	int i,j,flag;
	char s[12];
	char s1[6],s2[6];
	while(cin>>s)
	{
		for(i=0; i<6; i++)s1[i]=s[i];
		while(i<12)
		{
			s2[i-6]=s[i];
			i++;                     //把两个方块的面全部读入
		}
		for(i=0; i<3; i++)
		{
			flag=0;
			for(j=0; j<6; j++)//双重遍历，不需要排序了
				if(s1[i]==s2[j]&&s1[5-i]==s2[5-j])
				{
					s2[j]=0;
					s2[5-j]=0;
					flag=1;
					break;
				}
				if(flag==0)break;
		}
		if(flag==0) cout<<"FALSE"<<endl;
		else cout<<"TRUE"<<endl;
	}
	return 0;
}