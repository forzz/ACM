#include <stdio.h>
#include <math.h>
#define EPS 1e-8
#define MAXN 35
#define INF 0xfffffff
struct Point {
    double x, y;
} p[MAXN<<1];
double cross_pro(Point p0, Point p1, Point p2)
{
    return (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y);
}
int dblcmp(double d) // 三出口判断正负浮点数函数
{
    if (fabs(d) < EPS)
        return 0; // 三点共线
    return (d > 0) ? 1 : -1;
}
bool is_intersect(Point p1, Point p2, Point p3, Point p4) // 判断严格相交（实际值已经用dblcmp替换为1或-1）
{
    return dblcmp(cross_pro(p3, p4, p1)) * dblcmp(cross_pro(p3, p4, p2)) == -1;
 // 判断起点终点是否在wall的两侧，如果在同侧不需要穿墙。
}
int compute(Point dest, int cnt)
{
    int i, j, res, min=INF;
    for (i = 0; i < cnt; ++i)//枚举每个顶点和宝藏组成的线段，记录其与所有墙的交点个数
    {
        res = 0;
        for (j = 0; j < cnt; j += 2)//枚举每道墙
            if (is_intersect(dest, p[i], p[j], p[j+1]))
                ++res;
        if (min > res)
            min = res;
    }
    return min;
}
int main()
{
    int i, n, cnt=0;
    double x1, y1, x2, y2;
    Point dest;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)//读入每个墙，cnt记录所有的顶点数（相邻2个顶点组成1条边）
    {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        p[cnt].x = x1;
        p[cnt++].y = y1;
        p[cnt].x = x2;
        p[cnt++].y = y2;
    }
    scanf("%lf%lf", &dest.x, &dest.y); //宝藏的位置
    if (n == 0)
        printf("Number of doors = 1\n");
    else
        printf("Number of doors = %d\n", compute(dest, cnt)+1);//最后得出的数字加1即为结果(因为还有边界墙)
    return 0;
}
