/*
叉积的结果也是一个向量，是垂直于向量a，b所形成的平面，如果看成三维坐标的话是在 z 轴上，上面结果是它的模。
方向判定：右手定则，（右手半握，大拇指垂直向上，四指右向量a握向b，大拇指的方向就是叉积的方向）
叉积的集合意义：
1：其结果是a和b为相邻边形成平行四边形的面积。
2：结果有正有负，有sin（a，b）可知和其夹角有关，夹角大于180°为负值。
3：叉积不满足交换律
应用：
1：通过结果的正负判断两矢量之间的顺逆时针关系
若 a x b > 0表示a在b的顺时针方向上（有共同的起点C）
若 a x b < 0表示a在b的逆时针方向上（有共同的起点C）
若 a x b == 0表示a在b共线，但不确定方向是否相同（有共同的起点C）
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#define Point Vector
using namespace std;
struct Vector
{
    double x, y;
    Vector(int xx, int yy) :x(xx), y(yy) { }
    Vector() { }
    double operator ^ (const Vector & v) const {
        return x*v.y - v.x*y;
    }
};
Vector operator - (const Point & p1, const Point & p2)
{ //从A点指向B点的矢量AB可用B-A来表示
return Vector(p1.x - p2.x, p1.y - p2.y);
//矢量从 p2指向p1
}
bool operator < (const Point & p1, const Point & p2)
{//如果p1^p2>0，说明p1经逆时针旋转<180度可以到p2，则 p1 < p2
    if ((Vector(p2 - Point(0, 0)) ^ Vector(p1 - Point(0, 0))) > 0)
        return true;
    return false;
}
Point ps[60];
int main()
{
    int x, y;
    int n = 0;
    while (cin >> ps[n].x >> ps[n].y)
        ++n;
    sort(ps + 1, ps + n);
    cout << "(0,0)" << endl;
    for (int i = n - 1; i > 0; --i)
        cout << "(" << ps[i].x << ","<< ps[i].y << ")" << endl;
    return 0;
}
