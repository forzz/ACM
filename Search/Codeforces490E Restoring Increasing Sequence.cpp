#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 5;
const int maxm = 10;
int N, len[maxn];
char s[maxn][maxm];
void init () { //读取数据
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%s", s[i]);
}
inline void fill(int d) {//
	for (int i = 0; i < len[d]; i++)
		if (s[d][i] == '?')
			s[d][i] = (i == 0 ? '1' : '0');
}
bool dfs (char* a, char* b, int d, int n) {
	if (d >= n)
		return false;

	if (b[d] != '?') {
		if (a[d] == b[d])
			return dfs(a, b, d + 1, n);
		else
			return a[d] < b[d];
	} else {
		b[d] = a[d];
		if (dfs(a, b, d + 1, n))
			return true;
		if (b[d] != '9') {
			b[d]++;
			return true;
		}
		b[d] = '?';
		return false;
	}
}
bool solve() {
	len[0] = 1;
	s[0][0] = '0';
	for (int i = 1; i <= N; i++) {
		len[i] = strlen(s[i]);
		if (len[i] < len[i-1])
			return false;
		else if (len[i] == len[i-1] && dfs(s[i-1], s[i], 0, len[i]) == false)
			return false;
		fill(i);
	}
	return true;
}
int main () {
	init();
	if(solve()) {
		printf("YES\n");
		for (int i = 1; i <= N; i++)  //s数组保存答案
		   printf("%s\n", s[i]);
	} else
		printf("NO\n");
	return 0;
}
