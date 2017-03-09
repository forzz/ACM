#include<stack>
#include<queue>
#include<cstdio>
using namespace std;
const int N = 5e5;
int T, n, a[N], L[N], R[N], cas = 0;
int main()
{
/*
给出一个数组，问你对于第i个数，从最后一个比它大的数到它之间比它小的数中最大的那个数的下标，
以及它右边到第一个比它大的数中比它小的数中最大的那一个数的下标<下标从1开始>。
eg：5 2 4 3 1
l 0 0 2 0 0 对5来说左边比它小的数没有，所以是0。对2来说左边比它小的数没有，所以是0。对4来说左边比它小的数是2，所以下标是2。
r 3 0 4 5 0 对5来说右边比它小的数中最大的是4，是第3个，所以答案是3。对2来说右边比它小的数是1，但是4比2大，所以无法到达1，所以答案是0。对于4，右边比它小的数中最大一个3的下标是4，所以答案是4。
*/
	scanf("%d", &T);
	while (T--)
	{
                stack<int> p;
                scanf("%d", &n);
		for (int i = 1; i <= n; i++)
                        scanf("%d", &a[i]), L[i]=R[i]=0;
		for (int i = 1; i <= n; i++)//枚举每个数
		{
			while (!p.empty() && a[p.top()] < a[i])//从左到右单调递减栈（每个出栈的数都可能是栈顶元素的结果）
			{
				int q = p.top();     p.pop();
				if (!p.empty()) R[p.top()] = q;//栈顶元素右边的解暂时记为出栈的数
			}
			p.push(i);//每次都会压入i，栈并不是递减，但可以保证每次i入栈前栈顶比i大
		}
		while (!p.empty())
		{
			int q = p.top();     p.pop();
			if (!p.empty()) R[p.top()] = q;
		}
		for (int i = n; i >= 1; i--)//从右到左单调递减栈
		{
			while (!p.empty() && a[p.top()] < a[i])
			{
				int q = p.top();     p.pop();
				if (!p.empty()) L[p.top()] = q;
			}
			p.push(i);//压入索引
		}
		while (!p.empty())
		{
			int q = p.top();     p.pop();
			if (!p.empty()) L[p.top()] = q;
		}
		printf("Case %d:\n", ++cas);
		for (int i = 1; i <= n; i++)
                        printf("%d %d\n", L[i], R[i]);
	}
	return 0;
}
/*
单调栈有以下两个性质：
1、若是单调递增栈，则从栈顶到栈底的元素是严格递增的。若是单调递减栈，则从栈顶到栈底的元素是严格递减的。
2、越靠近栈顶的元素越后进栈。
单调栈与单调队列不同的地方在于栈只能在栈顶操作，因此一般在应用单调栈的地方不限定它的大小，否则会造成元素无法进栈。
元素进栈过程：对于单调递增栈，若当前进栈元素为e，从栈顶开始遍历元素，把小于e或者等于e的元素弹出栈，直接遇到一个大于e的元素或者栈为空
为止，然后再把e压入栈中。对于单调递减栈，则每次弹出的是大于e或者等于e的元素。
*/
