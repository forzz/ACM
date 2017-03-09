#include<stdio.h>
int fa[50005]={0};
int rank[50005]={0};
int n;
void initial()
{
    for(int i=1;i<=n;i++)
    {
        fa[i]=i; rank[i]=0;//初始化每个节点的父亲都是自己，并且自己和根节点是同类
    }
}
int Find(int x)//找寻父节点+路径压缩
{
    if(x==fa[x])  return x;
    int oldfa = fa[x];
    fa[x]=Find(fa[x]);//更新其父点节与根点节的关系
    rank[x]=(rank[x]+rank[oldfa])%3;  //向量法递归求每个节点到祖先的向量（只有0 1 2三种情况，而且三种情况可以互相转化）（偏序关系：自反对称传递）
    return fa[x];
}
void Union(int r,int x,int y)
{
    int fx,fy;
    fx=Find(x); fy=Find(y);
    if(fx==fy) return;
    fa[fx]=fy;
    rank[fx]=(rank[y]+r-rank[x]+3)%3;   // 这里同样可以用向量来推公式。另外需要注意的是，这里只更新了fx的rank值，而fx的儿子的rank值都没有更新会不会有问题。其实不碍事，由于我们每次输入一组数据我们都对x和y进行了Find的操作（x>n || y>n ……)的除外。在执行Find的操作时，在回溯的过程中就会把fx的儿子的rank值都更新了。
    return ;
}
int istrue(int d,int x,int y)//d为当前语句的含义 d-1为定义中的关系
{
    int fx,fy,r;
    if(x>n || y>n || ((x==y)&&(d==2)) )//当前的话中X或Y比N大，就是假话； 当前的话表示X吃X，就是假话； x和y大于n，就是假话
        return 0;
    fx=Find(x); fy=Find(y);
    if(fx!=fy)  return 1;//共父节点才能判断出关系，暂且判断为真话
    else
    {
        if(rank[x]==((d-1)+rank[y])%3) return 1; //f（x，y）表示当前指令
 //这个公式可以用向量来推：如果（ f(x,y) + f(y,father[y]））% 3 == f(x,father[x]) 则是正确的，否则是错的。
 //这个形式可以用向量来表示，就是判断这个向量加法对不对   x--->y + y---> fx(fy) 是否等于  x--->fx(fy)
        else  return 0;
    }
}
int main()
{
    int k,i,x,y,d; int ans=0;
    scanf("%d%d",&n,&k);//n个动物 k句话
    initial();
    for(i=1;i<=k;i++)
    {
        scanf("%d%d%d",&d,&x,&y);
        if( !istrue(d,x,y) )//判断是否为真
            ans++;
        else//加入集合
            Union(d-1,x,y);
    }
    printf("%d\n",ans);
    return 0;
}

