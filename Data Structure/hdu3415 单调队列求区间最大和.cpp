#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;
int a[100100];
int sum[210000];
const int INF = 0x3fffffff;
int main()
{
    int t,n,m,i,k,head,end;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        m = n;
        sum[0] = 0;
        for(i = 1; i<=n; i++)
        {
            scanf("%d",&a[i]);
            sum[i] = sum[i-1]+a[i];//将前i项和全部存入sum数组中
        }
        int ans = -INF;
        for(i = n+1; i<n+k;i++)
//因为序列是环状的，所以可以在序列后面复制前k-1个数字。任意一个子序列[i..j]的和就等于s[j]-s[i-1]。
            sum[i] = sum[i-1]+a[i-n];
        n = n+k-1;
        deque<int> Q;//双向队列（保存索引）
        Q.clear();
        for(i = 1; i<=n; i++)
        {
            while(!Q.empty() && sum[i-1]<sum[Q.back()])//求最小值要保持单调队列递增
//因为当前要插入的元素位置更大，值更小。这样找到的s[j]能更大，求出来的解更小
                Q.pop_back();
            while(!Q.empty() && Q.front()<i-k)//超过k的长度则消除队列前面的元素
                Q.pop_front();
            Q.push_back(i-1);
            if(sum[i]-sum[Q.front()]>ans)//记录最优解，sum[n]-sum[m]所得出的是n-1到m+1之间的和
            {
                ans = sum[i]-sum[Q.front()];
                head = Q.front()+1;
                end = i;
            }
        }
        if(end>m)
        end%=m;
        printf("%d %d %d\n",ans,head,end);
    }
    return 0;
}
/*
单调递减队列是这么一个队列，它的头元素一直是队列当中的最大值，而且队列中的值是按照递减的顺序排列的。
我们可以从队列的末尾插入一个元素，可以从队列的两端删除元素。
1.插入元素：为了保证队列的递减性，我们在插入元素v的时候，要将队尾的元素和v比较，
  如果队尾的元素不大于v,则删除队尾的元素，然后继续将新的队尾的元素与v比较，直到队尾的元素大于v,这个时候我们才将v插入到队尾。
2.删除元素：由于我们只需要保存i的前k-1个元素中的最大值，所以当队首的元素的索引或下标小于i-k+1的时候，
  就说明队首的元素对于求f(i)已经没有意义了，因为它已经不在窗里面了。所以当index[队首元素]<i-k+1时，将队首元素删除。
3.从上面的介绍当中，我们知道，单调队列与队列唯一的不同就在于它不仅要保存元素的值，而且要保存元素的索引
 （当然在实际应用中我们可以只需要保存索引，而通过索引间接找到当前索引的值）。
*/
