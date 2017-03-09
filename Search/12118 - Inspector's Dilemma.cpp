#include <bits/stdc++.h>
using namespace std;
int v, e, t, kase = 0;  //全局变量
const int maxn = 1024;
vector<int> Road[maxn];
bool vis[maxn];

void init()//初始化
{
    memset(vis, false, sizeof(vis));
    for(int i = 0; i < maxn; ++i)  //每个节点相连的点
        Road[i].clear();
}

int DFS(int n)//以n为起点
/*
当每条边仅经过一次时，路径最短。给出的边可能构成若干棵树。
在一棵树中，若一棵树的奇点个数为0，则这棵树可以构成欧拉回路，若不为0，则必有走不到的边。
*/
{
    if(vis[n]) return 0; //n已访问
    int cnt = 0;
    vis[n] = true;
    cnt += (Road[n].size() & 1);//度数进行二进制&运算，判断奇偶（奇1偶0）
    for(size_t i = 0; i < Road[n].size(); ++i)
        cnt += DFS(Road[n][i]);
    return cnt;

}

int solve()
{
    int res = 0;
    for(int i = 1; i <= v; ++i)
        if(!vis[i] && !Road[i].empty()) //未访问且与i有关的路不空
            res += max(DFS(i), 2);
    return t * (max((res - 2) / 2, 0) + e);
/*
当每条边仅经过一次时，路径最短。
在一棵树中，设奇点个数为n，则走不到的边数为(n-2)/2 （n-2为除去起点和终点的奇点个数），
这意味着，还需要走额外的(n-2)/2条边才能将这(n-2)/2条指定的但走不到的边走完。
并且，这(n-2)/2条走不到的边是不共点的，这意味着，一棵树还是多棵树是无关紧要的。
但是，如果有的树中奇点个数恰为0，没有走不到的边，此时这棵树成了孤立的了，要注意这种情况。
*/
}

int main()
{
    ios::sync_with_stdio(false);
    while(init(), cin >> v >> e >> t, v || e || t){
        for(int i = 0; i < e; i++){
            int x, y; cin >> x >> y;
            Road[x].push_back(y); Road[y].push_back(x);
        }
        printf("Case %d: %d\n", ++kase, solve());
    }
    return 0;
}
