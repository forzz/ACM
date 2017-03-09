#include<algorithm>
#include<stdio.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int maxn=150;
const int maxm=5010;
int ti[maxn][maxm],f[maxn][maxm],tree[maxm<<2],lazy[maxm<<2];
int dp[maxm],n,m;
void build(int L,int R,int rt)
{
    int ls,rs,mid;
    tree[rt]=lazy[rt]=INF;
    if(L==R)
        return ;
    ls=rt<<1;
    rs=ls|1;
    mid=(L+R)>>1;
    build(L,mid,ls);
    build(mid+1,R,rs);
}
void pushdown(int k,int ls,int rs)
{
    tree[ls]=min(tree[ls],lazy[k]);
    tree[rs]=min(tree[rs],lazy[k]);
    lazy[ls]=min(lazy[ls],lazy[k]);
    lazy[rs]=min(lazy[rs],lazy[k]);
    lazy[k]=INF;//消除标记
}
void update(int L,int R,int l,int r,int k,int v)
{
    int ls,rs,mid;
    if(L==l&&R==r)//找到区间
    {
        tree[k]=min(tree[k],v);
        lazy[k]=min(lazy[k],v);
        return;
    }
    ls=k<<1;
    rs=ls|1;
    mid=(L+R)>>1;
    if(lazy[k]!=INF)//存在标记
        pushdown(k,ls,rs);
    if(l>mid)
        update(mid+1,R,l,r,rs,v);
    else if(r<=mid)
        update(L,mid,l,r,ls,v);
    else
    {
        update(L,mid,l,mid,ls,v);
        update(mid+1,R,mid+1,r,rs,v);
    }
    tree[k]=min(tree[ls],tree[rs]);
}
int query(int L,int R,int l,int r,int k)
{
    int ls,rs,mid;
    if(L==l&&R==r)
        return tree[k];
    ls=k<<1;
    rs=ls|1;
    mid=(L+R)>>1;
    if(lazy[k]!=INF)
        pushdown(k,ls,rs);
    if(l>mid)
        return query(mid+1,R,l,r,rs);
    else if(r<=mid)
        return query(L,mid,l,r,ls);
    else
        return min(query(L,mid,l,mid,ls),query(mid+1,R,mid+1,r,rs));

}
int main()
{
    int i,j,l,r,ans;

    while(scanf("%d%d",&n,&m),n||m)
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                scanf("%d",&ti[i][j]);
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                scanf("%d",&f[i][j]);
        for(i=1;i<=m;i++)//初始化dp值为每列第一个
            dp[i]=ti[1][i];
        for(i=2;i<=n;i++)//枚举第二行以后每行
        {
            build(1,m,1);//建树
            for(j=1;j<=m;j++)//添加当前列的dp值到线段树，求出最小值
            {//[j-f[i][j],j+f[i][j]]区间内
                l=max(j-f[i-1][j],1);//左端点
                r=min(j+f[i-1][j],m);//右端点
                update(1,m,l,r,1,dp[j]);
            }
            for(j=1;j<=m;j++)
            {
                l=max(j-f[i][j],1);
                r=min(j+f[i][j],m);
                dp[j]=query(1,m,l,r,1)+ti[i][j];//更新dp
            }
        }
        ans=INF;
        for(i=1;i<=m;i++)
            ans=min(ans,dp[i]);
        printf("%d\n",ans);
    }
    return 0;
}
