#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson (rt<<1)
#define rson ((rt<<1)|1)
using namespace std;
typedef long long ll;
const int M = 1e5 + 10;
int head[M],cas,num[M],ans,st[M],ed[M];
ll sum[M],a[M];
ll max(ll x,ll y) {return x>y?x:y;}
struct Edge{ //保存边
   int to;
   int next;
}edge[M*2];
struct Tree{//保存树节点
    int l,r;
    ll ans,lazy;
}tree[M*4];
void add(int x,int y)//两次add，使x和y无方向性
{
    edge[cas].to=x;//cas边的头节点
    edge[cas].next=head[y];//另一个和y相连的边
    head[y]=cas++;//记录和y相连的另一条边
}
void dfs(int u,int pre)//起点u到子节点的权值和（pre是父节点） 利用dfs序找到u在线段树的位置
{
    st[u]=++ans;//前序dfs序列
    num[ans]=u;
    sum[u]+=sum[pre];//更新当前节点u的sum
    for (int i=head[u] ; i!=-1 ; i=edge[i].next)//向下寻找
    {
        int v=edge[i].to;
        if (v==pre) continue;
        dfs(v,u);
    }
    ed[u]=ans;//后序dfs序列
}
void push_down(int rt)
{
    if(tree[rt].lazy)
    {
        tree[lson].lazy+=tree[rt].lazy;tree[rson].lazy+=tree[rt].lazy;
        tree[lson].ans+=tree[rt].lazy;tree[rson].ans+=tree[rt].lazy;
        tree[rt].lazy=0;
    }
}
void build(int rt,int left,int right)
{
    tree[rt].l=left;tree[rt].r=right;
    tree[rt].lazy=0;
    if (left==right)
	{tree[rt].ans=sum[num[left]];return ;}
    int mid=(left+right)/2;
    build(lson,left,mid);
    build(lson+1,mid+1,right);
    tree[rt].ans=max(tree[lson].ans,tree[lson+1].ans);//维护rt到叶子节点的最大值
}

ll query(int rt,int left,int right)
{
    if(tree[rt].l>=left&&tree[rt].r<=right)
        return tree[rt].ans;
    push_down(rt);
    int mid=(tree[rt].l+tree[rt].r)/2;
    if(mid>=right){return query(lson,left,right);}
    else if(mid<left){return query(rson,left,right);}
    else{return max(query(lson,left,mid),query(rson,mid+1,right));}

}
void update(int rt,int left,int right,ll tt)
{
    if(tree[rt].l>=left&&tree[rt].r<=right){
		tree[rt].lazy+=tt;//打上lazy标记
		tree[rt].ans+=tt;
		return;
	}
    int mid=(tree[rt].l+tree[rt].r)/2;
    push_down(rt);//如果有lazy标记
    if(mid<left) update(rson,left,right,tt);
    else if(mid>=right) update(lson,left,right,tt);
    else
    {
        update(lson,left,mid,tt);
        update(rson,mid+1,right,tt);
    }
    tree[rt].ans=max(tree[lson].ans,tree[rson].ans);
}
int main()
{
    int t,n,m,e=0;
    scanf("%d",&t);
    while (t--)
    {
	cas=0;ans=0;
        printf("Case #%d:\n",++e);
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));
        for (int i=1 ; i<n ; i++){//读入边
            int a,b;
            scanf("%d%d",&a,&b);
            a++,b++; //节点全部加1
            add(a,b);add(b,a);//存入边
        }
        for (int i=1 ; i<=n ; i++) //读入权值，初始化sum
		scanf("%lld",&a[i]),sum[i]=a[i];
        dfs(1,0);//求dfs序
        build(1,1,n);//建树
        while (m--)
        {
            int w,b;ll c;
            scanf("%d",&w);
            if (w){
                scanf("%d",&b);b++;
                printf("%lld\n",query(1,st[b],ed[b]));//查询
            }
            else{//改变节点值
                scanf("%d%lld",&b,&c);b++;
                ll q=c-a[b];//需要增加的值
                a[b]=c;//更新节点值
                update(1,st[b],ed[b],q);//维护线段树中数据
            }
        }
    }
    return 0;
}
