#include <iostream>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <cstdio>
#define MAX_V 500
#define INF 0x3f3f3f3f
using namespace std;
struct edge
{
        int to, cap, rev;//cap保存流量   rev表示起点
        edge(){}
    edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
};
vector <edge> G[MAX_V];
struct machine {
    int time;
    int in[20], out[20];
};
machine m[100];
int level[MAX_V];//顶点到源点的距离编号
int iter[MAX_V];//当前弧，在其之前的边不用再考虑
void add_edge(int from, int to, int cap) {
    G[from].push_back(edge(to, cap, G[to].size()));//正向建立边
    G[to].push_back((edge(from, 0, G[from].size()-1)));//反向建立边
}
void bfs(int s) {//bfs用来计算从源点出发所有点的距离编号
    memset(level, -1, sizeof(level));
    queue<int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()) {
        int v = que.front(); que.pop();
        for (int i = 0; i < G[v].size(); i++) {//枚举每条边
            edge &e = G[v][i];
            if (e.cap > 0 && level[e.to] < 0) {//没访问过并且存在边
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v, int t, int f) {//通过DFS寻找当前的最短的增广路(V为起点，t为虚拟汇点，f为当前最大流)
    if (v == t) return f;//dfs到终点
    for (int  &i = iter[v]; i < G[v].size(); i++) {//这里用引用，巧妙地修改了iter数组（相当于visit数组）使其在DFS中一直附带
        edge &e = G[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {//level[v] < level[e.to]这个条件保证了当前的增广路是最短的
            int d = dfs(e.to, t, min(f, e.cap));//dfs中附加当前最小流量
            if (d > 0) {//找到最短增广路
                e.cap-=d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s, int t) {//求出最大流（s为虚拟原点）
    int flow = 0;
    while(1) {
        bfs(s);//求出分层
        //当残余网络的分层操作无法算出汇点的层次（即BFS到达不了汇点）时，算法结束，最大流求出
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while (( f = dfs(s, t, INF)) > 0) {
            flow += f;
        }
    }
}
int main() {
//机器要组装零件，每个机器有2*P+1个数字来描述，装配速度可以理解为容量
//每个零件有3个参数0 表示不需要 1表示必须有 2可以可有可无
    int P, N;
    while (EOF != scanf("%d%d", &P, &N)) {//P个部件 N台机器
        int i, j, k;
        for (i = 0; i < MAX_V; i++) G[i].clear();
        for (i = 0; i < N; i++) {//读入每台机器的数据
            scanf("%d", &m[i].time);
            for (j = 0; j < P; j++) {
                scanf("%d", &m[i].in[j]);
            }
            for (j = 0; j < P; j++) {
                scanf("%d", &m[i].out[j]);
            }
        }
//将每个机器拆成两个点: 编号为i的接收节点，和编号为2*i+1的产出节点（ n是机器数目），
//前者用于接收原料，后者用于提供加工后的半成品或成品。所有偶数点只进不出，所有奇数点只出不进
//这两个点之间要连一条边，容量为单位时间产量Q
//1) 添加一个虚拟原点S,S提供最初的原料 00000...  （设该点为2N）
//2) 添加一个虚拟汇点T, T接受最终的产品 11111....（设该点为2N+1）
        for (i = 0; i < N; i++) {//枚举每个节点
        //判断i，j之间有供求关系
            for (j = 0; j < N; j++) {
                if (i != j) {
                    for (k = 0; k < P; k++) {
                        if ((m[i].out[k] == 1 && m[j].in[k] == 0) || (m[i].out[k] == 0 && m[j].in[k] == 1)) {//无供求关系
                            break;
                        }
                    }
                    if (k == P) {//产出节点连边到能接受其产品的接收节点，容量无穷大
                        add_edge(2*i+1, 2*j, INF);
                    }
                }
            }
            add_edge(2*i, 2*i+1, m[i].time);//结点本身有流量限制，将结点展开成两个点，然后用流量链接一下就好
            for (k = 0; k < P; k++) {
                if (m[i].in[k] == 1) break;
            }
            if (k == P) {//如果该机器的接收零件全为0或若干个2，连接到虚拟源点S，容量为INF
                add_edge(2*N, 2*i, INF);
            }
            for (k = 0; k < P; k++) {
                if (m[i].out[k] == 0) break;
            }
            if (k == P) //如果该机器的接收零件全为1或若干个2，连接到虚拟汇点T，容量为INF
                add_edge(2*i+1, 2*N+1, INF);
        }
        vector <edge> G_origin[MAX_V];//将原图保存下来
        for (i = 0; i <= 2*N+1; i++) {
            G_origin[i] = G[i];
        }
        printf("%d ", max_flow(2*N, 2*N+1));//max_flow后，网络G变成残余网络！！
        int count = 0;
        for (i = 0; i <= 2 * N + 1; i++) {
//所有偶数点只进不出，所有奇数点只出不进，其他点都是附加点
            if (i != 2 * N && i % 2 != 0) {//源点不是虚拟源点和奇数点
                for (j = 0; j < G_origin[i].size(); j++) {
                    edge &e = G_origin[i][j];
                    if (e.to % 2 != 1 && e.to != 2 * N + 1 && e.cap > G[i][j].cap) {
                //汇点不是虚拟汇点和偶数点，并且流量比原图小，也就是添加了反向边
                        count ++;//流量发生变化的边数count（和s还有t关联的边不在其内，那些不属于原有的边，是附加边）
                    }
                }
            }
        }
        printf("%d\n", count);
        for (i = 0; i <= 2 * N + 1; i++) {
            if (i != 2 * N && i % 2 != 0) {
                for (j = 0; j < G_origin[i].size(); j++) {
                    edge &e = G_origin[i][j];
                    if (e.to % 2 != 1 && e.to != 2 * N + 1 && e.cap > G[i][j].cap) {
                        printf("%d %d %d\n", i/2+1, e.to/2+1, e.cap - G[i][j].cap);
                        //原网络流量减去残余网络流量，其实就是最终的流量选择
                    }
                }
            }
        }
    }
    return 0;
}
