#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
struct CNode {
    int k; //有向边的终点
    int w; //权值，或当前k到源点的距离
};
bool operator < ( const CNode & d1, const CNode & d2 )
{ return d1.w > d2.w; } //priority_queue默认队首是最大的元素
priority_queue<CNode> pq;
bool bUsed[30010]={0};
vector<vector<CNode> > v; //v是整个图的邻接表
    const unsigned int INFINITE = 100000000;
int main()
{
    int N,M,a,b,c;
    int i,j,k;
    CNode p;
    scanf("%d%d", & N, & M );
    v.clear();
    v.resize(N+1);//初始化vector
    memset( bUsed,0,sizeof(bUsed));
    for( i = 1;i <= M; i ++ ) {
        scanf("%d%d%d", & a, & b, & c);
        p.k = b;
        p.w = c;
        v[a].push_back( p);
    }
    p.k = 1; //源点是1号点，终点就是源点1
    p.w = 0; //1号点到自己的距离是0
    pq.push (p);//将源点到自己的边放入，使优先队列可以工作
        while( !pq.empty ()) {//优先队列维护源点到已访问过的点和上一次新增的节点的最短路，每次只取最短的路径
            p = pq.top ();
            pq.pop();//直接弹出，只用一次
            if( bUsed[p.k]) //已经求出了最短路（原点到该结点）
                continue;
            bUsed[p.k] = true;//标记当前终点，放入已求出最短路的点集合中
            if( p.k == N ) //因只要求求1-N的最短路，所以要break，此时已找到答案
                break;
            for( i = 0, j = v[p.k].size(); i < j; i ++ ) {//枚举终点的邻接点
                CNode q; q.k = v[p.k][i].k;//建立新的边（当前终点到其邻接点）
                if( bUsed[q.k] ) continue;
                q.w = p.w + v[p.k][i].w ;//从源点到该点的路径长度是上一条边的长度加上当前边的长度
                pq.push (q); //队列里面已经有q.k点也没关系：先出优先队列的一定是距离最小的那个结点。
            }
        }
    printf("%d", p.w ) ;
    return 0;
}
