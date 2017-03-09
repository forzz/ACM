#include <stdio.h>
#include <string.h>
#define MAX 10010
#define INF 1000000000
#define MIN(a,b) (a)<(b)?(a):(b)
int n,m,tot,dp[MAX][20]; //dp记录位置和能量槽
int A[MAX],B[MAX];
int main()
{
    int i,j,k,t,add,next;
    while (scanf("%d%d",&n,&m) != EOF) {
        memset(dp,0x3f,sizeof(dp));
        tot = n * m;  //总路程
        for (i = 0; i < n; ++i)
            scanf("%d",&A[i]);  //未加速耗时
        for (j = 0; j < n; ++j)
            scanf("%d",&B[j]);  //加速后耗时
        for (i = 0; i < tot; ++i)
            A[i] = A[i%n],B[i] = B[i%n];//路补完
        dp[1][1] = A[0];  //边界值（dp从1开始）
        for (i = 1; i < tot; ++i)
            for (j = 0; j < 15; ++j) {
                k = j + 1;
                if (k == 15) k = 10;
                dp[i+1][k] = MIN(dp[i][j]+A[i],dp[i+1][k]); //不用加速器
                if (j >= 5) dp[i+1][j-5] = MIN(dp[i][j]+B[i],dp[i+1][j-5]);
            }
        int ans = INF;
        for (i = 0; i < 15; ++i)//遍历终点所有情况，找出最小值
            ans = MIN(ans,dp[tot][i]);
        printf("%d\n",ans);
    }
}
