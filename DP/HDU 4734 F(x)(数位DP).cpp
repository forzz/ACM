#include<cstdio>
#include<cstring>
#define maxn 16
int dp[maxn][111111];
int d[maxn];
int n;
long long tt;
long long  dfs(int len ,int pre ,bool fp)　//dfs过程中当深搜的边界，发现len < 0，pre >=0 的时候就返回1.
{
    if(pre<0)return 0;//说明上一层枚举的数超过了上限,没有可用的情况（dfs边界）
    if(!len)return 1;//说明上一层是个位，已经递归到底层，找到一个符合条件的数（dfs边界）
    if(!fp&&dp[len][pre]!=-1)return dp[len][pre];//记忆化搜索
    int fpmax=fp?d[len]:9;//取该位取值的最大值
    int ret=0;
    for(int i=0;i<=fpmax;i++){//从最大长度向下,每一个长度的所有取值都要遍历到,
        //一旦该位的取值不是紧贴最大值,fp就false.
        ret+= dfs(len-1,pre-i*(1<<(len-1)),fp&&i==fpmax);
    }
    if(!fp)dp[len][pre]=ret;//dp[len][j]表示len位的数{x}中F(x)小于pre的数的个数.
    return ret;
}
long long  calc(long long a)        //d保存a的每一位
{
    int len=0;
    memset(d,0,sizeof(d));
    while(a){
        d[++len]=a%10;
        a/=10;
    }
    return dfs(len,tt,true);//dfs(len, pre, flag)表示求长度为len，不超过pre的所有符合条件的值。其中flag是用来控制边界的
}
int get(int x)      //求出fx
{
    int tmp=1;
    int ans=0;
    while(x){
        ans+=(x%10)*tmp;
        x/=10;
        tmp<<=1;
    }
    return ans;
}
int main()
{
    long long  a,b;
    int nc;
    scanf("%d",&nc);
    int d=1;
    memset(dp,-1,sizeof(dp));//dp[i][j]的值不用每次都初始化，因为它的值不受输入的影响，如果前面算过了就直接拿来用，没算过就拿来算并记录下来
    while(nc--){
        scanf("%lld%lld",&a,&b);
        tt=get(a);
        printf("Case #%d: %lld\n",d++,calc(b));
    }
    return 0;
}
