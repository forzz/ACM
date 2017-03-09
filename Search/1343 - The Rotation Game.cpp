#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 24, LEN = 8;  //24格 8方向
int board[LEN][LEN - 1] = { {0, 2, 6, 11, 15, 20, 22}, {1, 3, 8, 12, 17, 21, 23},
                        {10, 9, 8, 7, 6, 5, 4}, {19, 18, 17, 16, 15, 14, 13},
                        {23, 21, 17, 12, 8, 3, 1}, {22, 20, 15, 11, 6, 2, 0},
                        {13, 14, 15, 16, 17, 18, 19}, {4, 5, 6, 7, 8, 9, 10} };
                        //8个方向（由前到后） 每个方向有7格
int check_order[] = {6, 7, 8, 11, 12, 15, 16, 17}; //检查格
int a[MAXN], maxd;
char order[30];
int unordered() {//估价函数
    int n1 = 0, n2 = 0, n3 = 0;
    for (int i = 0; i < LEN; i++)
        if (a[check_order[i]] == 1)  n1++;
        else if (a[check_order[i]] == 2) n2++;
        else n3++;
    return LEN - max(max(n1, n2), n3);      //返回至少需要移动的格数
}
void rotate(int di) {    //旋转棋盘
    int t = a[board[di][0]];
    for (int i = 1; i < LEN - 1; i++) a[board[di][i - 1]] = a[board[di][i]];
    a[board[di][LEN - 2]] = t;
}
bool dfs(int d) {
    int cnt = unordered();
    if (!cnt) return true;
    if (cnt + d > maxd) return false;//剪枝公式，每一次操作，我们最多可以让中心格子多一个目标数字。
    int temp[MAXN]; memcpy(temp, a, sizeof(a));
    for (int i = 0; i < LEN; i++) {//各个方向遍历
        rotate(i);  //旋转棋盘a
        order[d] = i + 'A'; //记录旋转方向
         if (dfs(d + 1)) return true;
         memcpy(a, temp, sizeof(a));//还原状态
     }
     return false;
 }

int main() {
    while (scanf("%d", &a[0]) && a[0]) {
         for (int i = 1; i < MAXN; i++) scanf("%d", &a[i]);
         if (!unordered()) { printf("No moves needed\n%d\n", a[6]); continue;}
         for (maxd = 1;; maxd++) if (dfs(0)) break;
         for (int i = 0; i < maxd; i++) printf("%c", order[i]);
         printf("\n%d\n", a[6]);
     }
     return 0;
      }
