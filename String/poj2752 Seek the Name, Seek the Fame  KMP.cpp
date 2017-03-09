#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int nxt[400005];
char str[400005];
int ans[400005];
int cnt;
int len;
void getnxt()
{
	nxt[0] = -1;
	int i = 0, j = -1;      //i表示模板字符串下标，j表示当前最大前后缀长度（由于nxt数组是从0开始，所以j表示最大前缀的下一位,也就是失配位）
	while (i < len)     //i表示失配位的前一位 也就是需要寻找前后缀的字符串的尾部
	{
		if (j == -1 || str[i] == str[j])//j=-1表示比较到空位0，i和j如果相等，那么最大相同前后缀长度加1
		{
			++i;
			++j;
			nxt[i] = j;//失配位nxt值求出
		}
		else j = nxt[j];//返回失配位j之前的最长公共前后缀，再次比较i和j
	}
}
int main()
{
	while (scanf("%s", str) != EOF)
	{
		len = strlen(str);
		getnxt();
		cnt = 0;
		int t = nxt[len - 1];//t为上一个失配位
		while (t != -1)     //t到-1就说明没有前后缀可以匹配了
		{
			if (str[t] == str[len - 1]) ans[cnt++] = t + 1;//由大到小找出所给串的所有前缀长度，使得所给串中这个长度的前缀==这个长度的后缀
			t = nxt[t];
 //
		}
		for (int i = cnt - 1; i >= 0; --i)
		{
			printf("%d ", ans[i]);
		}
		printf("%d\n", len);
	}
	return 0;
}
//求出next值：[非修正]
//下标：      0  1  2  3  4  5  6  7  8  9  10  11   12  13  14  15  16  17
//串：           a  b  a  b  c  a  b  a  b   a   b    a   b   c   a   b   a   b
//next值：   -1  0  0  1  2  0  1  2  3  4   3   4    3   4   5   6   7   8   9
//len = 18  str[t] == str[len - 1]
//说明对于前面长度为18的字符串，【长度为9的前缀】和【长度为9的后缀】是匹配的, 也就是整个串的最大前后缀匹配长度就是9,没有更大的可能
//问题就转化成串（前9）的前缀跟串（后9）的后缀的匹配问题，又因为后者的后缀和前者的后缀相同 问题就转化为串(前9)的前后缀匹配问题

