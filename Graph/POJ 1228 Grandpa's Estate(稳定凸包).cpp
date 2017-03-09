#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const double EPS = 1e-6;
struct point{
    double x , y;
} p[1010] , chn[1010];
bool cmp (point a , point b)//水平排序，以x为第一关键字，以y为第二关键字
{
     return (a.y < b.y || (a.y == b.y && a.x < b.x));
}
double xmult(point p1 , point p2 , point p3)//计算b点在o-a的左侧还是右侧(实质是oa和ob叉积)
{
     return ((p1.x - p3.x) * (p2.y - p3.y) - (p1.y - p3.y) * (p2.x - p3.x));
}
int andrew(int n)
{
    int len , top = 1;
    //先将前2点压入栈（此时top为1），然后再进行判断（从第三个点开始）
    chn[0] = p[0];
    chn[1] = p[1];
    for (int i = 2 ; i < n ; i ++)
    {
        while (top && xmult(p[i] , chn[top] , chn[top - 1]) > EPS) top --;
        chn[++ top] = p[i];
    }
    len = top;
    chn[++ top] = p[n - 2];//此时栈顶定是p[n-1]，已经在栈内，第二个需要提前入栈的点是p[n-2]，需要利用t直接放入栈
    for (int i = n - 3 ; i >= 0 ; i --)
    {
        while (top != len && xmult(p[i] , chn[top] , chn[top - 1]) > EPS) top --;
        chn[++ top] = p[i];
    }
    return top;
}
bool judge(int n)
//用Andrew算法求出凸包后（栈内不删去共线的点）这些点已经是按一定顺序排好
//然后之需要对栈内的点进行叉积判断就可以了
//返回false的情况就是i-1，i，i+1，i+2形成了三条折线，这样i和i+1之间就没有点了，就不满足退出
{
     for (int i = 1 ; i < n ; i ++)
     {
         if ((xmult(chn[i - 1] , chn[i] , chn[i + 1]) != 0) && (xmult(chn[i] , chn[i + 1] , chn[i + 2]) != 0))
           return false;
     }
     return true;
}
int main()
{
    int T , n;
    scanf("%d" , &T);
    while (T --)
    {
          scanf("%d" , &n);
          for (int i = 0 ; i < n ; i ++) scanf("%lf%lf" , &p[i].x , &p[i].y);
          if (n < 6) printf("NO\n");//小于6，不可能构成稳定凸包
          else
          {
              sort(p , p + n , cmp);//先按坐标排序
              int top = andrew(n);
              if (judge(top)) printf("YES\n");
              else printf("NO\n");
          }
    }
    return 0;
}
