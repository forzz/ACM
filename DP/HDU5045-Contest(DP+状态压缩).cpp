#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1200;
double p[15][MAXN];
double d[MAXN][MAXN];
//dp[i][j]表示前i道题目j个人答题状态的最大值，j用二进制表示，
//因为人最多就10个。因为每两个人之间答题数目不能超过1，所以当状态达到1 << n - 1，即所有人都答过一题时，将重置为0。
int n, m;
void dp() {
    for (int i = 0; i <= m; i++)
        for (int j = 0; j < (1 << n); j++)
            d[i][j] = -1.0;//初始化dp值（i个人做j题的成功率）
    d[0][0] = 0;//边界条件（当i=0时，只有这个状态是有效状态）
    for (int i = 0; i < m; i++) //枚举每道题
        for (int j = 0; j < (1 << n); j++) { //n个人
            if (d[i][j] < 0) continue;//顺序dp，找到有效状态
            int st;
            for (int k = 0; k < n; k++) {//每个人（题是按顺序答的）
                if (!((1 << k) & j)) {//该人没答
                    st = j | (1 << k);   //更新状态
                    if (st == (1 << n) - 1) //m个人全答过1题
                        st = 0;
                    d[i + 1][st] = max(d[i + 1][st], d[i][j] + p[k][i]);
                }
            }
        }
}
int main() {
    int cas, t = 1;
    scanf("%d", &cas);
    while (cas--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%lf", &p[i][j]);
        dp();
        double ans = 0;
        for (int i = 0; i < (1 << n); i++) //遍历所有情况，取最优解
            ans = max(ans, d[m][i]);
        printf("Case #%d: %.5lf\n", t++, ans);
    }
    return 0;
}
