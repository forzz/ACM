/*
最小费用最大流：求最大费用只需费用cost取反，结果取反即可。
算法思想：先用spfa找一条最小费用的可增广流路径，再更新残流网络，数组模拟队列快
存图：邻接表
*/
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int MAXN = 10010;
const int MAXM = 100100;
const int INF = 1<<30;
struct EDG{
    int to,next,cap,flow;
    int cost;  //单价
}edg[MAXM];
int head[MAXN],eid;
int pre[MAXN], cost[MAXN] ; //点0~(n-1)

void init(){
    eid=0;
    memset(head,-1,sizeof(head));
}
void addEdg(int u,int v,int cap,int cst){
    edg[eid].to=v; edg[eid].next=head[u]; edg[eid].cost = cst;
    edg[eid].cap=cap; edg[eid].flow=0; head[u]=eid++;

    edg[eid].to=u; edg[eid].next=head[v]; edg[eid].cost = -cst;
    edg[eid].cap=0; edg[eid].flow=0; head[v]=eid++;
}

bool inq[MAXN];
int q[MAXN];
bool spfa(int sNode,int eNode,int n){
    int l=0 , r=0;

    for(int i=0; i<n; i++){
        inq[i]=false; cost[i]= -1;
    }
    cost[sNode]=0; inq[sNode]=1; pre[sNode]=-1;
    q[r++]=sNode;
    while(l!=r){
        int u=q[l++];
        if(l==MAXN)l=0;
        inq[u]=0;
        for(int i=head[u]; i!=-1; i=edg[i].next){
            int v=edg[i].to;
            if(edg[i].cap-edg[i].flow>0 && cost[v]<cost[u]+edg[i].cost){ //在满足可增流的情况下，最小花费
                cost[v] = cost[u]+edg[i].cost;
                pre[v]=i;   //记录路径上的边
                if(!inq[v]){
                    if(r==MAXN)r=0;
                    q[r++]=v;
                    inq[v]=1;
                }
            }
        }
    }
    return cost[eNode] != -1;    //判断有没有增广路
}
//反回的是最大流，最小花费为minCost
int minCost_maxFlow(int sNode,int eNode ,int& minCost,int n){
    int ans=0;
    while(spfa(sNode,eNode,n)){
        int mint=INF;
        for(int i=pre[eNode]; i!=-1; i=pre[edg[i^1].to]){
            if(mint>edg[i].cap-edg[i].flow)
                mint=edg[i].cap-edg[i].flow;
        }
        ans+=mint;
        for(int i=pre[eNode]; i!=-1; i=pre[edg[i^1].to]){
            edg[i].flow+=mint; edg[i^1].flow-=mint;
            minCost+=mint*edg[i].cost;
        }
    }
    return ans;
}

int main()
{
    int T,n,m,k , vs, vt  ;
    scanf("%d",&T);
    for(int cas = 1; cas <= T; cas++)
    {
        scanf("%d%d%d",&n,&m,&k);
        vs = 0 ; vt = m+n+1;
        int ans = 0;
        init();
        for(int i = 1 ; i <= n; i++)
            addEdg( vs , i , 1 , 0);
        int b[20] , tmp ;
        for(int i = 1; i <= m; i++){
            scanf("%d",&b[i]);
            tmp = b[i]/k;
            addEdg( i+n , vt , tmp , k );
            if(b[i]%k != 0)
                addEdg( i+n , vt , 1 , b[i]%k );
            ans += b[i];
        }
        for(int i = 1; i <= m ; i++)
         for(int j = 1; j <= n ; j++){
            scanf("%d",&tmp);
            if(tmp) addEdg( j , i+n , 1  , 0 );
         }

         int tn = n , flow[30]={0};
         n -= minCost_maxFlow( vs , vt , tmp , vt+1) ;
         for(int i = head[vt] ; ~i ; i=edg[i].next)
         {
             int u = edg[i].to - tn ;
             flow[u] += edg[i^1].flow ;
         }
         for(int i = 1 ; i <= m ; i++)
         {
              tmp = flow[i] ;
             if(tmp*k>=b[i])
                ans -= b[i] ;
             else{
                b[i] -= tmp*k ;
                ans -= tmp*k ;
                if(b[i]>n) break;
                ans -= b[i] ;
                n -= b[i] ;
             }
         }

         printf("Case #%d: ",cas);
         if(ans>0)
            printf("NO\n");
         else
            printf("YES\n");
    }
}
