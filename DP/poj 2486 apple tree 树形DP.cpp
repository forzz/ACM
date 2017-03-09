#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int> g[1010];
int dp[2][1010][210];
int n,V,val[1010];
bool used[1010];
void Max(int &a,int b){//手写max，增加了赋值功能
    if(a<b) a=b;
}
void dfs(int s){
    int i;
    used[s]=true;
    for(i=0;i<=V;i++){
         dp[0][s][i]=dp[1][s][i]=val[s];//dfs之前需要先初始化dp（从s到i的dp值初始化为s的值，考虑边界）
    }
    for(i=0;i<g[s].size();i++){
        int t=g[s][i];
        if(used[t]) continue;
        dfs(t);//先dfs求出子节点的结果
        for(int j=V;j>=0;j--){//枚举总步数
            for(int k=0;k<=j;k++){//父节点与子节点分配总步数（做的步数相当于背包的容量，点上的权值相当于价值，给定一定的背包容量，求最多能装进背包的价值
                Max(dp[0][s][j+2],dp[0][t][k]+dp[0][s][j-k]);//从s出发，要回到s，需要多走两步s-t,t-s,分配给t子树K步，其他子树j-K步，都返回
                Max(dp[1][s][j+2],dp[0][t][k]+dp[1][s][j-k]);//不回到s（去s的其他子树），在t子树返回，同样有多出两步
                Max(dp[1][s][j+1],dp[1][t][k]+dp[0][s][j-k]);//先遍历s的其他子树，回到s，遍历t子树，在当前子树t不返回，多走一步s-t
            }
        }
    }
}
int main(){
//dp[0][s][j]表示从s（当前根节点）出发，走j步，回到s所能获得的最大权值
//dp[1][s][j]表示从s（当前根节点）出发，走j步，不回到s所能获得的最大权值
    int i,a,b;
    while(scanf("%d%d",&n,&V)!=EOF){
        for(i=0;i<=1000;i++)
            g[i].clear();
        for(i=1;i<=n;i++)//保存每个节点的权值
            scanf("%d",&val[i]);
        for(i=0;i<n-1;i++){//保存每条边
            scanf("%d%d",&a,&b);
            g[a].push_back(b);
            g[b].push_back(a);
        }
        memset(dp,0,sizeof(dp));
        memset(used,false,sizeof(used));
        dfs(1);
        printf("%d\n",dp[1][1][V]);
    }
    return 0;
}
/*
主要思想：考虑父子节点各有2种状态（返回和不返回），考虑两者之间的联系
s返回，t返回
s不返回，t返回（走向t子树，t子树返回之后走向s的其他子树，然后不回到s）
s返回，t不返回（遍历s的其他子树后返回s，返回之后走向t子树，然后不回到t）
没有都不返回，肯定有一方有一个返回的过程，再去另一边的子树的
总结起来一句话，要么去s的其他子树呆着，要么去t子树呆着，要么回到s点
*/
