#include "cstdio"
#include "string"
#include "queue"
#include "cstring"
#include "iostream"
using namespace std;
#define maxn 55*25
#define inf 0x3f3f3f3f
struct Trie
{
    Trie *next[4],*fail;
    int cnt;
}pool[maxn],*root,*sz;//内存池 根节点 内存池尾节点
int dp[2][maxn],now,pre;
Trie *newnode()//建立新节点
{
    Trie *ret=sz++;
    memset(ret->next,0,sizeof(ret->next));//清空子节点
    ret->fail=0;
    ret->cnt=0;
    return ret;
}
int idx(char c)
{
    if(c=='A') return 0;
    if(c=='G') return 1;
    if(c=='C') return 2;
    if(c=='T') return 3;
}
void Insert(string str)//字典树加入新DNA串
{
    Trie *pos=root;
    for(int i=0;i<str.size();i++)
    {
        int c=idx(str[i]);//字符转数字
        if(!pos->next[c]) pos->next[c]=newnode();
        pos=pos->next[c];
    }
    pos->cnt++;//结尾标记为1
}
void getfail()//BFS求fail指针
{
    queue<Trie *> Q;
    for(int c=0;c<4;c++)
    {
        if(root->next[c])//压入root的所有子节点（BFS从第二层节点开始）
        {
            root->next[c]->fail=root;//对于根结点下所有的子结点，失败指针一定是指向root，在初始化的时候就已经预处理
            Q.push(root->next[c]);
        }
        else root->next[c]=root;//如果root的子节点不存在，不必维护其fail指针，将其引向root
    }
    while(!Q.empty())//BFS
    {
        Trie *x=Q.front();Q.pop();
        for(int c=0;c<4;c++)
        {
            if(x->next[c])
            {
                x->next[c]->fail=x->fail->next[c];//维护fail
                x->next[c]->cnt+=x->fail->next[c]->cnt;//根据自动机找出所有的不能出现的串的节点
                Q.push(x->next[c]);
            }
            else x->next[c]=x->fail->next[c];//如果节点子节点不存在，不必维护其fail指针，直接将其值转移到其fail指针上
        }
    }
}
void init()//建立根节点
{
    sz=pool; //reset
    root=newnode();
}
int main()
{
    ios::sync_with_stdio(false);
    int n,no=0;
    string tt;
    while(cin>>n&&n)
    {
        init();//建立根节点
        for(int i=1;i<=n;i++)//字典树中插入DNA串
        {
            cin>>tt;
            Insert(tt);
        }
        getfail();
        cin>>tt;
        int cnt=sz-pool;//总节点数
        now=0,pre=1;
        memset(dp,0x3f,sizeof(dp));
//dp[i][j]表示当前串长度为i，状态为自动机上j节点时最少改变的字符数。
        dp[now][0]=0;//dp初始边界条件
        for(int i=0;i<tt.size();i++)//i为当前的串长度（因为每个状态是由前面一个状态直接得到，可以利用滚动数组）
        {
            now^=1,pre^=1;//滚动数组
            memset(dp[now], 0x3f, sizeof(dp[now]));
            for(int j=0;j<cnt;j++)//j为当前尾结点，每位一共有tot种可能（j为树中的节点）
            {
                if(dp[pre][j]<inf)//防止重复dp
                {
                    Trie *pos=pool+j;
                    for(int k=0;k<4;k++)//向下查找其4个子节点
                    {
                        if(pos->next[k]->cnt) continue;//不能走到致病状态
                        int t=pos->next[k]-pool;//得到当前子节点在树中的编号
                        int add=idx(tt[i])==k?0:1;//如果当前结点为之前给定的串的节点，那么不用修改，否则add为1
                        dp[now][t]=min(dp[now][t],dp[pre][j]+add);//查找最小值
                    }
                }
            }
        }
        int ans=inf;
        for(int i=0;i<cnt;i++) ans=min(ans,dp[now][i]);//找到最小值
        if(ans==inf) printf("Case %d: -1\n",++no);
        else  printf("Case %d: %d\n",++no,ans);
    }
}
