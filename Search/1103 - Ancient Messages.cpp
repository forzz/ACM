#include <bits/stdc++.h>
using namespace std;
const string dict[16] = {
	"0000", "0001", "0010", "0011",
	"0100", "0101", "0110", "0111",
	"1000", "1001", "1010", "1011",
	"1100", "1101", "1110", "1111",
};
const int dir[4][2] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };  //四种连通方向
const char alp[8] = { 'W', 'A', 'K', 'J', 'S', 'D' };  //洞对应的字母
map<char, int> cnt;
char tab[256][256];
int H, W, kase, cur;
bool isin(const int r, const int c){//该坐标在图内，因为dfs要查找4个方向的坐标，会超出范围
	return r >= 0 && r <= H + 1 && c >= 0 && c <= W + 1;
}
void DFS1(const int r, const int c){
	//将相连的0全部转化为1
	if (!isin(r, c) || tab[r][c]!='0') return;
	tab[r][c] = '-';
	for (int i = 0; i < 4; ++i) //继续查找外围的坐标
		DFS1(r + dir[i][0], c + dir[i][1]);
}
void DFS2(const int r, const int c){
	if (!isin(r, c) || tab[r][c] != '1') return;
	tab[r][c] = '-';
	for (int i = 0; i < 4; ++i){
		int r1 = r + dir[i][0], c1 = c + dir[i][1];
		if (tab[r1][c1] == '0')
			++cur, DFS1(r1, c1);
		else DFS2(r1, c1);
	}
}
int main()
{               //while类似for 可以先执行一部分命令
	while (memset(tab, '0', sizeof(tab)), cnt.clear(), cin >> H >> W, H || W){ //条件只有H || W
		W *= 4;   //H为行，W为列
		for (int i = 1; i <= H; ++i){
			string line, res; cin >> line;
			for (auto i : line) //c++11，遍历line 每个元素赋值到i
                                res += dict[i >= 'a' ? (i - 'a' + 10) : (i - '0')];
                        //res每一行表示16进制转2进制后的结果
			memcpy(tab[i]+1, res.c_str(), W);//tab[i][0]不保存值，作为外围
//c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同. 为了与c语言兼容，在c语言中没有string类型，
//故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式。
		}
		DFS1(0, 0);
		for (int i = 1; i <= H; ++i){
			for (int j = 1; j <= W; ++j){
				if (tab[i][j] != '1') continue;
				cur = 0;
				DFS2(i, j);
				cnt[alp[cur]]++;
			}
		}
		printf("Case %d: ", ++kase);
		for (auto i : cnt) while (i.second--) cout << i.first;
		cout << endl;
	}
	return 0;
}
