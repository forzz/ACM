#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define FOR_CELL(c,p) for(auto c=(p).begin();c!=(p).end();++c)
using namespace std;
struct Cell  //定义单元格
{
    int x,y;
    Cell(int x=0,int y=0):x(x),y(y){};
    bool operator < (const Cell& rhs) const {
        return x < rhs.x||(x==rhs.x&&y<rhs.y);//由于要使用set，必须对单元格定义大小关系
    }
};
typedef set<Cell> Polyomino;  //定义连通块
const int maxn=10;
set<Polyomino> poly[maxn+1];//连通块集合，poly[i]表示所有的i连通块构成的集合
int ans[maxn+1][maxn+1][maxn+1];//打表，ans[w][h]表示w*h网格中的n连通块的个数
const int dx[]={-1,1,0,0};
const int dy[]={0,0,-1,1};
inline Polyomino normalize(const Polyomino &p){
/*
对于平移操作，我们可以定义一个normalize函数，找出x,y分别的最小值minX,minY，
那么它可以视为一个平移矢量(minX,minY)，将连通块的每个单元格都减去该矢量，即实现了标准化。
*/
    int minX=p.begin()->x, minY = p.begin()->y;
    FOR_CELL(c,p){
        minX = min(minX, c->x);
        minY = min(minY, c->y);
    }
    Polyomino p2;
    FOR_CELL(c,p)
        p2.insert(Cell(c->x-minX,c->y-minY));
    return p2;
}
inline Polyomino rotate(const Polyomino &p)//旋转操作，对一个连通块顺时针旋转90度，并标准化
//对于旋转操作，只需要将每个格子都顺时针旋转90度即可。相应的几何变换为(x,y)->(y,-x)。
{
    Polyomino p2;
    FOR_CELL(c,p)
    p2.insert(Cell(c->y,-c->x));
    return normalize(p2);//注意：此处一定要先旋转，再标准化！
}
inline Polyomino flip(const Polyomino&p)//翻转操作，对一个连通块沿x轴翻转，并标准化
/*对于翻转操作，由于既可以沿x轴翻转，也可以沿y轴翻转，但实际上沿x轴翻转后再绕坐标原点顺时针旋转180度
即可得到沿y轴翻转的图案。因此这里我们定义一个flip函数，表示将一个连通块沿x轴翻转。相应的几何变换为(x,y)->(x,-y)。
*/
{
    Polyomino p2;
    FOR_CELL(c,p)
    p2.insert(Cell(c->x,-c->y));
    return normalize(p2);
}
void check_polyomino(const Polyomino& p0, const Cell& c)
////判断重复性，如果p0+c构成的连通块不重复，则加入到集合中
{
    Polyomino p = p0;
    p.insert(c);
    p=normalize(p);
    int n=p.size();
    for(int i=0;i<4;i++){//4次旋转
        if(poly[n].count(p)!=0) return; //存在重复联通块
        p=rotate(p);
    }
    p=flip(p); //翻转
    for(int i=0;i<4;i++){
        if(poly[n].count(p)!=0) return ;
        p=rotate(p);
    }
    poly[n].insert(p);//添加新联通块
}
void generate(){
    Polyomino s;
    s.insert(Cell(0,0));
    poly[1].insert(s);//放进第一个
//生成所有的n连通块
    for(int n=2;n<=maxn;n++){//枚举每个n连通块集合
        for(auto p=poly[n-1].begin();p!=poly[n-1].end();++p)//枚举每个n连通块
            FOR_CELL(c,*p)//枚举一个n连通块的每个单元格
            for(int dir=0;dir<4;dir++){//枚举4个方向，看能否扩展
                Cell news(c->x+dx[dir],c->y+dy[dir]);
                if(p->count(news)==0) check_polyomino(*p,news);
            }
    }
//打表
    for(int n=1;n<=maxn;n++)
    for(int w=1;w<=maxn;w++)
    for(int h=1;h<=maxn;h++){
        int cnt=0;
        for(auto p=poly[n].begin();p!=poly[n].end();++p){
            int maxX=0,maxY=0;
            FOR_CELL(c,*p){//寻找当前的连通块的最大的x，y
                maxX=max(maxX,c->x);
                maxY=max(maxY,c->y);
            }
            if(min(maxX,maxY)<min(h,w)&&max(maxX,maxY)<max(h,w))//能够放入w*h网格内的条件
                ++cnt;
        }
        ans[n][w][h]=cnt;
    }
}
int main()
/*
首先将当前的连通块平移到坐标原点，每次都顺时针旋转90度，检查是否和当前的n连通块集合中出现的有重复。
如果均没有，将该连通块沿x轴翻转后，再依次顺时针旋转90度判断，如果均没有,加入到n连通块所在的集合中即可。
*/
{
    generate();
    int n,w,h;
    while(scanf("%d%d%d",&n,&w,&h)==3){
        printf("%d\n",ans[n][w][h]);
    }
    return 0;
}
