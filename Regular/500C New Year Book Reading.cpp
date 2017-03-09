#include <cstdio>
#include <cstring>
using namespace std;
int w[505], b[1005];
bool vis[505];
int main()
{
/*
贪心结论：拿每本书第一次出现的顺序作为初始序列，比如1 1 3 1 1 3 2 1 1
按此策略得到的初始序列为1 3 2，不管初始序列是什么样的，读完 1 1 3以后的书的顺序肯定都是确定的都为3 1 2，
但是只有初始序列为1 3 2时得到3 1 2的代价最小。
*/
    int n, m, ans = 0;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", &w[i]);     //书的重量
    for(int i = 1; i <= m; i++)
        scanf("%d", &b[i]);     //看书安排
    for(int i = 2; i <= m; i++) //考虑第i天看书安排
    {
        memset(vis, false, sizeof(vis));
        for(int j = i - 1; j > 0; j--)//第i天前看的书倒序遍历
        {
//对于其上面的书，我只关心它们的总重量，比如1 2 3 2 3 1 关心第二次读到1时它上面有哪些书和它们的重量即w[2] + w[3]
            if(b[j] == b[i]) //找到同一本读过的书
                break;

            if(!vis[b[j]])      //vis标记重复
            {
                ans += w[b[j]];
                vis[b[j]] = true;
            }
        }
    }
    printf("%d\n", ans);
}
