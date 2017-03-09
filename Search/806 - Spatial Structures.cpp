#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
char p[80][80];
int ans;
vector<int>v;
int get(int r,int c,int w)  //返回黑色节点的个数
{
    int cnt=0;
    for(int i=r;i<r+w;++i)
        for(int j=c;j<c+w;++j)
            if(p[i][j]=='1')
                ++cnt;
    return cnt;
}
int getval(string path)  //路径倒序转十进制
{
    int l=path.size();
    int res=0;
    for(int i=l-1;i>=0;--i)
        res=res*5+path[i]-'0';
    return res;
}
void f1(int r,int c,int w,string path)
{
    int k=get(r,c,w);
    if(k==0)   //全白
        return;
    if(k==w*w)  //全黑
    {
        ++ans;
        v.push_back(getval(path));
        return;
    }
    f1(r,c,w/2,path+'1');
    f1(r,c+w/2,w/2,path+'2');
    f1(r+w/2,c,w/2,path+'3');
    f1(r+w/2,c+w/2,w/2,path+'4');
}
void f2(int r,int c,int w,int s)
{
    if(s==0)//第一层，代表全黑
    {
        for(int i=r;i<r+w;i++)
            for(int j=c;j<c+w;j++)
                p[i][j]='*';
        return;
    }
    int mod=s%5;
    if(mod==1)
        f2(r,c,w/2,s/5);
    else if(mod==2)
        f2(r,c+w/2,w/2,s/5);
    else if(mod==3)
        f2(r+w/2,c,w/2,s/5);
    else if(mod==4)
        f2(r+w/2,c+w/2,w/2,s/5);
}
int main()
{
    int n,cas=0,flag=0;
    while(scanf("%d",&n)&&n)
    {
        v.clear();
        if(flag)
            printf("\n");
        flag=1;
        if(n>0)
/*
图转树用dfs，传的参数是当前已经走的路径（避免全局变量的回溯），
有了边长和起点的横纵坐标就可以很容易的遍历当前的正方形从而判断该点是什么颜色以及是否有子节点
*/
        {
            int i,j;
            for(i=0;i<n;++i)
                scanf("%s",p[i]);
            printf("Image %d\n",++cas);
            ans=0;
            f1(0,0,n,"");
//当前访问的正方形的左上角点的横纵坐标 以及当前正方形边长
            sort(v.begin(),v.end());
            int l=v.size();
            for(i=0;i<l;i++)
                printf("%d%c",v[i],(i%12==11||i==l-1)?'\n':' ');
            printf("Total number of black nodes = %d\n",ans);
        }
        if(n<0)
        {
            n=-n;
            int i,j;
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                    p[i][j]='.';
                p[i][n]=0;      //终止符
            }
            int a;
            while(scanf("%d",&a)&&a!=-1)
            {
                v.push_back(a);
            }
            printf("Image %d\n",++cas);
            int l=v.size();
            for(i=0;i<l;++i)
                f2(0,0,n,v[i]);
            for(i=0;i<n;++i)
                printf("%s\n",p[i]);
        }
    }
}
