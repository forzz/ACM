#include<cstring>
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long ll;
int n,m;
int a[10]={6,2,5,5,4,5,6,3,7,6};//每个数字需要的木棒数
ll dp[510][2][2][2];//dp[num][rc][b][c] num表示当前使用木棒数 rc表示是否有进位 b表示B已经到最高位，c表示C已经到最高位
int dfs(int num,int cr,int b,int c){
    //有低位到高位进行DFS，低位对高位的影响只在于当前位的B+C会引起A进位。
    //A - B = C 可以转化成 B + C = A
	if(num>n)//木棒使用超过总数，边界条件
		return 0;
	if(dp[num][cr][b][c]!=-1)//记忆化搜索
		return dp[num][cr][b][c];
	if(b==1&&c==1){ //两个加数都已经到最高位，不再继续DFS，到达边界
		if(num==n&&cr==0)  //当前位没有进位且木棒正好消耗完，符合条件
			return 1;
		if(num+a[1]==n&&cr==1) //有进位，剩余的火柴数刚好等于进位"1"，也符合条件。
			return 1;
		return 0;
	}
	if(num==n)   //火柴已经用完，又不符合上面的判别条件
		return 0;
	dp[num][cr][b][c]=0;//符合条件，进行dfs
	if(b==0){
		if(c==0){
			for(int i=0;i<10;i++){
				for(int j=0;j<10;j++){
					int t=a[i]+a[j]+a[(i+j+cr)%10];//当前位BCA所需要的木棒总数（算上上一位造成的进位）
					dp[num][cr][b][c]+=dfs(num+t,(i+j+cr)/10,0,0);
					if(i!=0)//假设b已经到达最高位（排除前导0）
						dp[num][cr][b][c]+=dfs(num+t,(i+j+cr)/10,1,0);
					if(j!=0)//假设c已经到达最高位
						dp[num][cr][b][c]+=dfs(num+t,(i+j+cr)/10,0,1);
					if(i!=0&&j!=0)//假设b和c都到达最高位
						dp[num][cr][b][c]+=dfs(num+t,(i+j+cr)/10,1,1);
					dp[num][cr][b][c]%=m;
				}
			}
		}
		else{//c已经到最高位，只枚举B
			for(int i=0;i<10;i++){
				int t=a[i]+a[(i+cr)%10];
				dp[num][cr][b][c]+=dfs(num+t,(i+cr)/10,0,1);
				if(i!=0)
					dp[num][cr][b][c]+=dfs(num+t,(i+cr)/10,1,1);
			}
		}
	}
	else{
		if(c==0){//B已经到最高位，只枚举C
			for(int i=0;i<10;i++){
				int t=a[i]+a[(i+cr)%10];
				dp[num][cr][b][c]+=dfs(num+t,(i+cr)/10,1,0);
				if(i!=0)
					dp[num][cr][b][c]+=dfs(num+t,(i+cr)/10,1,1);
			}
		}
	}
	return dp[num][cr][b][c]%=m;
}
int main(){
	int T;
	scanf("%d",&T);
	for(int cs=1;cs<=T;cs++){
		cin>>n>>m;
		n-=3;//减去-和=所用的木棒数
		memset(dp,-1,sizeof(dp));
		printf("Case #%d: %d\n",cs,dfs(0,0,0,0));
	}
}

