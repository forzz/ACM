#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<sstream>
using namespace std;

typedef pair<int,int> PII;

const int maxr = 10000 + 5;
const int maxc = 10 + 5;

int m, n, db[maxr][maxc], cnt;

map<string, int> id;//为每个字符串编号
int ID(const string& s) {   //将每个字符串编号
	if(!id.count(s)) {//如果之前未出现
		id[s] = ++cnt;//自动初始化一个map，并且赋值
	}
	return id[s];
}

void find() {
	for(int c1 = 0; c1 < m; c1++)//按列遍历
		for(int c2 = c1+1; c2 < m; c2++) {//下一列
			map<PII, int> d;
			for(int i = 0; i < n; i++) {//按行遍历，每一行构造一个pair
				PII p = make_pair(db[i][c1], db[i][c2]); //返回一个已初始化的pair数据p
				if(d.count(p)) {//返回关键字为p的元素数量，如果是普通map，是0或1
					printf("NO\n");
					printf("%d %d\n", d[p]+1, i+1);
					printf("%d %d\n", c1+1, c2+1);
					return;
				}
				d[p] = i;
			}
		}
		printf("YES\n");
}


int main() {
	string s;
	while(getline(cin, s)) {       //统一读入每一行，然后存到ss流中分开读取
		stringstream ss(s);
		if(!(ss >> n >> m)) break;
		cnt = 0;
		id.clear();
		for(int i = 0; i < n; i++) {   //n为行数
			getline(cin, s);   //读入每行数据
			int lastpos = -1;
			for(int j = 0; j < m; j++) {  //m为列数
				int p = s.find(',', lastpos+1);    //从lastpos+1开始查找“，” p为逗号位置
				if(p == string::npos) p = s.length();//string::npos定义为保证大于任何有效下标的值，代表查找不到
				db[i][j] = ID(s.substr(lastpos+1, p - lastpos - 1));//复制子字符串，从指定位置开始，带指定长度。
				lastpos = p;
			}//完全读入每一个数据
		}
		find();
	}
	return 0;
}
