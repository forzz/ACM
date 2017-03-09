#include <iostream>
#include <cstdio>
#include <cmath>
#include<algorithm>
using namespace std;
struct Point {
   double x, y;
} up[22], down[22];//点定义
const double eps = 1e-3;//精度
double Multi(Point p1, Point p2, Point p0) {//计算P0点在p1-p2的左侧还是右侧(实质是叉积)
   return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
bool Across(Point a, Point b, Point c, Point d) {//此处是判断直线ab与线段cd是否相交，cd的端点在ab上也算相交
    double tmp = Multi(c, b, a) * Multi(d, b, a);
    if (tmp < 0 || fabs(tmp) < eps) return true;
    return false;
}
double getIntersect(Point a, Point b, Point c, Point d) {//计算ab和cd的交点
    double A1 = b.y - a.y;
    double B1 = a.x - b.x;
    double C1 = (b.x - a.x) * a.y - (b.y - a.y) * a.x;
    double A2 = d.y - c.y;
    double B2 = c.x - d.x;
    double C2 = (d.x - c.x) * c.y - (d.y - c.y) * c.x;
    double x = (C2 * B1 - C1 * B2) / (A1 * B2 - A2 * B1);
    //y = (C1 * A2 - C2 * A1) / (A1 * B2 - A2 * B1); //交点纵坐标
    return x;
 }

int main() {
    int n, i, j, k;
    double best;
    bool flag;

    while (scanf ("%d", &n) && n) {
         for (i = 0; i < n; i++) {
            scanf ("%lf%lf", &up[i].x, &up[i].y);
            down[i].x = up[i].x;
            down[i].y = up[i].y - 1;
         }
         best = up[0].x;//最大可见度(管中最远可见点的横坐标)
         flag = false;
//一条光线从入口到某一点必然会擦过一个上点（管转弯口上壁的点）和一个下点（管转弯口下壁的点）。
//如果一条光线自始至终未擦到任何定点，这条光线是可以“优化的”。
//“优化”就是可以通过旋转使它擦过一个上点和一个下点。
         for (i = 0; i < n && !flag; i++) {//枚举所有通过一个上折点、一个下折点的直线
            for (j = 0; j < n && !flag; j++) {
                if (i != j) {
                   for (k = 0; k < n; k++)//判断该光线能通过多少折线（和某对上下管壁组成的线段相交证明通过）
                      if (!Across(up[i], down[j], up[k], down[k])) break;
                   if (k == n) flag = true;//完全通过
                   else if (k > max(i, j)) {//中途撞到管壁
//计算入口到相交管壁的距离，有可能是上管壁，也有可能是下管壁，保存最大值。
                      double tmp;
                      tmp = getIntersect(up[i], down[j], up[k-1], up[k]);
                      if (tmp > best) best = tmp;
                      tmp = getIntersect(up[i], down[j], down[k-1], down[k]);
                      if (tmp > best) best = tmp;
                   }
                }
            }
         }
         if (flag) printf ("Through all the pipe.\n");
         else printf ("%.2lf\n", best);
    }
}
