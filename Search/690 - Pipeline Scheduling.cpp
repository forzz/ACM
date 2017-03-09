#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 5;
const int M = 100;
int n, c, ans, w[N], jump[M];
bool judge (int* s, int k) {//第k个时间片（列）
	for (int i = 0; i < N; i++) {   //每个工作单元（行）
		if ((s[i]>>k)&w[i]) return false;
//如果该时间片中该工作单元的起始时间片和第i个时间片都为1，说明第i个时间片不能为任务起始
	}
	return true;
}
void init () {//读入保留表
	char str[M];
	c = 0;
	ans = n * 10;
	memset(w, 0, sizeof(w));
	for (int i = 0; i < N; i++) {          //5个工作单元
		scanf("%s", str);
		for (int j = 0; j < n; j++)    //n个时间片
			if (str[j] == 'X')
				w[i] |= (1<<j);  //数据压缩
	}
	for (int i = 0; i <= n; i++) {//n个时间片
		if (judge (w, i)) {      //n次平行移动任务保留表
			jump[c++] = i;   //剪枝，开数组把不能放的位置剔除掉
		}
	}
}
void dfs (int* s, int d, int sum) {//第d个任务 总步数为sum
	if (sum + jump[0] * (10 - d) > ans) return;
/*
从当前结点开始，每次都走最小步数（最小步数就是摆放第二个任务时可以走得最小步数）
如果这样到最后的结果还要大于目前的最优解，则剪枝。
*/
	if (d == 10) {
		ans = min (ans, sum);//更新答案
		return;
	}
	for (int i = 0; i < c; i++) {     //c个可放位置
		if (judge (s, jump[i])) {
			int p[N];  //建立新的图
			for (int j = 0; j < N; j++)   //N行，
				p[j] = (s[j]>>jump[i])^w[j];//保留表平移jump[i]位 见1则1
			dfs (p, d + 1, sum + jump[i]);//当前最大值sum右平移jump[i]个单位
		}
	}
}
int main () {
	while (scanf("%d", &n), n) {
		init ();
		dfs (w, 1, n);
		printf("%d\n", ans);
	}
	return 0;
}
