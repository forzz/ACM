#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxa=1<<6;
int n,m,maxm,ans,s[maxa],dp[45][maxa][maxa];
bool check(int sta1,int sta2,int sta3)  //sta1表示当前行  sta2表示上一行 sta3表示下一行
//在状态转移判断某些状态能否转移过来只需要判断中间那一行能否恢复成初始状态即可（因为未改变的时候sta1就是初始状态）
{
    return ((sta1 | (sta1<<1) | (sta1>>1) | sta2 | sta3) & (maxm-1))==(maxm-1);//模拟左右上下四个方向移动（按位或中只要有1个状态为1，结果就为1）
    //& (maxm-1))==(maxm-1)是因为之前进行左移操作，数可能比max还大。
}
int cal(int x)   //记录x各位含有1的总个数（1代表空位）
{
    int r=0;
    while(x)
    {
        if(x&1)r++;
        x>>=1;
    }
    return m-r;
}
int main(void)
{//dp[i][sta][stb]=max(dp[i-1][stc][sta]+s[sta],dp[i][sta][stb])  蜘蛛一步可以上下左右走，也可以停在原地（每一行的状态与上下都有关系）
 //sta表示当前行（第i行）的状态，stb表示下一行（第i+1行）的状态，stc在dp方程中表示了上一行（第i-1行）的状态
    scanf("%d%d",&n,&m);
    if(m>n)swap(m,n);//较大为n
    maxm=(1<<m);//状态hash（maxm-1是全空状态）
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<maxm;i++)//初始化边界（第0行）
    {
        dp[0][0][i]=0;
        s[i]=cal(i);
    }
    for(int i=1;i<=n;i++)  //当前行遍历
        for(int j=0;j<maxm;j++)  //上一行状态
            for(int k=0;k<maxm;k++)   //当前行状态
                if(dp[i-1][j][k]!=-1)    //i-1行存在状态(i-1行是j  i+1行是k)
                    for(int l=0;l<maxm;l++) //下一行状态
                    if(check(k,j,l))   //i行 i-1行 i+1行
                        dp[i][k][l]=max(dp[i][k][l],dp[i-1][j][k]+s[k]);
    for(int i=0;i<maxm;i++)//n行所有状态（下一行全是0）
        ans=max(ans,dp[n][i][0]);
    printf("%d\n",ans);
    return 0;
}
