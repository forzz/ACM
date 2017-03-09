#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 1005;
int N, pos[maxn];
vector<int> g[maxn]; //保存每个节点的孩子
int main () {
    while (scanf("%d", &N) == 1) {
        int x;
        for (int i = 1; i <= N; i++) {  //读入BFS序列，BFS序列映射出了每个节点和根节点的距离
            scanf("%d", &x);
            g[i].clear();
            pos[x] = i;          //将位置储存在pos数组中,也代表其与根节点的距离
        }
        int root;
        stack<int> sta;
        scanf("%d", &root);  //DFS中的根节点
        sta.push(root);

        for (int i = 1; i < N; i++) {  //遍历DFS先序序列，dfs的序列分成若干段，每一段相当一个子树，模拟DFS栈存储
            scanf("%d", &x);
            while (true) {
                int u = sta.top();
                if (u == root || pos[u] + 1 < pos[x]) {
//对当前节点和栈顶节点比较，如果该节点距离根节点更远，则说明该节点为栈顶节点的孩子节点，则记录后将节点放入栈中。
//需要注意一点，即当元素距离值比栈顶元素的距离值大1的时候要视为相等,因为它们属于兄弟节点
                    g[u].push_back(x);
                    sta.push(x); //x压入栈，判断下一个x是否为x的孩子
                    break;  //确定x所属，直接停止循环
                } else
                    sta.pop();//栈顶元素无孩子，直接出栈
            }
        }
        for (int i = 1; i <= N; i++) {
            printf("%d:", i);
            for (int j = 0; j < g[i].size(); j++)
                printf(" %d", g[i][j]);
            printf("\n");
        }
    }
    return 0;
}
