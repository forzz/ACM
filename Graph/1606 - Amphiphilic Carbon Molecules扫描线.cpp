#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1000 + 5;
struct Point {
  int x, y;
  double rad; //极角
  bool operator<(const Point &rhs) const {
    return rad < rhs.rad;//按极角大小排序
  }
}op[maxn], p[maxn];
int n, color[maxn];
// from O-A to O-B, is it a left turn?
bool Left(Point A, Point B) {
  return A.x * B.y - A.y * B.x >= 0;
}

int solve() {
  if(n <= 2) return 2;
  int ans = 0;

  // pivot point
  for(int i = 0; i < n; i++) {     //枚举基准点op[i]
    int k = 0;

    // the list of other point, sorted in increasing order of rad
    for(int j = 0; j < n; j++)
      if(j != i) {
        p[k].x = op[j].x - op[i].x;//将其他点都转换为相对坐标
        p[k].y = op[j].y - op[i].y;
        if(color[j]) { p[k].x = -p[k].x; p[k].y = -p[k].y; }//如果是黑点，将它绕原点旋转180度即可看做白点处理了
        p[k].rad = atan2(p[k].y, p[k].x);
        k++;
      }
    sort(p, p+k);

    // sweeping. cnt is the number of points whose rad is between p[L] and p[R]
    int L = 0, R = 0, cnt = 2;
    while(L < k) {//O-p[L]作为分隔线，O-p[R]作为扫描线，注意，R一直是在0~k-1之间不停地循环着，直到L>=k才停止
      if(R == L) { R = (R+1)%k; cnt++; }  //空区域，暂时多计入一个点，最后舍去
      while(R != L && Left(p[L], p[R])) { R = (R+1)%k; cnt++; }
      //扫描线一直逆时针旋转，直到旋转角度刚刚>180度停止统计
      cnt--;//舍去多计入的点，也可以理解为由于分隔线的旋转，原来在分隔线上的点现在变为了右侧的点，要减掉一个
      L++; //分隔线旋转
      ans = max(ans, cnt);//统计这一轮扫描的结果
    }
  }
  return ans;
}

int main() {
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++)
      scanf("%d%d%d", &op[i].x, &op[i].y, &color[i]);
    printf("%d\n", solve());
  }
  return 0;
}
