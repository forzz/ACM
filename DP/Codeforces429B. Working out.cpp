#include <bits/stdc++.h>
using namespace std;
#define N 1100
#define LL long long
int a[N][N];
LL dp[N][N][4];
int main(){
    int n, m;
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= m;j++)
                scanf("%d", &a[i][j]);
        memset(dp, 0, sizeof(dp));
        for(int i = 1;i <= n;i++)    //左上
            for(int j = 1;j <= m;j++)
                dp[i][j][0] = max(dp[i-1][j][0], dp[i][j-1][0]) + a[i][j];
        for(int i = 1;i <= n;i++)    //右上
            for(int j = m;j > 0;j--)
                dp[i][j][1] = max(dp[i-1][j][1], dp[i][j+1][1]) + a[i][j];
        for(int i = n;i > 0;i--)     //左下
            for(int j = m;j > 0;j--)
                dp[i][j][2] = max(dp[i+1][j][2], dp[i][j+1][2]) + a[i][j];
        for(int i = n;i > 0;i--)     //右下
            for(int j = 1;j <= m;j++)
                dp[i][j][3] = max(dp[i+1][j][3], dp[i][j-1][3]) + a[i][j];
        LL ans = 0;
        for(int i = 2;i < n;i++)
            for(int j = 2;j < m;j++){
//交叉点周围有4个方格，2人各分左右和上下
                ans = max(ans, dp[i][j-1][0] + dp[i-1][j][1] + dp[i][j+1][2] + dp[i+1][j][3]);
                //1号占左右
                ans = max(ans, dp[i][j-1][3] + dp[i-1][j][0] + dp[i][j+1][1] + dp[i+1][j][2]);
                //1号占上下
            }
        printf("%I64d\n", ans);
    }
    return 0;
}
