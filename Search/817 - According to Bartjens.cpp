#include <stdio.h>
#include <string.h>
#include <string>
#include <set>
#include <iostream>
using namespace std;
const char c[3] = {'*', '+', '-'};
const int N = 25;
char str[N], re[N];
set<string> output;
int n, res[N], flag;
void init() {
	output.clear();
	flag = 1;
	n = strlen(str) - 1; //间隔个数
}
int tra() {
	int num[N], num1[N], ans = 0, numn = 0, i, numn1 = 0, res1[N], resn = 0, res2[N], res2n = 0;
	num[0] = str[0] - '0'; //首位必数字
	for (i = 0; i < n - 1; i++) {//把str数组中的数字全部抽出来存入num数组中
		if (res[i] == 3) {//不放符号
			if (num [numn] == 0) return 0;
			num[numn] = num[numn] * 10 + str[i + 1] - '0';
		}
		else {//因为只能放一个符号，符号的下一个肯定是数字
			res1[resn++] = res[i];
			num[++numn] = str[i + 1] - '0';
		}
	}
	num1[0] = num[0];//首位必为数字    num1保存乘法结束后的第二级运算
	for (i = 0; i < resn; i ++) {
		if (res1[i] == 0) { //乘法
			num1[numn1] *= num[i + 1];
		}
		else {
			res2[res2n++] = res1[i]; //把加号减号所在的位置存入res1数组中
			num1[++numn1] = num[i + 1];//把下一位保存到num1数组中
		}
	}
	ans = num1[0];//ans保存结果
	for (i = 0; i < res2n; i ++) {
		if (res2[i] == 1)
			ans += num1[i + 1];
		else
			ans -= num1[i + 1];
	}
	return ans;
}

void dfs(int len) {
	if (len == n - 1) {//递归结束
		int num = tra();
		if (num == 2000) { //符合情况
			flag = 0;
			memset(re, 0, sizeof(re));
			int ren = 1;
			re[0] = str[0];//首位
			for (int j = 0; j < len; j ++) {
				if (res[j] == 3)   //不放符号
					re[ren++] = str[j + 1];
				else {  //先放符号，再放数字
					re[ren++] = c[res[j]];
					re[ren++] = str[j + 1];
				}
			}
			output.insert(re);
		}
		return;
	}
	for (int i = 0; i < 4; i ++) {//四种情况（i=3时为不放置）
		res[len] = i;
		dfs(len + 1);
	}
}

void solve() {
	if (strcmp(str, "2000=") == 0) {  //特殊情况，算为失败
		printf("  IMPOSSIBLE\n");
		return;
	}
	dfs(0);
	if (flag) printf("  IMPOSSIBLE\n");
	else {
		for (set<string>::iterator it = output.begin(); it != output.end(); it++)
			cout <<"  "<<*it<<"="<<endl;
	}
}

int main() {
	int cas = 0;
	while (~scanf("%s", str) && str[0] != '=') {
		init();
		printf("Problem %d\n", ++cas);
		solve();
	}
	return 0;
}
