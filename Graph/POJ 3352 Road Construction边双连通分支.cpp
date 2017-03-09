/*
所谓双连通与强连通，最大的差别，也是最本质的差别就是前者适用于无向图中，而后者适用于有向图。
至于两者的概念是一样的，就是图中有a点、b点，从a点可到达b点，同时从b点可到达a点。（若是有向图必须沿方向到达。）
至于边-双连通分量是指在一个无向图中两点间至少有两条路径，且路径中的边不同。边-双连通分量中一定没有桥。
无向连通图中，如果删除某边后，图变成不连通，则称该边为桥（无向图中的连通，就和有向图的强连通一样）

对于边双连通分支，求法更为简单。只需在求出所有的桥以后，把桥边删除，
原图变成了多个连通块，则每个连通块就是一个边双连通分支。桥不属于任何
一个边双连通分支，其余的边和每个顶点都属于且只属于一个边双连通分支。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include<algorithm>
using namespace std;
const int N = 11115;
const int M = 2000005;
struct List {
    int v, id;
    List *next;
} pool[M], *c[N], *g[N], *pp;    //c 为原图的邻接表, g 为 E_BCC 图的邻接表
//注意 pool[M] 要开得足够大以容得下新旧两个图中所有的边
inline void add_edge(int u, int v, int id, List *c[])//邻接表头插法加边
{
    pp->v = v;
    pp->id = id;
    pp->next = c[u];
    c[u] = pp ++;
}
struct Edge {    //edge[] 存储所有的桥,u,v为桥的两个顶点
    int u, v;
} edge[M];
int n, m, label, tot, top;//label时间戳,tot连通块数
int low[N], dfn[N], num[N], stack[N];
//low[u]定义为u或者u的子树中能够通过非父子边(父子边就是之前搜索树上的边）追溯到的最早的节点的DFS开始时间
//用dfn[i]表示编号为i的节点在DFS过程中的访问序号(也可以叫做开始时间）。
bool eflag[M];//num[u] 表示原图中的点 u 属于新图中的第 num[u] 个 E_BCC
void Tarjan(int u) //根据题意显然不存在多重边
{
    low[u] = dfn[u] = label ++;     //刚搜到一个节点时low = dfn
    stack[++ top] = u;// 将该节点入栈
    for(List *p = c[u]; p; p = p->next) {  // 遍历入栈节点的边
        int v = p->v;
        if(eflag[p->id])    continue;    // 如果新搜索到的边是被搜索过,直接跳过
        eflag[p->id] = true;//记录边（因为无向图没方向性，需要记录边防止边重复访问尤其是父亲边）
        if(dfn[v]){
//如果新搜索到的节点已经被搜索过而且现在在栈中(该节点的开始时间肯定比当前点早，而且没更新过low，所以用dfn更新)
            low[u] = min(low[u], dfn[v]);
            continue;
        }
        Tarjan(v);
        low[u] = min(low[u], low[v]);
//一条边(u,v)是桥，当且仅当(u,v)为树枝边，且满足dfn(u)<low(v)（前提是其没有重边）
//桥的特点:删除一条边之后，那么如果dfs过程中的子树没有任何一个点可以到达父亲节点及父亲节点以上的节点，
//那么这个时候子树就被封死了，这条边就是桥。有了这个性质，也就是说当我们dfs过程中遇到一条树边a->b，
//并且此时low[v]>dfn[u]，那么a-b就是一座桥。
        if(low[v] > dfn[u]) {
            edge[m].u = u;//第m条桥的两个顶点u,v
            edge[m ++].v = v;
            ++ tot;
//在找到一条桥后，就准备将一些点出栈，因为这些准备出栈的点都是属于一个边双连通分量的，出栈的终止条件是:
//点v最后出来，点u不能出，注意，点u不能，点u不是属于点v的那个连通分量的，因为桥（u，v）分开了他们
            do {

                num[stack[top]] = tot;
            } while( stack[top --] != v );
        }
    }
}
void solve()
{
    int i;
    tot = 0;
    m = 0;
    for(i = 1; i <= n; ++ i)    dfn[i] = 0, num[i] = -1;//初始化
    for(i = 0; i < m; ++ i)     eflag[i] = false;//初始化
    for(i = 1; i <= n; ++ i)
        if(dfn[i] == 0) {
            label = 1;
            top = -1;
            Tarjan(i);
            //将栈内剩余元素处理为新的双连通分支，因为最后1个子图没有桥
            ++ tot;
            while( top >= 0 ) {
                num[stack[top]] = tot;
                -- top;
            }
        }
}
int main()
{
    int i, j, k;
    while( scanf("%d %d", &n, &m) == 2 ) {
        for(i = 1; i <= n; ++ i)    c[i] = NULL;//初始化       n为顶点数, 标号从1开始
        pp = pool;
        for(k = 0; k < m; ++ k) {//读入无向图
            scanf("%d %d", &i, &j);
            add_edge(i, j, k, c);
            add_edge(j, i, k, c);
        }
        solve();
        if(m == 0){cout<<0<<endl; continue;}
        int du[N]={0};
        for(int i=0;i<m;i++){//桥即为联通块的之间的边,这里处理伪缩点，将双连通分支看作点
            du[num[edge[i].u]]++;//要用num[]映射到连通块编号上计算联通块的度
            du[num[edge[i].v]]++;
        }
        int leaf=0;//树叶
        for(int i=1;i<=tot;i++) if(du[i]==1)leaf++;
        cout<<(leaf+1)/2<<endl;
    }
    return 0;
}
/*
一个有桥的连通图，如何把它通过加边变成边双连通图？
方法为首先求出所有的桥，然后删除这些桥边，剩下的每个连通块都是一个双连通子图。
把每个双连通子图收缩为一个顶点，再把桥边加回来，最后的这个图一定是一棵树，边连通度为1。
统计出树中度为1的节点的个数，即为叶节点的个数，记为leaf。则至少在树上添加(leaf+1)/2条边，
就能使树达到边二连通，所以至少添加的边数就是(leaf+1)/2。
具体方法为：
首先把两个最近公共祖先最远的两个叶节点之间连接一条边，这样可以把这两个点到祖先的路径上所有点收缩到一起，
因为一个形成的环一定是双连通的。然后再找两个最近公共祖先最远的两个叶节点，这样一对一对找完，
恰好是(leaf+1)/2次，把所有点收缩到了一起。
*/
