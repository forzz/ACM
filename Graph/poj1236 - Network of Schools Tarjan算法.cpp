#include <stdio.h>
#include <string.h>
#include <queue>
#include<algorithm>
using namespace std;
#define MAXN 110
#define INF 0x3f3f3f3f
int n;
int mp[MAXN][MAXN];  //邻接矩阵保存图
int low[MAXN];//用low[i]表示从i节点出发DFS过程中i下方节点(开始时间大于dfn[i]，且由i可达的节点）所能到达的最早的节点的开始时间。
int dfn[MAXN];//用dfn[i]表示编号为i的节点在DFS过程中的访问序号(也可以叫做开始时间）。
int stack[MAXN], head;  //栈数组和栈顶
int instack[MAXN];
int belong[MAXN]; //染色
int in[MAXN];
int out[MAXN];
int index, cnt;  //时间戳和连通分量编号
void init()  //初始化并读入数据
{
    int i, j;
    int temp;
    memset(mp, 0, sizeof(mp));
    memset(dfn, -1, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instack, 0, sizeof(instack));
    index = cnt = 1; //初始时间戳为1，初始连通分量编号为1
    head = 0;  //初始栈顶为0
    for(i= 1; i <= n; i++)
    {
        while(scanf("%d", &temp) && temp)
        {
            mp[i][temp] = 1;
        }
    }
}
void tarjan(int x)
{
    int i, a;
    low[x] = dfn[x] = index; // 刚搜到一个节点时low = dfn
    index++;
    stack[++head] = x; // 将该节点入栈
    instack[x] = 1; // 将入栈标记设置为1
    for(i = 1; i <= n; i++) // 遍历入栈节点的边
    {
        if(!mp[x][i]) // 如果两点之间没有边
            continue; // 不用管它
        if(dfn[i] == -1) // 如果新搜索到的节点是从未被搜索过
        {
            tarjan(i); // 那自然就得搜索这个节点
            low[x] = min(low[x], low[i]); // 回溯的时候改变当前节点的low值
//对于u的子节点v，从v出发进行的DFS结束回到u时，使得 low[u] = min(low[u],low[v])。因为u可达v,所以v可达的最早的节点，也是u可达的。
        }
        else if(instack[i]) // 如果新搜索到的节点已经被搜索过而且现在在栈中(该节点的开始时间肯定比当前点早，而且没更新过low，所以用dfn更新)
        {
            low[x] = min(low[x], dfn[i]);
//如果发现某节点u有边连到栈里的节点v，则更新u的low 值为min(low[u],dfn[v]) ，若low[u]被更新为dfn[v],则表明目前发现u可达的最早的节点是v.
        }
    }
    if(low[x] == dfn[x]) // 最终退回来的时候 low == dfn ， 没有节点能将根节点更新，那low == dfn 的节点必然就是根节点
    {
        int temp;
        while(1) //此时，显然栈中u上方的节点，都是不能到达比u早的节点的。将栈中节点弹出，一直弹到u(包括u),弹出的节点就构成了一个强连通分量.
        {
            temp = stack[head--]; // 弹出栈元素
            belong[temp] = cnt; // 为了方便计算，将强联通分量进行标记
            instack[temp] = 0; // 将栈内标记置为0
            if(temp == x)     // 一直弹到x出现为止
                break;
        }
        cnt++;
    }
}
int main()
{
    int i, j;
    int t1, t2;
    while(scanf("%d", &n) != EOF)
    {
        init(); // 初始化
        for(i = 1; i <= n; i++)    //遍历每个节点
            if(dfn[i] == -1) // 如果某点没被访问过，则对其进行tarjan
                tarjan(i);     // tarjan的成果是得到了一个belong数组，记录每个节点分别属于哪个强联通分量
        for(i = 1; i <= n; i++) // 遍历每条边，找到缩点之后的边
        {
            for(j = 1;j <= n; j++)
            {
                if(mp[i][j] && belong[i] != belong[j]) // 两点之间有边，但不是属于一个强联通分量的边
                {
                    out[belong[i]]++; // 缩点后的点入度+1
                    in[belong[j]]++;// 缩点后的点出度+1
                }
            }
        }
//有向无环图中所有入度不为0的点，一定可以由某个入度为0的点出发可达。
//(由于无环，所以从任何入度不为0的点往回走，必然终止于一个入度为0的点)
        t1 = 0, t2 = 0;
        for(i = 1; i < cnt; i++)
        { //DAG上面有多少个入度为0的顶点，问题1的答案就是多少
            if(in[i] == 0)
                t1++;
//在DAG上要加几条边，才能使得DAG变成强连通的，问题2的答案就是多少
//加边的方法：要为每个入度为0的点添加入边，为每个出度为0的点添加出边，假定有 n 个入度为0的点，m个出度为0的点，max(m,n)就是第二个问题的解
//将这个图的所有子树找出来，然后将一棵子树的叶子结点（出度为0）连到另外一棵子树的根结点上（入度为0），这样将所有的叶子结点和根节点
//全部消掉之后，就可以得到一整个强连通分量，看最少多少条边，这样就是看叶子结点和根节点哪个多，即出度为0和入度为0哪个多
            if(out[i] == 0)
                t2++;
        }
        if(cnt == 2)  //只有1个结点要特判（cnt比节点值大1）
            printf("1\n0\n");
        else
            printf("%d\n%d\n", t1, max(t1, t2));
    }
    return 0;
}

