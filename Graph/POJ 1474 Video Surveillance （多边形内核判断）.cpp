//我们都知道一条直线可以将平面切割成两个区域，假设直线方程为
//ax+by+c==0，那么，两个平面可分别表示成ax+by+c>=0 和 ax+by+c<0
#include<iostream>
#include <stdio.h>
#include <math.h>
#define eps 1e-8
using namespace std;
const int MAXN=210;
int m;
double r;
int cCnt,curCnt;//此时cCnt为最终切割得到的多边形的顶点数、暂存顶点个数
struct point
{
    double x,y;
};
point points[MAXN],p[MAXN],q[MAXN];//读入的多边形的顶点（顺时针）、p为存放最终切割得到的多边形顶点的数组、暂存核的顶点
void getline(point x,point y,double &a,double &b,double   &c) //两点x、y确定一条直线a、b、c为其系数
{
    a = y.y - x.y;
    b = x.x - y.x;
    c = y.x * x.y - x.x * y.y;
}
void initial()
{
    for(int i = 1; i <= m; ++i)p[i] = points[i];
    p[m+1] = p[1];
    p[0] = p[m];
    cCnt = m;//cCnt为最终切割得到的多边形的顶点数，将其初始化为多边形的顶点的个数
}
point intersect(point x,point y,double a,double b,double c) //求x、y形成的直线与已知直线（由a、b、c确定）的交点
{
    double u = fabs(a * x.x + b * x.y + c);
    double v = fabs(a * y.x + b * y.y + c);
    point pt;
    pt.x=(x.x * v + y.x * u) / (u + v);
    pt.y=(x.y * v + y.y * u) / (u + v);
    return  pt;
}
/*
对凸多边形（指的是当前多边形）的每一个顶点，如果这个顶点在直线的指定的一侧（暨在该半平面上），
那么就将该顶点直接加入到新的多边形中，否则，看与该点相邻的多边形上的两个点（判断线段是否和直线相交），
如果和直线相交，则把交点加入到新的多边形中。这样，就可以得到一个新的凸多边形。
*/
void cut(double a,double b ,double c)
{
    curCnt = 0;
    for(int i = 1; i <= cCnt; ++i)//枚举每个点
    {
        if(a*p[i].x + b*p[i].y + c >= 0)q[++curCnt] = p[i];
        // c由于精度问题，可能会偏小，所以有些点本应在右侧而没在，故应该接着判断
        else
        {
            if(a*p[i-1].x + b*p[i-1].y + c > 0) //如果p[i-1]在直线的右侧的话，
            {
//则将p[i],p[i-1]形成的直线与已知直线的交点作为核的一个顶点(这样的话，由于精度的问题，核的面积可能会有所减少)
                q[++curCnt] = intersect(p[i],p[i-1],a,b,c);
            }
            if(a*p[i+1].x + b*p[i+1].y + c > 0) //原理同上
            {
                q[++curCnt] = intersect(p[i],p[i+1],a,b,c);
            }
        }
    }
    for(int i = 1; i <= curCnt; ++i)p[i] = q[i];//将q中暂存的核的顶点转移到p中
    p[curCnt+1] = q[1];//连成环
    p[0] = p[curCnt];
    cCnt = curCnt;//更新顶点数
}
int dcmp(double x)
{
    if(fabs(x)<eps) return 0;
    else return x<0?-1:1;
}
void solve()
{
    //注意：默认点是顺时针，如果题目不是顺时针，规整化方向
    initial();
    for(int i = 1; i <= m; ++i)
    {
        double a,b,c;
        getline(points[i],points[i+1],a,b,c);//求出每一条相邻点的连线
        cut(a,b,c);//用该连线进行切割
    }
    /*
      如果要向内推进r，用该部分代替上个函数
      for(int i = 1; i <= m; ++i){
          Point ta, tb, tt;
          tt.x = points[i+1].y - points[i].y;
          tt.y = points[i].x - points[i+1].x;
          double k = r / sqrt(tt.x * tt.x + tt.y * tt.y);
          tt.x = tt.x * k;
          tt.y = tt.y * k;
          ta.x = points[i].x + tt.x;
          ta.y = points[i].y + tt.y;
          tb.x = points[i+1].x + tt.x;
          tb.y = points[i+1].y + tt.y;
          double a,b,c;
          getline(ta,tb,a,b,c);
          cut(a,b,c);
      }*/
    //多边形核的面积
    double area = 0;
    for(int i = 1; i <= curCnt; ++i)
        area += p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
    area = fabs(area / 2.0);
    if(!curCnt&&dcmp(area)==0)
    puts("Surveillance is impossible.");
    else
    puts("Surveillance is possible.");

}
/*void GuiZhengHua(){
     //规整化方向，逆时针变顺时针，顺时针变逆时针
    for(int i = 1; i < (m+1)/2; i ++)
      swap(points[i], points[m-i]);
}*/
int main()
{
    int kk = 0;
    while(scanf("%d",&m)&&m)
    {
        int i;
        for(i=1; i<=m; i++)
            cin>>points[i].x>>points[i].y;
        points[m+1]=points[1];//构成一个环
        printf("Floor #%d\n",++kk);
        solve();
        puts("");
    }
}
