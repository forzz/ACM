#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 100005
#define MAXM 450
#define MOD 998244353
int n,c,l,r,dp[2][MAXN];
int main()
//开始的时候有一个大小为1的数 然后我们每次操作要么把所有的数+1  要么就把所有的数+1在添加一个新的数1，这样就可以不重不漏的枚举到所有的自然数组合
//把一个整数n，划分为m个不同的数的和
//转移方程为dp[m][n] = dp[m][n - m] + dp[m - 1][n - m]    当前状态是由2个状态直接得来
//dp[m][n - m] : 将分成的m个不同的数都减去1,导致出现划分的数中有1的情况的丢失,
//需要加上dp[m - 1][n - m]，划分数中有1的所有情况
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&n,&c,&l,&r);
        l -= c,r = min(r - c,n - 1);
        memset(dp,0,sizeof(dp));//dp[i][j]的值不用每次都初始化，因为它的值不受输入的影响，如果前面算过了就直接拿来用，没算过就拿来算并记录下来
        dp[0][0] = 1;           //边界条件
        int ans = l <= 0 ? 1 : 0;
//选取了i个划分 总和j的范围是n=100000  所以i的数量应该小于根号（2n）的 （前i项和i(i+1)/2<=n） 即n根号n的复杂度  (i + 1) * i / 2前n个自然数的和
        for(int i = 1;(i + 1) * i / 2 <= r;i++)     //选取i个划分
        {
            for(int j = (1 + i) * i / 2;j <= r;j++) //j是从1到i自然数和开始
            {
                dp[i & 1][j] = (dp[i & 1][j - i] + dp[(i - 1) & 1][j - i]) % MOD;   //因为状态不需要保存，只需要计算个数，滚动数组压缩空间
                if(l <= j && j <= r)
                    ans = (ans + dp[i & 1][j]) % MOD;  //补充存在1的情况
            }
            memset(dp[(i - 1) & 1],0,sizeof(dp[(i - 1) & 1])); //把i-1的划分重置，让数组再利用
        }
        printf("%d\n",ans);
    }
}
