#include <bits/stdc++.h>
using namespace std;
struct dot{
    double x, y, r;
}all[1024];
int n, vis[1024], ok;
double in, out;

void DFS(int u)
{
    if(!ok) return;
    vis[u] = 1;     //已访问
    if(all[u].y - all[u].r <= 0) {ok = 0; return;} //到达下界限
    for(int v = 0; v < n; ++v)   //再扫描v
        if(!vis[v] && hypot(all[u].x - all[v].x, all[u].y - all[v].y) < all[u].r + all[v].r)
        //如果没访问到v并且uv代表的圆相交
        /*
原型：extern float hypot(float x, float y);
用法：#include <math.h>
功能：对于给定的直角三角形的两个直角边，求其斜边的长度。
说明：返回斜边值。
        */
            DFS(v);
    if(all[u].x - all[u].r <= 0) //u圆与左边界相交
        in = min(in, all[u].y - sqrt(all[u].r * all[u].r - all[u].x * all[u].x));   //左上相交处
    if(all[u].x + all[u].r >= 1000)    //u圆与右边界相交
        out = min(out, all[u].y - sqrt(all[u].r * all[u].r - (1000-all[u].x) * (1000-all[u].x)));
}                                            //右上相交处

int main()
{
    ios::sync_with_stdio(false);
    while(memset(vis, 0, sizeof(vis)), ok = 1, in = out = 1000, cin >> n){ //in和out初始化
        for(int i = 0; i < n; ++i)
            cin >> all[i].x >> all[i].y >> all[i].r;
        for(int i = 0; i < n; ++i)
            if(!vis[i] && all[i].y + all[i].r >= 1000)//i没访问且包含上界限
                DFS(i);
        if(!ok) puts("IMPOSSIBLE");
        else printf("%.2f %.2f %.2f %.2f\n", 0.0, in, 1000.0, out);
    }
    return 0;
}
