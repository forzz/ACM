#include<iostream>
#include<algorithm>
#include<stdio.h>
#define maxn (100005)//数列长度最大值
#define LL long long
using namespace std;
struct node{
    int ch[3];//每个节点最多有2个子节点，还有一个保存权值
    void init()//初始化，在这道题里没什么用，但是多组数据的话就有用了
    {
        ch[0]=0;
        ch[1]=0;
    }
}tr[maxn*50];//开字典树
//用 long long 因为最大有10^12，大概是2的四十次方左右，但因为这只是单个数的值加以来后可能会更大
//所以就选择2的50次方，那么就开一个有50层的字典树，(10的3次方是2的10次方）
int tot,n;
LL ans,pre[maxn],nex[maxn],a[maxn];//pre前缀  nex后缀
void add(LL x)//往字典树中加一个值
{
    int now=0,p=0;
    for (int i=50;i>=0;i--)
    {
        if ((1LL<<i)&x) p=1;//（1<< x）这个运算是只能在int范围内，要在long long范围内时需写成 （1long long<< x ）
        else p=0;
        if (!tr[now].ch[p])//该节点不存在
        tot++,tr[now].ch[p]=tot,tr[tot].init();//开新节点
        now=tr[now].ch[p];//下一层
    }
}
LL solve(LL x)//找到最优序列，在字典树中和前缀对比（一个for循环）
{
    LL tmp=0;
    int now=0,p=0;
    for (int i=50;i>=0;i--)
    {
        if ((1LL<<i)&x) p=0;//因为树中已经保存了前缀和，若x为1，找该层是否有0
        else p=1;
        if (tr[now].ch[p]) tmp+=(1LL<<i);//如果存在相反的数，那么结果中该位为1
        else p^=1;//不存在相反的数，把该位还原为后缀的真实数字，也就是前缀的当前数字
        now=tr[now].ch[p];//继续对比前缀的下一位
    }
    return tmp;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        pre[i]=pre[i-1]^a[i];//保存前缀异或和 [0,0]表示前缀为空
    }
    for (int i=n;i>=1;i--)
    nex[i]=nex[i+1]^a[i];//保存后缀异或和 [n+1,n+1]表示为后缀为空
    for (int i=1;i<=n+1;i++)//枚举每个数字，以该数字为分界线划分前缀（定前缀讨论后缀）
    {
        add(pre[i-1]);
//把前缀异或和放入字典树（不需要每次清空树，因为add过程是独立的，而在每一次add后都有查询，就算查询的不是当前pre，也是之前的pre，符合题设）
        ans=max(ans,solve(nex[i]));//多次比较取最优（选取最大后缀异或和的一部分作为最优后缀异或和）
    }
    printf("%lld\n",ans);
}
