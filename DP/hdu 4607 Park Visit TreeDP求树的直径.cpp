#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 100005;
vector<int>tree[maxn];
int vis[maxn];
void init(int n){
    for( int i = 1; i <= n; i++)tree[i].clear();
}
int len;//保存树的最大直径
int dfs(int u){//以u为根节点dfs，求最大树的直径(每个dfs都维护最大距离和次大距离)
    vis[u] = 1;//保存标记
   int Max = 0,lastMax = 0,i,j,size;
   size = tree[u].size();
   for( int i = 0; i < size; i ++){
        if( vis[tree[u][i]])continue;
        int tmp = dfs(tree[u][i])+1;//dfs（i）保存以i为根节点的最大距离
        if( tmp > Max){//先维护最大距离
            lastMax = Max ;
            Max = tmp;
        }else if( tmp  > lastMax)//再维护次大距离
            lastMax = tmp ;
        if( len < Max + lastMax)len = Max + lastMax;//维护树的直径长度
   }
   return Max;//返回最大距离
}
int main(){
    int T,n,m;
    int u,v,k;
  // freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while( T-- ){
        scanf("%d%d",&n,&m);//n个点 m个询问
        init(n);
        for( int i = 1; i < n; i++){//建树
            scanf("%d%d",&u,&v);
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        len = 0;
        memset(vis,0,sizeof(vis));
        dfs(1);
        // printf("%d\n",len);
        while( m-- ){
            scanf("%d",&k);
//得到当需要访问的景点数目小于等于直路上的景点的和数目的时候不需要走岔路，大于的时候每多走一个景点就得多计算一个返程（树中无环）
            if( k <= len)printf("%d\n",k-1);
            else printf("%d\n",len + (k-1-len)*2);
        }
    }
}
