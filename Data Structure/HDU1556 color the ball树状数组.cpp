#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[110000];
int lowbit(int x)//找x二进制下为1的最低位
{
    return x&(-x);
}
void add(int x,int t)//建树(包含该数的所有a数组都加t，等到求sum的时候，就相当于该区间整体+t)
{
    for(int i=x;i<=n;i+=lowbit(i))
    {
        a[i]+=t;
    }
}
int query(int x)//求解
{
    int sum=0;
    for(int i=x;i>0;i-=lowbit(i))//i等于0死循环
    {
        sum+=a[i];
    }
    return sum;
}
int main()
{
    while(scanf("%d",&n)!=EOF&&n)
    {
        int x,y;
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            add(x,1);
            add(y+1,-1);//关键所在
        }
        for(int i=1;i<n;i++)
            printf("%d ",query(i));
        printf("%d\n",query(n));
    }
    return 0;
}
