#include <cstdio>
const int N=100005;
int p[N],q[N];
int main()
{
    int T,n,s1,s2,s,ans;
    scanf("%d",&T);
    while(int ca=1,T--)
    {
        scanf("%d",&n);
        s1=s2=0;
        for (int i=1;i<=n;i++) scanf("%d",&p[i]),s1+=p[i];
        for (int i=1;i<=n;i++) scanf("%d",&q[i]),s2+=q[i];
        printf("Case %d: ",ca++);
        if (s1<s2)//总加油量小于总耗油量，不可能完成
        {
            puts("Not possible");
            continue;
        }
        ans=1;s=0;
        for (int i=1;i<=n;i++)//起点从1开始，不需要做一个圈，因为如果从i开始，就证明1到i-1是可以到的
        {
            s+=p[i];
            s-=q[i];  //维护现在点到下一站时的汽油量
            if (s<0)//不能到下一点
            {
                s=0;//清空汽油量，以i为起点
                ans=i+1; //更新答案
            }
        }
        printf("Possible from station %d\n",ans);
    }
}
