#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int F,N,M,W;
const int INF = 1 << 30;
struct Edge {
    int e,w;
    Edge(int ee,int ww):e(ee),w(ww) { }
};
vector<Edge> G[1000]; //整个有向图
int updateTimes[1000]; //最短路的改进次数
int dist[1000]; //dist[i]是源到i的目前最短路长度
int Spfa(int v) {
    for( int i = 1; i <= N; ++i)//初始化所有边到源的最短距离
        dist[i] = INF;
    dist[v] = 0;//源点
    queue<int> que; que.push(v);
    memset(updateTimes ,0,sizeof(updateTimes));
    while( !que.empty()) {
        int s = que.front();
        que.pop();
        for( int i = 0;i < G[s].size(); ++i) {//枚举s的所有邻边
            int e = G[s][i].e;
            if( dist[e] > dist[s] + G[s][i].w ) {
                dist[e] = dist[s] + G[s][i].w;
//由于S到e的最短距离变小了，有可能e可以改进其它的点，所以若u不在队列中，就将它放入队尾。
                que.push(e);
                ++updateTimes[e];//维护改进次数
                if( updateTimes[e] >= N) return true;//若一个点最短路被改进的次数达到n ，则有负权环
            }
        }
    }
    return false;
}
int main(){
    cin >> F;
    while( F--) {
        cin >> N >> M >> W;
        for( int i = 1; i <1000; ++i)//清空vector
            G[i].clear();
        int s,e,t;
        for( int i = 0; i < M; ++ i) {//正权边（双向）
            cin >> s >> e >> t;
            G[s].push_back(Edge(e,t));
            G[e].push_back(Edge(s,t));
        }
        for( int i = 0;i < W; ++i) {//负权边（单向）
            cin >> s >> e >> t;
            G[s].push_back(Edge(e,-t));
        }
        if( Spfa(1))
            cout << "YES" <<endl;
        else cout << "NO" <<endl;
    }
}
