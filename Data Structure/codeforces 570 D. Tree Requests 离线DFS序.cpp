//离线算法，一次性处理所有询问后统一输出，需要考虑不同的询问中是否会有之前的询问残留数据存在
//先来说下离线的做法，先把所有的询问读入，按dfs搜索的顺序，每个询问在进入前先异或上这层的值，
//出这个结点时，再异或上这层的值，先前该层的值异或两次抵消了，所以就是这个结点下的子树的该层的值了。
#include<bits/stdc++.h>
using namespace std;
vector<int>G[500009];
vector<int>Query[500009];
int dep[500009];
char str[500009];
int ans[500009];
int height[500009];
void dfs(int u,int d)//u为dfs的根节点 d为u的深度（以root为根）
{
    for(int v:Query[u]) //遍历询问中以u为根节点的情况（开始处理这些询问）
        ans[v]^=dep[height[v]]; //先把该深度的所有节点全部异或
    for(int v:G[u])   //v表示u节点的子节点，更新下一层
        dfs(v,d+1);
    dep[d]^=(1<<(int)(str[u]-'a')); //将u加入dep[d]，维护dep数组
    for(int v:Query[u]) //以u为根节点的树dfs完毕，这时再异或该深度的所有节点，由异或性质，取出dfs过程中的变化量，也就是所求部分
        ans[v]^=dep[height[v]];
}
int main()
{//所有节点的字母能不能排成一个对称的字符串 即出现奇数次的字母个数<=1个 从根节点按深度异或，如果结果为0，不能回文，若结果为2的正整数幂（仅有1个1）为奇回文串
    int n,m,x,y;
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)   //按父节点保存整棵树
    {
        scanf("%d",&x);
        G[x].push_back(i);      //G[x]记录以x为父节点的所有节点编号
    }
    scanf("%s",(str+1));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        Query[x].push_back(i);   //Query[x][i]保存 以x为父节点 的询问编号
        height[i]=y;    //i询问深度为y
    }
    dfs(1,1);
    for(int i=1;i<=m;i++)
    {
        if(ans[i]&(ans[i]-1)) printf("No\n");
//若n为2的正整数幂（00100……00）即（n&（n-1））==0  当n=0时符合此式但不是正整数幂 需(!(n&(n-1)) ) && n == 1   但此题不需区分0，因为0满足条件
        else printf("Yes\n");
    }
    return 0;
}
