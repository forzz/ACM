#include<stdio.h>
#define M 100010
struct node{//用于邻接表
    int v,w,next;//v是终点，w是权值，next是和这条边同一起点的另一条边
}edge[M<<1];
struct trie{//字典树，子节点只有0和1
    int next[2];
}t[M<<8];
int e,L;//标记edge和t已用到的位置
int head[M];//为结点的邻接表的头指针
int visit[M];//标记数组
int value[M];//各结点到结点0的异或长度
void AddEdge(int u,int v,int w)//正向反向一共2条边
{

    edge[e].v=v;edge[e].w=w;edge[e].next=head[u];head[u]=e++;//用头插法将边的编号插入u的邻接表中
    edge[e].v=u;edge[e].w=w;edge[e].next=head[v];head[v]=e++;//用头插法将边的编号插入v的邻接表中（尾插法需要多使用一个尾节点变量）
}
void dfs(int x,int w)
//求出所有节点到根节点的路径的总异或长度，若求两点之间的异或，只需要将预处理的异或值异或就行（因为是一棵树，两者多余的边相同）
{
    value[x]=w;//结点0到结点x的异或长度
    visit[x]=1;//标记已访问结点
    int a;
    for(a=head[x];a;a=edge[a].next){//遍历从a出发的所有边
        if(visit[edge[a].v])continue;//如果访问过，继续访问其他结点
        dfs(edge[a].v,w^edge[a].w);//如果未访问过，访问此结点邻接表中的边
    }
}
void Insert(int num)//从最高位按位插入直到到最低位，目标是找最大值，优先选择最高位最大的异或值
{
    int i,a,p=0;
    for(i=30;i>=0;i--){//从二进制的第31位到第1位存储num信息，位运算1<<31会溢出
        a=num&(1<<i)?1:0;//获得num的二进制数的第i+1位上的数字
        if(!t[p].next[a]){//如果未开空间
            t[p].next[a]=++L;//给其静态分配空间
            t[L].next[0]=t[L].next[1]=0;//初始化新分配的空间
        }
        p=t[p].next[a];//指针后移，进入下一层
    }
}
int find(int num)//只要存在和num相异的数位，就可以通过异或将这位取出来加入到最优解中
{
    int i,a,p=0,w=0;
    for(i=30;i>=0;i--){//从二进制的第31位到第1位查找最大异或值
        a=num&(1<<i)?0:1;//获取num的二进制数的第i+1位上的数字的非
        if(t[p].next[a]){//如果字典树有要查找的数
            w|=1<<i;//加上该位的权值
            p=t[p].next[a];//进入下一层
        }
        else p=t[p].next[!a];//如果没有，则按num当前位上的数字进入下一层查找
    }
    return w;
}
int main()
{//求树中的最长异或长度，可以把树中的所有节点的异或信息全部利用，不只是两个节点之间求异或值
    int i,u,v,w,n;
    while(~scanf("%d",&n)){
        e=L=1;//初始化邻接表与字典树所用的数组
        for(i=0;i<n;i++)head[i]=visit[i]=0;//清空邻接表和初始化结点访问情况（标记为未访问）
        for(i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);//将边加入邻接表中,
        }
        dfs(0,0);//递归查找结点0到各结点的异或长度
//利用字典树求n个数之间的异或最大值
        t[0].next[0]=t[0].next[1]=0;//初始化字典树的头结点
        for(w=i=0;i<n;i++){//每insert一次，就find一次，不要把insert和find放到两个循环里，避免重复贪心。
            Insert(value[i]);//将0到i的异或长度插入字典树
            u=find(value[i]);//查找字典树中已存长度与0到i的异或长度异或后的最大值
            if(w<u)w=u;//如果取得新的最大值，则更新当前最长异或路径
        }
        printf("%d\n",w);//输出最长异或路径
    }
    return 0;
}
