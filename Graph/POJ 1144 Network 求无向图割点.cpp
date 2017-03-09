#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nMax 110
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)
int map[nMax][nMax];
int DFN[nMax],Low[nMax];
bool isVisted[nMax];
int gPoint[nMax];
int index, root;
int n,ans;
void tarjan(int u)
{
//一个顶点u是割点，当且仅当满足(1)或(2)
//（1）u为树根，且u有多于一个子树（若是求点双连通分量，不需要考虑）
//条件1的意思是若为根，下面如果只有一颗子树，也就是整个图是强连通，那么去掉根节点，肯定不会变成多个子图，
//因此也不会成为割点。只有大于一颗子树，去掉根节点，才会有两个或者2个以上的子图，从而才能成为割点
//（2）u不为树根，且存在(u,v)为树枝边(或称父子边，即u为v在搜索树中的父亲)，使得dfn(u)<=low(v)
//条件2的意思是u不为树根，那么u肯定有祖先，如果存在Low【v】>=DFN【u】时，表示u的子孙只能通过u才能访问u的祖先，
//这也就是说，不通过u，u的子孙无法访问u的祖先，那么如果去掉u这个节点，就会至少分为两个子图，一个是u祖先，一个是u子孙的。
    DFN[u] = Low[u] = ++index;
    isVisted[u] = true;
    for (int i = 1; i <= n; ++ i)
    {
        if (map[u][i])
        {
            if (!isVisted[i])
            {
                tarjan(i);
                Low[u] = Min(Low[u], Low[i]);
                if (Low[i] >= DFN[u] && u != 1)//if it is not root
                {
                    gPoint[u] ++;
                }
                else if (u == 1)//if it is root
                {
                    root ++;
                }
            }
            else
            {
                Low[u] = Min(Low[u], DFN[i]);
            }
        }
    }
}
int main()
{
    while (scanf("%d", &n) && n)
    {
        int u, v;
        memset(map, 0, sizeof(map));
        memset(isVisted, false, sizeof(isVisted));
        memset(gPoint, 0, sizeof(gPoint));
        ans = root = index = 0;
        while (scanf("%d", &u) && u)
        {
            while (getchar() != '\n')
            {
                scanf("%d", &v);
                map[u][v] = 1;
                map[v][u] = 1;
            }
        }
        tarjan(1);
        if (root > 1)
        {
            ans ++;
        }
        for (int i = 2; i <= n; ++ i)
        {
            if (gPoint[i])
            {
                ans ++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
