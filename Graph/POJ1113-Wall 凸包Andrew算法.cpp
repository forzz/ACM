//如果要保留凸包边上非顶点（只有右拐时才出栈），则极角序法不适用。
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define eps 1e-8
#define inf 1<<29
const double pi = acos(-1.0);
struct point
{
    int x, y;
}p[1002], conbag[1002];
int det(int x1, int y1, int x2, int y2)//叉积
{
    return x1 * y2 - x2 * y1;
}

int cross(point o, point a, point b)//计算b点在o-a的左侧还是右侧(实质是oa和ob叉积)
{
    return det(a.x - o.x, a.y - o.y, b.x - o.x, b.y - o.y);
    //大于0:a在b右    小于0:a在b左       等于0：a和b共线
}
double f(int x)//将int平方转化为double型
{
    return x * x * 1.0;
}
double dis(point a, point b)//求ab之间的距离
{
    return sqrt( f(a.x - b.x) + f(a.y - b.y) );
}
bool cmp(point a, point b)//水平排序，以x为第一关键字，以y为第二关键字
{
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}
int n, l;
double graham(point p[], int n)
{//在凸包上，但不是顶点的点，没有抛弃，留在stack里面
    if(n < 3) return 0.0;//总点个数小于3不能构成凸包
    int i;
    sort(p, p + n, cmp);//先按坐标排序，
    int top = -1;
    point res[1003];
    for(i = 0; i < n; i++)//正序扫描求下凸壳
//先将前2点压入栈（此时top为1），然后再进行判断
    {
        while(top >= 1 && cross(res[top-1], res[top], p[i]) < 0)
        //如果p[i]在当前直线的右端,那么当前栈顶元素出栈，p[i]进栈（如果p在直线上也进栈）
            top--;
        res[++top] = p[i];//将栈内元素直接保存在res数组
    }
    int t = top + 1;//当前栈内的元素个数，也就是下凸壳的顶点数
    //此时栈顶定是p[n-1]，已经在栈内，第二个需要提前入栈的点是p[n-2]，需要利用t直接放入栈
    for(i = n - 2; i >= 0; i--)//倒序扫描求上凸壳
    {//先将栈顶的元素放入结果中
        while(top >= t && cross(res[top-1], res[top], p[i]) < 0)
//如果p[i]在当前直线的右端,那么当前栈顶元素出栈，p[i]进栈（如果p在直线上也进栈）
            top--;
        res[++top] = p[i];
    }
    res[top] = p[0];//最后再次放入p[0]，构成一个环
    double ans = 0;
    for(i = 0; i < top ; i++)//计算凸包周长
        ans += dis(res[i], res[i+1]);
    return ans;
}
int main()
{
    int i, j;
    while( ~scanf("%d%d", &n, &l) )
    {
        for(i = 0; i < n; i++)
            scanf("%d%d", &p[i].x, &p[i].y);
//结果等于，凸包周长+一个完整的圆周长。因为走一圈，经过拐点时，所形成的扇形的内角和是360度，故一个完整的圆。
        double ans = graham(p, n) + 2 * pi * l;
        printf("%d\n", (int) (ans + 0.5) );//四舍五入
    }
    return 0;
}
