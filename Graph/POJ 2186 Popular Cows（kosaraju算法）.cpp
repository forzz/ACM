#include<cstdio>
#include<cstring>
#include<iostream>
#define M 10005 //结点的最大数
using namespace std;
struct node{
    int to,next;
}edge1[M*10],edge2[M*10];
int mark1[M],mark2[M],head1[M],head2[M];
int tot1,tot2;
int cnt1,st[M],cnt2,belong[M];//belong当前顶点属于哪个集合，相当于染色，当前顶点被染成了什么颜色
int num,setNum[M];
struct nn{
    int l,r;
}e[M*10];
void add(int a,int b){ //头插法保存图
    edge1[tot1].to=b, edge1[tot1].next=head1[a], head1[a]=tot1++;//邻接表存的原图
    edge2[tot2].to=a, edge2[tot2].next=head2[b], head2[b]=tot2++;//邻接表存的逆图
}
void DFS1(int x) {//深度优先遍历G，后序遍历算出每个结点u的结束时间st[u],起点如何选择无所谓。（拓补排序）
    mark1[x]=1;
    for(int i=head1[x]; i!=-1; i=edge1[i].next) //正向
        if(!mark1[edge1[i].to]) DFS1(edge1[i].to);
    st[cnt1++]=x;//st数组是按照完成时间从小到大排序的，越接近搜索树的叶子，顶点标号越小。
}
void DFS2(int x) {
    mark2[x]=1;
    num++;
    belong[x]=cnt2; //记录点x所属连通分量的编号为cnt2（染色）
    for(int i=head2[x]; i!=-1; i=edge2[i].next) //逆向
        if(!mark2[edge2[i].to]) DFS2(edge2[i].to);
}
int main() {
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF){
//每个强连通分量缩成一点，则形成一个有向无环图DAG。
//缩点的时候不一定要构造新图，只要把不同强连通分量的点染不同颜色，然后考察各种颜色
//的点有没有连到别的颜色的边即可(即其对应的缩点后的DAG图上的点是否有出边）。
        tot1=tot2=0;
        for(int i=0; i<n; i++){//初始化
        {
            head1[i]=head2[i]=-1;
            mark1[i]=mark2[i]=0;
        }
        for(int i=0; i<m; i++){
            int w,v;
            scanf("%d%d",&w,&v);
            w--, v--; //结点从0开始编号
            e[i].l=w; e[i].r=v;
            add(w,v);//建立邻接表
        }
        cnt1=cnt2=0;
        for(int i=0; i<n; i++){//无向图可能不是一个连通图，而是由多个连同分量组成
            if(!mark1[i]) DFS1(i);
        }
        for(int i=cnt1-1; i>=0; i--){
//深度优先遍历G的转置图GT，选择遍历的起点时，按照节点的结束时间从大到小进行。遍历的过程中，一边遍历，
//一边给节点做分类标记（相当于染色，一遍DFS遍历到的所有节点染成相同的颜色）每找到一个新的起点，分类标记值就加1。
            if(!mark2[ st[i] ]) {
                num=0;
                DFS2(st[i]);
                setNum[cnt2++]=num;//记录每个强连通分支包含的顶点数
            }
        }
        int de[M];//转化为DAG以后的每个缩点的出度
        memset(de,0,sizeof(de));//计算各个DAG图的出度
        for(int i=0; i<m; i++){
            if(belong[ e[i].l ] != belong[ e[i].r ])//如果两者不是一点（强连通分支看作一点）
                de[ belong[e[i].l] ]++;//出度增加
        }
//有向无环图中唯一出度为0的点，一定可以由任何点出发均可达(由于无环，所以从任何点出发往前走，必然终止于一个出度为0的点)
//那么该点所代表的连通分量上的所有的原图中的点，都能被原图中的所有点可达，则该连通分量的点数，就是答案。
        int cnt=0,res;
        for(int i=0; i<cnt2; i++){
            if(!de[i]) {//查找出度为0的点，记下编号和存在该点的个数
                cnt++;  res=i;
            }
        }
        if(cnt>1) printf("0\n");//DAG上面如果有不止一个出度为0的点，则这些点互相不可达，原问题无解，答案为0
        else printf("%d\n",setNum[res]);
    }
    return 0;
}
/*
根据深搜和回溯来标示节点的开始与结束时间故可以推出以下的性质：
1.所有比一个结点X的结束时间小的节点都是在原图中节点X能到达的节点
2.如果逆图中X能到达某一个节点Y,说明原图中节点Y能到达X.
3.节点X结束时间最大说明：X是一个子树的根，否则X的结束时间不是最大的，其根的时间要比它还大。
4.根的所有子树节点的结束时间处在其结束时间之前。
5.所有比节点X的结束时间大的节点是节点X不能到达的，所以先处理大的结束时间就避免了转置图中所有X能到达的没
被访问过的节点在原图中是X能到的。要是X不能到肯定结束时间比X的大已经被处理。
*/
