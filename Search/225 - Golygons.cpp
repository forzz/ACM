#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int N = 222;
const char ANS[5] = {"ensw"};
const int d[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
const int O = 105;
int t, n, m, g[N][N], ans[25], vis[N][N], sum[25], ansn;
void init() {  //初始化
    ansn = 0;
    memset(g, 0, sizeof(g));
    memset(vis, 0, sizeof(vis));
    vis[O][O] = 1;  //读入起点被访问
    scanf("%d%d", &n, &m);//走n次 有m个障碍
    int x, y;
    while (m--) {
        scanf("%d%d", &x, &y);
        g[y + O][x + O] = 1;
    }
}
bool judge(int x, int y, int xx, int yy, int k, int i) {//判断函数，k为次数 i为方向
    if (abs(xx - O) + abs(yy - O) > sum[n] - sum[k + 1]) return false;//剪枝，距离原点太远
    if ((vis[xx][yy] || g[xx][yy]) && !(xx == O && yy == O && k + 1 == n)) return false;
    //新节点已被访问或是障碍判断失败（vis为1有可能是已经回到起点，需要把此情况排除）
    int xxx = x, yyy = y;
    while (xxx != xx - d[i][0]) {//该方向存在障碍
        xxx += d[i][0];
        if (g[xxx][y]) return false;
    }
    while (yyy != yy - d[i][1]) {//该方向存在障碍
        yyy += d[i][1];
        if (g[x][yyy]) return false;
    }
    return true;
}

void dfs(int x, int y, int k, int v) { //k代表次数（从0开始） v代表上次移动的方向
    if (g[x][y]) return;
    if (k == n) { //上一次是最后一次 这次dfs为了输出，新的坐标没有读入价值
        if (x == O && y == O) {
            ansn ++; //answer的个数
            for (int j = 0; j < k; j ++) //k个点
                printf("%c", ANS[ans[j]]);  //输出answer，ans数组保存的是方向的数字编号
            printf("\n");
        }
        return;
    }
    for (int i = 0; i < 4; i++) {//4种方向
        if (i == v || i + v == 3) continue;//排除同方向和相反方向
        int xx = x + d[i][0] * (k + 1);//移动后的坐标
        int yy = y + d[i][1] * (k + 1);
        if (!judge(x, y, xx, yy, k, i)) continue;//判断过程复杂，另设函数
        ans[k] = i;
        vis[xx][yy]++;
        dfs(xx, yy, k + 1, i);//第k+1次
        vis[xx][yy]--;//恢复状态
    }
}

void solve() {
    dfs(O, O, 0, -1);
    printf("Found %d golygon(s).\n\n", ansn);
}

void sum_table() {
    sum[0] = 0;
    for (int i = 1; i <= 20; i++)
        sum[i] = sum[i - 1] + i;   //第i次走的单位数
}

int main() {
    sum_table();
    scanf("%d", &t);
    while (t--) {
        init();
        solve();
    }
    return 0;
}
