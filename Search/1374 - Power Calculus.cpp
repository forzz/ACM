#include<cstdio>
#include<cstring>
const int N = 1005;
int s[N],n,d;
bool dfs(int cur) {
	int pre = s[cur - 1];//每次总使用刚刚得到的数
	if(cur == d) {
		if(pre == n)  //找到结果
			return true;
		return false;
	}
	if(pre << (d - cur) < n)  //A*剪枝函数
		return false;
	for(int i = 0; i < cur; i++) {
		s[cur] = s[i] + pre; //当前乘法所有可能
		if(s[cur] <= 1000 && dfs(cur + 1))
			return true;
		s[cur] = pre - s[i];//当前除法所有可能
		if(s[cur] > 0 && dfs(cur + 1))
			return true;
	} //虽然更改了全局变量 但是新的递归不会使用false递归的数值 不需要恢复状态
	return false;
}
int main() {
	while(scanf("%d",&n) && n) {
		s[0] = 1;
		d = 1;  //d为深度
		while(!dfs(1)) d++;
		printf("%d\n",d - 1);
	}
}
