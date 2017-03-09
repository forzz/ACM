#include<cstdio>
#include<cstring>
int max(int a,int b){return a>b?a:b;}
int dp[100][60][60];//dp[i][r1][j]:遍历到第i行，前一行状态为r1，当前状态为j的最大结果
int st[60];//每种状态的二进制数
int sum[60];//每种状态的炮塔数
int col[100];//按列存放每一行1(指高地)的分布
int cnt;//合法状态总数
char s[10];
bool J(int x)
{//判断状态是否合法(每两个1中间至少有2个0)
	if(x&(x<<1))return 0;
	if(x&(x<<2))return 0;
	return 1;
}
int getSum(int x){//获得状态x下所安置的炮塔数(即求x有多少个二进制位1)
	int res=0;
	while(x){
		if(x&1)res++;
		x>>=1;
	}
	return res;
}
void pre(int m){//预处理出所有合法状态及该状态下炮塔数
	int i,e=1<<m;  //e是最大值
	cnt=0;//标记活动总个数
	for(i=0;i<e;i++){ //遍历每种可能
		if(J(i))st[cnt]=i,sum[cnt++]=getSum(i);//记录每种可能存入st中
	}
}
int main(){
	int n,m,i,j,r1,r2;
	while(~scanf("%d%d",&n,&m)){    //n行m列
		pre(m);
		memset(col,0,sizeof(col));
		for(i=0;i<n;i++){//从0行0列开始
			scanf("%s",s);
			for(j=0;j<m;j++)if(s[j]=='H')col[i]|=(1<<j);  //直接将输入数据处理
		}
		memset(dp,-1,sizeof(dp));
		for(i=0;i<cnt;i++) //枚举每种可行状态
                        if(!(col[0]&st[i]))//该种状态满足第0行平原位置
                                dp[0][0][i]=sum[i];//第0行
		for(i=1;i<n;i++){//枚举每行（dp有3维，4重for循环）
			for(j=0;j<cnt;j++)//当前行状态(高地与当前状态不冲突)（不在记录范围）
			if(!(col[i]&st[j]))
			{
				for(r1=0;r1<cnt;r1++)//前一行状态(与当前状态不冲突)
				if(!(st[j]&st[r1]))
				{
					for(r2=0;r2<cnt;r2++)//前二行状态(与当前状态不冲突)
					if(!(st[j]&st[r2]))
					{
						if(dp[i-1][r2][r1]!=-1)
						dp[i][r1][j]=max(dp[i][r1][j],dp[i-1][r2][r1]+sum[j]);
					}
				}
			}
		}
		int ans=0;
		for(i=0;i<cnt;i++)
                        for(j=0;j<cnt;j++)
                                ans=max(ans,dp[n-1][i][j]);
		printf("%d\n",ans);
	}
	return 0;
}
