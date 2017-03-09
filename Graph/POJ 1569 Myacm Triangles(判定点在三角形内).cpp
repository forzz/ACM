#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double eps=1e-10;
int dcmp(double x)//判断与0的关系
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}
const int maxn=15+5;
struct Point
{
    double x,y;
    Point(){}
    Point(double x,double y):x(x),y(y){}
}P[maxn];
typedef Point Vector;
Vector operator-(Point A,Point B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
double Cross(Vector A,Vector B)//叉积判断线段相交
{
    return A.x*B.y-A.y*B.x;
}
double Area(Point A,Point B,Point C)//两个矢量所围成的三角形的面积等于叉积的一半
{
    return fabs(Cross(B-A,B-C))/2;
}
bool InTriangle(Point P,Point A,Point B,Point C)//判断点P是否在三角形ABC的内部(包括边上)
//如果一个点P在三角形ABC内部(或边上),那么三角形PAB+三角形PBC+三角形PAC的面积 == ABC的面积. 否则前者面积和应该更大.
{
    double a1=Area(P,A,B),a2=Area(P,A,C),a3=Area(P,B,C),b=Area(A,B,C);
    return dcmp(a1+a2+a3-b)==0;
}
bool check(int i,int j,int k,int n)//判断第i,j,k个点是否能构成一个内部无点的三角形
{
    if( dcmp(Cross(P[i]-P[j],P[i]-P[k]))==0 ) return false;//三点共线
    for(int it=0;it<n;++it)//枚举可能在三角形内部的点
        if(it!=i && it!=j && it!=k)//排除三角形三个顶点
                if(InTriangle(P[it],P[i],P[j],P[k])) return false;
    return true;
}
int main()
{
    int n;
    while(scanf("%d",&n)==1 && n)
    {
        for(int i=0;i<n;++i)
        {
            char c;
            scanf(" %c %lf %lf",&c,&P[i].x,&P[i].y);
        }
//由于点数<=15,所以我们直接暴力枚举每个可能的三角形(枚举的三点首先要不共线),
//然后判断该三角形是否包含点. 如果不含点,那么就计算它的面积即可.
        double ans=0; //最大三角形面积
        int num[3];//保存最大三角形的三个点编号
        for(int i=0;i<n;++i)
        for(int j=i+1;j<n;++j)
        for(int k=j+1;k<n;++k)
        if(check(i,j,k,n))//判断三角形内部是否存在点
        {
            double area=Area(P[i],P[j],P[k]);
            if(ans<area)
            {
                ans=area;
                num[0]=i,num[1]=j,num[2]=k;
            }
        }
        printf("%c%c%c\n",num[0]+'A',num[1]+'A',num[2]+'A');
    }
    return 0;
}
