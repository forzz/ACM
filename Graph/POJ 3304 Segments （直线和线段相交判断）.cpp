#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
using namespace std;
const double eps = 1e-8;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0) return -1;
    return 1;
}
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};
struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e)
    {
        s = _s;e = _e;
    }
};
double xmult(Point p0,Point p1,Point p2) //p0p1 X p0p2
{
    return (p1-p0)^(p2-p0);
}
bool Seg_inter_line(Line l1,Line l2) //判断直线l1和线段l2是否相交,如果线段P1P2和直线Q1Q2相交，则P1P2跨立Q1Q2
/*
若P1P2跨立Q1Q2 ，则矢量 ( P1 - Q1 ) 和( P2 - Q1 )位于矢量( Q2 - Q1 ) 的两侧，
即( P1 - Q1 ) × ( Q2 - Q1 ) * ( P2 - Q1 ) × ( Q2 - Q1 ) < 0。
当 ( P1 - Q1 ) × ( Q2 - Q1 ) = 0 时，说明 ( P1 - Q1 ) 和 ( Q2 - Q1 )共线，
上式可改写成
( P1 - Q1 ) × ( Q2 - Q1 ) * ( Q2 - Q1 ) × ( P2 - Q1 ) > 0
( P1 - Q1 ) × (Q2 - Q1) = 0 说明 P1 一定在线段 Q1Q2上
( Q2 - Q1 ) ×(P2 - Q1 ) = 0 说明 P2 一定在线段 Q1Q2上。
所以判断P1P2跨立Q1Q2的依据是：
( P1 - Q1 ) × ( Q2 - Q1 ) * ( Q2 - Q1 ) × ( P2 - Q1 ) ≥ 0
或者
( Q1 - P1 ) × ( P2 - P1 ) * ( P2 - P1 ) × ( Q2 - P1 ) ≥ 0
*/

{
    return sgn(xmult(l2.s,l1.s,l1.e))*sgn(xmult(l2.e,l1.s,l1.e)) <= 0;
}
double dist(Point a,Point b)//求向量ab的模长
{
    return sqrt( (b - a)*(b - a) );
}
const int MAXN = 110;
Line line[MAXN];
bool check(Line l1,int n)//判断该线是否和所有线段相交
{
    if(sgn(dist(l1.s,l1.e)) == 0 )return false;//s和e重合
    for(int i = 0;i < n;i++)//判断与所有线段是否相交
        if(Seg_inter_line(l1,line[i]) == false)
            return false;
    return true;
}
int main()
{
    int n;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        double x1,y1,x2,y2;
        for(int i = 0; i < n;i++)//将每对点变成边保存起来
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            line[i] = Line(Point(x1,y1),Point(x2,y2));
        }
        bool flag = false;
        for(int i = 0;i < n;i++)//枚举每2个不同线上的端点，组成一条新的线
            for(int j = 0; j < n;j++)
                if(check(Line(line[i].s,line[j].s),n) || check(Line(line[i].s,line[j].e),n)
                        || check(Line(line[i].e,line[j].s),n) || check(Line(line[i].e,line[j].e),n) )
                {
                    flag = true;
                    break;
                }
        if(flag)
            printf("Yes!\n");
        else printf("No!\n");
    }
    return 0;
}
/*
给定一些线段，问是否有直线L存在，使得所有线段到L的投影有至少一个公共点.
实际上就是问，是否存在一条直线K, 和所有这些线段都相交。 L是K的垂线即可。
若存在一条直线与所有线段相交，该直线必定经过这些线段的某两个端点
(否则可以平移或转动使之靠上端点,此时由于头尾节点对称，不会改变相交关系）。
枚举任意两个端点构造直线并看它是否与每条线段相交即可。
*/
