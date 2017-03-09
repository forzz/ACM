/*
求最大流的过程，就是不断找到一条源到汇的路径，然后构建残余网络，再在残余网络上寻找新的路径，使总流量增加，然后形成
新的残余网络，再寻找新路径…..直到某个残余网络上找不到从源到汇的路径为止，最大流就算出来了。
每次寻找新流量并构造新残余网络的过程，就叫做寻找流量的“增广路径”，也叫“增广”
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <deque>
#include<cstring>
using namespace std;
#define INFINITE 999999999
int G[300][300];
bool Visited[300];
int Layer[300]; int n,m; //1是源点， m是汇点
bool CountLayer() {//一个节点的“层”数，就是源点到它最少要经过的边数。（生成残余网络后，一些边的流量已为0）
//前面在分层时，只要进行到汇点的层次数被算出即可停止，因为按照该BFS的规则，和汇点同层或更下一层的节点，是不可能走到汇点的。
//当残余网络的分层操作无法算出汇点的层次（即BFS到达不了汇点）时，算法结束，最大流求出
    int layer = 0; deque<int>q;
    memset(Layer,0xff,sizeof(Layer)); //都初始化成-1
    Layer[1] = 0; q.push_back(1);
    while( ! q.empty()) {
        int v = q.front();
        q.pop_front();
        for( int j = 1; j <= m; j ++ ) {//枚举每个边
            if( G[v][j] > 0 && Layer[j] == -1 ) {
                //Layer[j] == -1 说明j还没有访问过
                Layer[j] = Layer[v] + 1;
                if( j == m ) //分层到汇点即可
                    return true;
                else
                    q.push_back(j);
            }
        }
    }
    return false;
}int Dinic()
{
    int i; int s;
    int nMaxFlow = 0;
    deque<int> q; //DFS用的栈，这样就能从栈中提取出增广路径
    while( CountLayer() ) { //DFS结束后，对残余网络再次进行分层，然后再进行BFS
        q.push_back(1); //源点入栈
        memset(Visited,0,sizeof(Visited)); Visited[1] = 1;
        while( !q.empty()) {
            int nd = q.back();
            if( nd == m ) { // nd是汇点
//BFS过程中，要是碰到了汇点，则说明找到了一条增广路径。此时要增加总流量的值，（BFS自带最短路性质）
//消减路径上各边的容量，并添加反向边，即所谓的进行增广。
                //在栈中找容量最小边
                int nMinC = INFINITE;
                int nMinC_vs; //容量最小边的起点（确定该增广路径的最大流量）
                for( i = 1;i < q.size(); i ++ ) {//遍历栈内所有元素，记录容量最小的边
                    int vs = q[i-1];
                    int ve = q[i];
                    if( G[vs][ve] > 0 ) {
                        if( nMinC > G[vs][ve] ) {
                            nMinC = G[vs][ve];
                            nMinC_vs = vs;
                        }
                    }
                }//增广，改图，构建新的残余网络
                nMaxFlow += nMinC;
                for( i = 1;i < q.size(); i ++ ) {
                    int vs = q[i-1];
                    int ve = q[i];
                    G[vs][ve] -= nMinC; //修改边容量
                    G[ve][vs] += nMinC; //添加反向边
                }
//BFS找到一条增广路径后，并不立即结束，而是回溯后继续BFS寻找下一个增广路径。
//回溯到的节点u满足以下条件：
//1) BFS搜索树的树边(u,v)上的容量已经变成0。即刚刚找到的增广路径上所增加的流量，等于(u,v)本次增广前的
//   容量。 (BFS的过程中，是从u走到更下层的v的)
//2)u是满足条件 1)的最上层的节点
                while( !q.empty() && q.back() != nMinC_vs ) {//退栈到 nMinC_vs成为栈顶，以便继续BFS
                    Visited[q.back()] = 0;//把退栈的点重新设为未访问点
                    q.pop_back();
                }
            }
            else { //nd不是汇点
                for( i = 1;i <= m; i ++ ) {
                    if( G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&! Visited[i]) {
                        //只往下一层的没有走过的节点走
                        Visited[i] = 1;
                        q.push_back(i);
                        break;
                    }
                }
                if( i > m) //找不到下一个点，回溯
                q.pop_back();
            }
        }
    }
    return nMaxFlow;
}
int main()
{
    while (cin >> n >> m ) {
        int i,j,k;
        int s,e,c;
        memset( G,0,sizeof(G));
        for( i = 0;i < n;i ++ ) {
            cin >> s >> e >> c;
            G[s][e] += c; //两点之间可能有多条边
        }
        cout << Dinic() << endl;
    }
    return 0;
}
