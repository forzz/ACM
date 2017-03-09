#include <iostream>
#include <cmath>
using namespace std;
const int maxn = 1e5;
int arr[maxn], block[400][10][10];
void clear() {//初始化数组
    fill(arr, arr + maxn, 0);
    //头文件为<iostream>,与memset的不同不仅在于函数参数的顺序，而且对int型的数组赋值，fil_n可以赋任何值，而memset只能赋0或-1.
    for (int a = 0; a < 400; ++a) {//n^(1/2)
        for (int b = 0; b < 10; ++b) {//最多为十位
            fill(block[a][b], block[a][b] + 10, 0);//分成a块，每块有10位，每位记录满足的数字个数
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        clear();
        int N, M;
        cin >> N >> M;
        int size = sqrt(N);//每块的大小
        for (int a = 0; a < N; ++a) {
            cin >> arr[a];//读入每个数，预处理相关数据
            for (int b = 0, t = arr[a]; b < 10; ++b, t /= 10) {
                block[a / size][b][t % 10] += 1;
            }
        }
        while (M--) {
            char op;
            cin >> op;
            if (op == 'S') {//赋值
                int x, y;
                cin >> x >> y;
                x -= 1;
                for (int a = 0, t = arr[x]; a < 10; ++a, t /= 10) {//先把原来的数据删除掉
                    block[x / size][a][t % 10] -= 1;
                }
                for (int a = 0, t = y; a < 10; ++a, t /= 10) {//增加新的数据
                    block[x / size][a][t % 10] += 1;
                }
                arr[x] = y;//赋值
            }
            else {//查询
                int l, r, d, p;
                cin >> l >> r >> d >> p;
                l -= 1, r -= 1, d -= 1;//从0开始存储数
                int res = 0;
                if (l / size == r / size) {//所求区间在同一块内，逐个检查
                    for (int a = l; a <= r; ++a) {//遍历区间内的所有元素
                        for (int b = 0, t = arr[a]; b <= d; ++b, t /= 10) {//拆出每一位并记录位数b（第一位为0位）
                            if (b == d && t % 10 == p) res += 1;//符合条件
                        }
                    }
                    cout << res << endl;
                    continue;
                }
                //所求区间在不同块，分为三部分：左端点所在块  右端点所在块 两端点之间包含的块
                for (int a = l; a < (l / size + 1) * size; ++a) {//左端点所在块，逐个检查（第一块是0到size-1 size是第二块的元素）
                    for (int b = 0, t = arr[a]; b <= d; ++b, t /= 10) {
                        if (b == d && t % 10 == p) res += 1;
                    }
                }
                for (int a = l / size + 1; a < r / size; ++a) {//两端点之间包含的块（a为l的下一块 r/size是r所在的块号）
                    res += block[a][d][p];//直接利用预处理结果
                }
                for (int a = r / size * size; a <= r; ++a) {// r/size*size 右端点所在的块的首元素
                    for (int b = 0, t = arr[a]; b <= d; ++b, t /= 10) {
                        if (b == d && t % 10 == p) res += 1;
                    }
                }
                cout << res << endl;
            }
        }
    }
    return 0;
}
