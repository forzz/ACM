#include<bits/stdc++.h>
using namespace std;
const int maxw = 16;
const int maxn = 150;//14*14*3/4+2 149
int s[3];
int t[3];
int w,h,n;
char maze[maxw][maxw+1];
int deg[maxn],G[maxn][5];//抽出底图，每个节点最多只有5种移动方式
inline bool conflict(int a1,int b1,int a2,int b2){ //两者目标位置重合或者换位置
//内联扩展是用来消除函数调用时的时间开销。它通常用于频繁执行的函数。 一个小内存空间的函数非常受益。
    return a1 == a2 || (a1 == b2 && a2 == b1);
}
int vis1[maxn][maxn][maxn];
int vis2[maxn][maxn][maxn];
typedef vector<int> VINT;
VINT v1;
VINT v2;
VINT v3;
typedef VINT * PV;
inline int Hash(int a,int b,int c) {return a<<16|b<<8|c;}//把三个ghost的位置状态压缩成一个数字（abc小于256）
int dBfs()                            //但是注意重时不能直接用Hash掉的值来判断vis，因为Hash以后数字范围很大
{
    v1.clear();v2.clear();v3.clear();
    memset(vis1,-1,sizeof(vis1));
    memset(vis2,-1,sizeof(vis2));
    PV q1 = &v1,q2 = &v2,nxt = &v3;
    int (*d1)[maxn][maxn] = vis1, (*d2)[maxn][maxn] = vis2;
    d1[s[0]][s[1]][s[2]] = 0;   //起点
    d2[t[0]][t[1]][t[2]] = 0;   //终点
    q1->push_back(Hash(s[0],s[1],s[2]));
    q2->push_back(Hash(t[0],t[1],t[2]));
    while(q1->size()&&q2->size()){ //双向BFS避免单向BFS步数太多产生的组合性爆炸的情况
        if(q1->size()>q2->size()) swap(q1,q2),swap(d1,d2);  //当一个方向的组合更多时 直接交换q和d
        for(int ii = 0,sz = q1->size(); ii < sz; ii++){//起点BFS
            int u = (*q1)[ii];  //取出起点
            int a = u>>16, b = (u>>8)&0xff, c = u&0xff;  //取出后八位
            for(int i = 0; i < deg[a]; i++){
                int a1 = G[a][i];                //a的目标点
                for(int j = 0; j < deg[b]; j++){
                    int b1 = G[b][j];            //b的目标点
                    if(conflict(a1,a,b1,b)) continue;
                    for(int k = 0; k < deg[c]; k++){
                        int c1 = G[c][k];
                        if(conflict(c1,c,a1,a)||conflict(c1,c,b1,b)||~d1[a1][b1][c1]) continue;
                    //矛盾或者该状态已存在，直接跳过
                        d1[a1][b1][c1] = d1[a][b][c]+1;  //步数更新
                        if(~d2[a1][b1][c1])
/*
在C语言里不等于0就表示真。~的意思是把数据的各个二进制位反转。如果scanf返回值为0，
那~scanf(...)就是~0，是一个二进制位全部为1的数，在C里当然表示真；如果scanf返回值为1，那~scanf(...)就是~1，
是一个只有最后一个二进制位为0其余二进制位全部为1的数，在C里同样表示真。不论输入正确与否都为真，
循环都会继续，因此~scanf(...)不能用于表示没有正确输入。 只有在scanf返回EOF，是个所有二进制位都为1的数，
这时~scanf(...)就是~EOF，是一个所有二进制位都为0的数，也就是0，
表示假，这时候循环才会结束。
*/
                                { return d1[a1][b1][c1]+d2[a1][b1][c1]; }
                        nxt->push_back(Hash(a1,b1,c1));//压入vector
                    }
                }
            }
        }
        q1->clear();
        swap(nxt,q1);
    }

    return -1;
}
void init()
{
    int cnt = 0;
    int id[maxw][maxw];
    const int dx[] = {-1, 1, 0, 0, 0};
    const int dy[] = { 0, 0,-1, 1, 0};
    int x[maxn];
    int y[maxn];

    for(int i = 0; i < h; i++)
    for(int j = 0; j < w; j++) {
        char ch = maze[i][j];
        if(ch != '#'){//把位置坐标二元组编号成一个数cnt
            x[cnt] = i; y[cnt] = j;  id[i][j] = cnt;
            if('A'<= ch && ch <= 'C') t[ch-'A'] = cnt; //终点
            else if('a' <= ch && ch <= 'c') s[ch-'a'] = cnt;//起点
            cnt++; //非障碍格数
            }
        }
    for(int i = 0; i < cnt; i++){
        deg[i] = 0;  //deg记录节点i转移状态的个数
         for(int k = 0; k < 5; k++) {
/*
预处理， 枚举5^3的状态然后判断合不合法，由于题目说了有很多墙壁，实际上没有那么多要转移的状态那么
可以把底图抽出来，然后3个ghost在上面跑到时候就不必判断了，减少了两次无用的枚举。
*/
            int nx = x[i]+dx[k], ny = y[i]+dy[k]; //更新坐标
            if(maze[nx][ny] != '#')
                G[i][deg[i]++] = id[nx][ny];//抽出底图
        }
    }
    //结点没有3个时增加冗余点，起点为cnt 终点为cnt++ 都是不存在的点
    if(n<=2) {deg[cnt] = 1; G[cnt][0] = cnt; s[2] = t[2] = cnt++; }
    if(n<=1) {deg[cnt] = 1; G[cnt][0] = cnt; s[1] = t[1] = cnt++; }
}
int main()
{
    while(~scanf("%d",&w)&&w) {   //判断是否读入
        scanf("%d%d\n",&h,&n);
        for(int i = 0; i < h; i++)
            gets(maze[i]);//G[i-1]  //读入迷宫
            init();
            int ans = dBfs();
            printf("%d\n",ans);
    }
    return 0;
}
