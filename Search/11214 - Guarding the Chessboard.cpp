#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=11;
int n,m,t,maxd;
bool g[maxn][maxn],vis[4][maxn*2];  //vis数组判断皇后所在的行和列和两个对角线是否有其他皇后
bool guard(){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        if(g[i][j]&&!vis[0][i]&&!vis[1][j]&&!vis[2][i+j]&&!vis[3][i-j+maxn]) return false;
    return true;
}
bool dfs(int i,int j,int d){
    if(d==maxd){//到达最大深度
        if(guard())  return true;
        return false;
    }
    while(i<n){
        while(j<m){
            bool tmp1=vis[0][i],tmp2=vis[1][j],tmp3=vis[2][i+j],tmp4=vis[3][i-j+maxn];
        //备份全局变量
            vis[0][i]=vis[1][j]=vis[2][i+j]=vis[3][i-j+maxn]=true;
            //行 列 主对角线 副对角线
            if(dfs(i,j+1,d+1)) return true;  //dfs下一列
            vis[0][i]=tmp1,vis[1][j]=tmp2,vis[2][i+j]=tmp3,vis[3][i-j+maxn]=tmp4;
            //恢复状态
            ++j;
        }
        j%=m,++i;
    }
    return false;
}
int main()
{
    while(scanf("%d",&n),n){
        scanf("%d",&m);
        memset(g,0,sizeof(g));
        for(int i=0;i<n;i++){
            getchar();
            for(int j=0;j<m;j++)
                if(getchar()=='X') g[i][j]=true;
        }
        for(maxd=0;maxd<5;++maxd){
//测试之后发现10*10的棋盘全部守卫至少需要5个，所以上限就是5，当maxd等于5时直接输出，不进行搜索。
            memset(vis,0,sizeof(vis));
            if(dfs(0,0,0)) break;
        }
        printf("Case %d: %d\n",++t,maxd);
    }
    return 0;
}
