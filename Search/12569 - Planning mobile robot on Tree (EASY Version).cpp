#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=15;
const int maxstate=(1<<maxn)*maxn+10;  //15种可能，状态用二进制方式存储
int n,m,s,t;
int fa[maxstate],dist[maxstate];
bool vis[1<<maxn][maxn],g[maxn][maxn];  //每一个状态只有2个数，可以直接开二维数组vis来判重
typedef int go[2];
typedef int state[2];
state st[maxstate];
go k[maxstate];
void read(){
    memset(g,0,sizeof(g));
    memset(k,0,sizeof(k));
    memset(fa,0,sizeof(fa));
    memset(st,0,sizeof(st));
    memset(vis,0,sizeof(vis));
    memset(dist,0,sizeof(dist));
    scanf("%d%d%d%d",&n,&m,&s,&t);
    st[1][1]=s-1,st[1][0]|=1<<(s-1);//记录初始状态机器人的位置。 st[1][0]保存图状态 st[1][1]保存起点
    for(int i=0;i<m;++i){
        int k;
        scanf("%d",&k);
        st[1][0]|=1<<(k-1);//障碍物的位置。（位或操作）
    }
    for(int i=1;i<n;++i){  //保存连通关系
        int u,v;
        scanf("%d%d",&u,&v);
        g[u-1][v-1]=g[v-1][u-1]=true;
    }
    return;
}
int bfs(){
    int front=1,rear=2;  //队列指针
    while(front<rear){
        state& s=st[front]; //st直接作为队列数组
        if(s[1]==t-1) return front;  //到达终点
        for(int i=0;i<n;++i){
            if(!(s[0]&(1<<i))) continue;//i处为空地，跳过
            for(int j=0;j<n;++j){//i处有东西
                if((s[0]&(1<<j))||!g[i][j]) continue;  //j处有东西或者i与j不连通，跳过
                state& t=st[rear];
                memcpy(&t,&s,sizeof(s)); //将s复制到队尾（队尾初始为空）
                if(s[1]==i) t[1]=j;  //维护机器人位置
                t[0]^=1<<i|1<<j;//交换位置。（01则1 全1则0）
                k[rear][0]=i+1,k[rear][1]=j+1;  //记录新状态的走法
                dist[rear]=dist[front]+1,fa[rear]=front;//记录当前步数和父状态。（队列数组中数据不会清除）
                if(!vis[t[0]][t[1]]) vis[t[0]][t[1]]=true,++rear;
                //如果未访问，标记新状态；如果已访问，下一次bfs会直接覆盖
            }
        }
        ++front;
    }
    return 0;
}
void print_ans(int a){
    if(!fa[a]) return;//递归至初始状态。
    print_ans(fa[a]);
    printf("%d %d\n",k[a][0],k[a][1]);
    return;
}
int main(){
    int t,tt=0;
    scanf("%d",&t);
    while(t--){
        read();
        int a=bfs();
        printf("Case %d: %d\n",++tt,a?dist[a]:-1);
        print_ans(a);
        printf("\n");
    }
    return 0;
}
