#include<cstdio>
#include<cstring>
#include <algorithm>
#include<cstring>
using namespace std;
bool solve(int *a, int *b, int *c, int n) {
  fill(c, c+n, -1);
  //fill原理是把那一块单元赋成指定的值,memset是按字节填充
  for(int col = 1; col <= n; col++) {  //col为车的坐标(共n个车)  坐标从小到大搜索
    int rook = -1, minb = n+1; //rook为区间 minb为右端点的最小值
    for(int i = 0; i < n; i++)
      if(c[i] < 0 && b[i] < minb && col >= a[i]&&col <= b[i]) { rook = i; minb = b[i]; }
//找一个没有安排过的区间，它的b[i]最小，且车在区间内，因为车是从小到大搜索，这样能让下一个车更容易找到区间
    if(rook < 0 ) return false;//如果没找到区间，则不存在点合格
    c[rook] = col;  //rook区间的点为col
  }
  return true;
}
const int maxn = 5000 + 5;
int n, x1[maxn], y1[maxn], x2[maxn], y2[maxn], x[maxn], y[maxn];
int main() {
  while(scanf("%d", &n) == 1 && n) {
    for (int i = 0; i < n; i++)
      scanf("%d%d%d%d", &x1[i], &y1[i], &x2[i], &y2[i]);
    if(solve(x1, x2, x, n) && solve(y1, y2, y, n))
      for (int i = 0; i < n; i++) printf("%d %d\n", x[i], y[i]);
    else
      printf("IMPOSSIBLE\n");
  }
  return 0;
}
