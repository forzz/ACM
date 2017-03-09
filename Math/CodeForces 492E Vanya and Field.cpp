#include<cstdio>
#include<algorithm>
#include<string.h>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn = 1e6 + 5;
int n, m, dx, dy, x[maxn], cnt[maxn];
int main() {
/*
首先最重要的条件就是gcd(n,dx)=gcd(n,dy)=1;由这可知x方向上的位移与n互质,于是当沿着dx方向走n次恰好回到起点(最小公倍数),并且走过的n个点互不重合
现在假设(0,0)为起点,那么第一步后就到达了(dx%n,dy%n),第k步后到达了(k*dx%n,k*dy%n),对于每一步我们可以储存他到达
的位置,发现因为x,y都是互异的,因此只需要x[k*dx%n]=k*dy%n;这样关联,就能表示一个点的坐标(k*dx%n,k*dy%n)
*/
    while(~scanf("%d%d%d%d", &n, &m, &dx, &dy)) {
        memset(cnt, 0, sizeof(cnt));
        memset(x, 0, sizeof(x));
        int x1 = 0, y1 = 0;
        for(int i = 1; i <= n; i++) {//打表（一共就n种可能）  以0为起点
            x1 = (x1 + dx) % n; y1 = (y1 + dy) % n;
            x[x1] = y1;
        }
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x1, &y1);
            int y0 = (y1 - x[x1] + n) % n;//以0为起点要走的距离
            cnt[y0]++;
        }
        int index = 0;
        for(int i = 1; i < n; i++) {
            if(cnt[i] > cnt[index])index = i;
        }
        printf("0 %d\n", index);
    }
    return 0;
}
