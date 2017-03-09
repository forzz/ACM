#include<algorithm>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<math.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=100010;
typedef long long ll;
struct qnode
{
    int l,r,idx;
} qu[maxn];
int id[maxn],pos[maxn],ans[maxn],bks;
bool vis[maxn];
bool cmp(qnode a,qnode b)//先按左端点所在的块区排，再按右端点排
{
    if(pos[a.l]==pos[b.l])
        return a.r<b.r;
    return pos[a.l]<pos[b.l];//所在的块区
}
void update(int x,bool d)//对权值为x的数进行增删操作
{
/*
开bool数组。如果i出现了就把vis[i]置为1。加入一个数的时候如果vis[i-1]和vis[i+1]都为1的话那么块数ans就要-1.
如果只有一个为1的话ans不变。如果全为0的话ans+1.删除一个数类似处理就行了。
*/
    vis[x]=d;//维护当前节点的vis
    if(d)//增
        bks+=1-vis[x-1]-vis[x+1];
    else//删
        bks+=vis[x-1]+vis[x+1]-1;
}
int main()
{
    int t,n,m,i,j,bk,pl,pr,pp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(vis,0,sizeof vis);
        bk=ceil(sqrt(1.0*n));//每块的大小和总块数都是sqrt（ceil返回大于或者等于指定表达式的最小整数）
        for(i=1;i<=n;i++)//读取每个点的值
        {
            scanf("%d",&id[i]);
            pos[i]=(i-1)/bk;//记录每个i所在的块
        }
        for(i=0;i<m;i++) //读取每个区间（真实坐标）
        {
            scanf("%d%d",&qu[i].l,&qu[i].r);
            qu[i].idx=i;
        }
        sort(qu,qu+m,cmp);
        pl=1,pr=0,bks=0;//pl pr表示当前区间 bks表示总连续块数
        for(i=0;i<m;i++)
        {
            pp=qu[i].idx;
            if(pr<qu[i].r) //当前区间比所求区间小，需要增大区间范围
            {
                for(j=pr+1;j<=qu[i].r;j++)
                    update(id[j],1);
            }
            else//当前区间比所求区间大，需要减小区间范围
            {
                for(j=pr;j>qu[i].r;j--)
                    update(id[j],0);
            }
            if(pl<qu[i].l)
            {
                for(j=pl;j<qu[i].l;j++)
                    update(id[j],0);
            }
            else
            {
                for(j=pl-1;j>=qu[i].l;j--)
                    update(id[j],1);
            }
            pl=qu[i].l,pr=qu[i].r;//此时两区间相等（下一次从该区间开始修改）
            ans[pp]=bks;//记录当前区间得到的解
        }
        for(i=0;i<m;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
