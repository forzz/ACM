#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e5+5;
int n, arr[maxn], pos[maxn];
bool judge (int l, int r) {
    for (int i = 0; i + l <= r; i++) {
        if (arr[l+i] != pos[r-i])
            return false;
    }
    return true;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        pos[i] = arr[i];        //读入的数据保存在两个数组中
    }
    sort(pos, pos + n);   //pos数组排序
    int l = 0, r = n-1; //翻转左右边界
    while (l < n && pos[l] == arr[l]) l++;
    while (r >= 0 && pos[r] == arr[r]) r--; //确定翻转边界
    if (judge(l, r)) {
        if (r < l)
            l = r = 0;
        printf("yes\n%d %d\n", l+1, r+1);
    } else
        printf("no\n");
    return 0;
}
//reverse()函数可以翻转
