#include<iostream>
#include<algorithm>
#include<cstdio>
#include<memory.h>
#include<cmath>
using namespace std;
const int maxn=2002;
const int maxm=2002;
const int inf=1<<29;//int类型最大值是2^30
int q[maxn];
int t,cas,maxp,w,ap[maxn],bp[maxn],as[maxn],bs[maxn];
int dp[maxn][maxm];
int main()
{
    scanf("%d",&cas);
    while(cas--)
    {
        int i,j;
        scanf("%d%d%d",&t,&maxp,&w);//t天 股票数量上限maxp 间隔时间w
        for(i=1; i<=t; i++)//
        {
            scanf("%d%d%d%d",&ap[i],&bp[i],&as[i],&bs[i]);//每天股票 买价格ap 卖价格bp 买上限as  卖上限bs
        }
        for(i=0; i<=t; i++)//初始化dp值全为负无穷（没有dp到全为负）
        {
            for(j=0; j<=maxp; j++)
            {
                dp[i][j]=-inf;//i天持有j张股票时获得的利润（只有天数和持股数影响下一天的状态）
            }
        }
        dp[0][0]=0;
        for (i=1; i<=w+1; i++)//再特别初始化dp值，在前w+1天时(天数从1开始)，只能进行买或者不动这种状态，这里是前w+1天只能买
        {
            for (j=0; j<=min(as[i],maxp); j++) dp[i][j]=-ap[i]*j;
        }
        for(i=1; i<=t; i++)//进行dp    先枚举天数
        {
            for(j=0; j<=maxp; j++) //不买不卖   dp值为前一天的dp值
            {
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
            }
            if(i<=w+1) continue;//第一天到W+1天只都是只能买，不能卖,一次交易后至少要间隔w天才能再次交易
            int pre=i-w-1;//w天前,今天的交易状态是以w天前的状态决定的
            //买        dp[i][j]=max(dp[i][j],dp[pre][k]-(j-k)*ap[i]);  从w天前持股票推现在最大利润
                //dp[i][j]+j*ap[i]=dp[pre][k]+k*ap[i]。右边与j无关， 可见我们只需要对每一个 i 维护一个关于k的单调队列
            int front = 1;
            int tail = 0;
            for (j = 0; j <= maxp; ++j)//枚举持股量j，枚举完一个j，就把j放入k（因为是买入，j肯定比k大）
            {//用单调队列优化dp[i-w-1][k]+ap[i]*k     找到其最大值时的持股量k
                while (tail >= front && j-q[front]> as[i]) front++;//单调队列维护长度不能超过as（要买的票数必须比上限小，维护队首）
                while (tail >= front && (dp[pre][j]+ap[i]*j) > (dp[pre][q[tail]]+ap[i]*q[tail])) tail--;//保证队列单调递减（队首为最大值）
                q[++tail] = j;//把当前j放入单调队列供下次求k（所以上一步才让队列的值和j比较，）
                if (tail >= front) dp[i][j] = max(dp[i][j],dp[pre][q[front]] - ap[i]*(j - q[front]));//维护dp值
            }
            //卖     dp[i][j]=max(dp[i][j],dp[i-w-1][k]+(k-j)*bp[i]);
            front = 1;
            tail = 0;
            for (j = maxp; j >= 0; --j)
            {
                while (tail >= front && q[front] - bs[i] > j) front++;
                while (tail >= front && dp[pre][q[tail]] + bp[i]*q[tail] < (dp[pre][j]+bp[i]*j)) tail--;
                q[++tail] = j;//j放入队列
                if (tail >= front) dp[i][j] = max(dp[i][j],dp[pre][q[front]] + bp[i]*(q[front] - j));
            }
        }
        int ans=0;
        for(i=0; i<=maxp; i++)
        {
            ans=max(ans,dp[t][i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}

