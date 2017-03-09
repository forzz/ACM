#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;
#define maxn 6005
int n;
int dp[maxn][2],father[maxn];//dp[i][0]0表示不去，dp[i][1]1表示去了
bool visited[maxn];
/*
dp[u][0]表示以u为顶点的子树，不选u点的情况下最大值
dp[u][1]表示以u为顶点的子树，选u点的情况下最大值
*/
void tree_dp(int node)
{
    int i;
    visited[node] = 1;//dfs标记已访问节点
    for(i=1; i<=n; i++)
    {
        if(!visited[i]&&father[i] == node)//i为下属
        {
            tree_dp(i);//先递归调用孩子结点，从叶子结点开始dp，然后维护当前节点信息
            dp[node][1] += dp[i][0];//上司来,下属不来
            dp[node][0] +=max(dp[i][1],dp[i][0]);//上司不来，下属来、不来
        }
    }
}

int main()
{
    int i;
    int f,c,root;
    while(scanf("%d",&n)!=EOF)
    {
        memset(dp,0,sizeof(dp));
        memset(father,0,sizeof(father));
        memset(visited,0,sizeof(visited));
        for(i=1; i<=n; i++)
        {
            scanf("%d",&dp[i][1]); //记录每个节点的价值,初始化dp
        }
        root = 0;//记录父结点
        bool beg = 1;
        while (scanf("%d %d",&c,&f),c||f) //都为0时结束，c的父节点是f
                father[c] = f;
        while(father[root])//查找根节点
        root=father[root];//构造一棵树，设立空根节点，保持一致性
        tree_dp(root);
        int imax=max(dp[root][0],dp[root][1]);
        printf("%d\n",imax);
    }
    return 0;
}
