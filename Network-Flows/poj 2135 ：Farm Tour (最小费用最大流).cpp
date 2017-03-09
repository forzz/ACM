#include<queue>
#include<stdio.h>
#include<string.h>
#define N_node 1000 + 10
#define N_edge 40000 + 20
#define INF 100000000
using namespace std;
typedef struct
{
   int from ,to ,cost ,flow ,next;
}STAR;
STAR E[N_edge];
int list[N_node] ,tot;
int mer[N_edge];
int s_x[N_node];
void add(int a ,int b ,int c ,int d)//链式向前星
{
     E[++tot].from = a;//正向图
     E[tot].to = b;
     E[tot].cost = c;
     E[tot].flow = d;
     E[tot].next = list[a];
     list[a] = tot;

     E[++tot].from = b;//逆向图
     E[tot].to = a;
     E[tot].cost = -c;
     E[tot].flow = 0;
     E[tot].next = list[b];
     list[b] = tot;
}
bool Spfa(int s ,int t ,int n)//因为有负权边（取消流的时候产生的），所以不能用迪杰斯特拉算法求最短路。
{
    int mark[N_node] = {0};//标记数组
    for(int i = 0 ;i <= n ;i ++) s_x[i] = INF;//初始化所有边到源的最短距离
    mark[s] = 1 ,s_x[s] = 0;//源点
    queue<int>q;
    q.push(s);
    memset(mer ,255 ,sizeof(mer));
    while(!q.empty())
    {
        int xin ,tou = q.front();
        q.pop();
        mark[tou] = 0;
        for(int k = list[tou] ;k ;k = E[k].next)//枚举s的所有邻边
        {
            xin = E[k].to;
            if(s_x[xin] > s_x[tou] + E[k].cost && E[k].flow)
            {//由于S到u的最短距离变小了，有可能u可以改进其它的点，所以若u不在队列中，就将它放入队尾。
                s_x[xin] = s_x[tou] + E[k].cost;
                mer[xin] = k;//标记前驱
                if(!mark[xin])
                {
                    mark[xin] = 1;
                    q.push(xin);
                }
            }
        }
    }
    return mer[t] != -1;//如果
}
int M_C_Flow(int s ,int t ,int n)
{
   int maxflow = 0 ,mincost = 0 ,minflow;
   while(Spfa(s ,t ,n))
//反复用spfa算法做源到汇的最短路进行增广， 边权值为边上单位费用。反向边上的单位费用是负的。
//直到无法增广，即为找到最小费用最大流
//成立原因：每次增广时，每增加1个流量，所增加的费用都是最小的。
   {
       minflow = INF;
       for(int i = mer[t] ;i + 1 ;i = mer[E[i].from])//逆向遍历当前找到的最短路
       if(minflow > E[i].flow) minflow = E[i].flow;//找到当前最短路中的最小流量
       for(int i = mer[t] ;i + 1 ;i = mer[E[i].from])//逆向遍历
       {
           E[i].flow -= minflow;//正向边减少流量
           E[i^1].flow += minflow;//逆向边添加流量
           mincost += minflow * E[i].cost;
       }
       maxflow += minflow;
   }
   return mincost;
}
int main ()
{
//最小费用就是路径长度的总和，最大流就是来回的两条路。
//由于去和回来可以看成： 2条从1到n的不同的路。所以转化成求从1到n的两条不同的路。
    int n ,m ,i ,a ,b ,c;
    while(~scanf("%d %d" ,&n ,&m))
    {
//假设a b之间有长度为c的路。按照最小费用流建图：
//ab之间费用为c，容量是1。 ba之间费用为c，容量是1
       memset(list ,0 ,sizeof(list)) ,tot = 1;
       for(i = 1 ;i <= m ;i ++)
       {
          scanf("%d %d %d" ,&a ,&b ,&c);
          add(a ,b ,c ,1);
          add(b ,a ,c ,1);
       }
       add(0 ,1 ,0 ,2);//建立一个源点，连接1号景点，无费用，容量为2，费用为0（表示可以有两条路）
       add(n ,n + 1 ,0 ,2);//建立一个汇点，连接n号景点，无费用，容量为2.费用为0
       printf("%d\n" ,M_C_Flow(0 ,n + 1 ,n + 1));
//如果求的的最大流是2，就表示了有两条从1到n的不同的路。（因为中间的点边容量只是1，只能用一次）
    }
    return 0;
}
