#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
#define maxn 111111
int n,m,pf[maxn];
struct node
{
    int l,r,num,op,id;
    //op表示是曲子还是演奏家
    //如果op=1说明是演奏家,l,r,num就表示其ci,di和ki,id表示其编号
    //如果op=0说明是曲子,l,r就表示其ai,bi,id表示其编号
}a[2*maxn];
struct edge //
{
    int l,id;
    bool operator<(const edge&e)const  //先排左端点，再排序号
    {
        if(e.l!=l) return e.l>l;
        return e.id>id;
    }
    edge(int a=0,int b=0):id(a),l(b){}
}del;
set<edge>s;
set<edge>::iterator p;
bool cmp(node x,node y) //先排右端点，再排歌曲和歌手，再排左端点（降维）
{
    if(x.r!=y.r)return x.r<y.r;
    if(x.op!=y.op)return x.op<y.op;
    return x.l<y.l;
}
int main()
{
    while(~scanf("%d",&n))
    {
        memset(pf,0,sizeof(pf));//第i首曲子是由第pf[i]个演奏家演奏的
        s.clear();
        for(int i=1;i<=n;i++)    //歌曲初始化
        {
            scanf("%d%d",&a[i].l,&a[i].r);
            a[i].op=0;a[i].id=i;
        }
        scanf("%d",&m);
        for(int i=1;i<=m;i++)  //歌手初始化（保存在同一结构体中）
        {
            scanf("%d%d%d",&a[i+n].l,&a[i+n].r,&a[i+n].num);
            a[i+n].op=1;a[i+n].id=i;
        }
        sort(a+1,a+n+m+1,cmp);//将这n+m个时间段按结束点排序,那么靠前的一定是结束时间早
        int ans=0;//ans记录能够被演奏的曲子数目
        for(int i=1;i<=n+m;i++)
            if(a[i].op)  //如果这个时间段是演奏家的演奏阶段，那么s中存放的曲子结束时间显然都小于等于其结束时间
            {
                while(s.size()&&a[i].num--)  //当前演奏家可演奏数减1
                {
                    p=s.lower_bound(edge(0,a[i].l));//贪心找到开始时间大于等于a[i].l的曲子中开始时间最小的
                    if(p==s.end())break; //没找到，无可谈曲子
                    del=*p;
                    s.erase(p);//删掉这首曲子
                    pf[del.id]=a[i].id;//记录这首曲子的演奏者
                    ans++;//被演奏完成的曲子数量加一
                }
            }
            else
                s.insert(edge(a[i].id,a[i].l));//如果是曲子的时间段，直接放入s中
        if(ans==n)//所有曲子均被演奏完成则说明存在合法方案
        {
            printf("YES\n");
            for(int i=1;i<=n;i++)
                printf("%d%c",pf[i],i==n?'\n':' ');
        }
        else printf("NO\n");
    }
    return 0;
}
