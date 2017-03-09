#include<cstdio>
const int N = 200005;
int n,m,f[N],d[N];     //d[i]表示根节点到i的和
void init() //初始化并查集和权值
{
    for(int i=0; i<=n; ++i)
        f[i]=i,d[i]=0;
}
int find(int x)
{
    if(x==f[x])return f[x];
    int fa=f[x];
    f[x] = find(f[x]);//找到根节点（要先开始递归，再维护权值，否则权值不会一直加到根节点）
    d[x] += d[fa]; //维护权值
    return f[x];
}
bool Union(int x,int y,int c)
{
    int a=find(x), b=find(y);
    if(a==b){//两者在一连续区间中
        if(d[x]+c!=d[y]) return false;
        return true;
        }
    f[b] = a; //构建新关系
    d[b] = d[x]-d[y]+c;//维护d
    return true;
}
int main()
{
    int a,b,c;
    while(~scanf("%d%d",&n,&m)){
        int cnt=0;
        init();
        for(int i=0; i<m; ++i){
            scanf("%d%d%d",&a,&b,&c);
            if(!Union(a-1,b,c)){//a-1可以让两个区间相连(ab带权c )  1,2 与3,4
                ++cnt;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
