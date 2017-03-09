#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>
#include <climits>
using namespace std;
const int MAX = 1003;
const int dirx[5] = {0,0,1,0,-1};   //右下左上
const int diry[5] = {0,1,0,-1,0};
bool visit[MAX][MAX];
int map[MAX][MAX];
int wan[MAX][MAX];
int n,m,bx,by;
bool mark;//全局变量，一旦为1代表找到合法解
void dfs(int x,int y,int cnt,int dir){ //dir表示当前方向，cnt表示转弯数
	int i,tx,ty;
	if(mark)return;
	if(x<1 || y<1 || x>n || y>m || cnt>2)return;
	//注意下面几个剪枝的顺序，顺序搞错了就会出错，因为最后一个元素非0
	if(x==bx && y==by){   //到达目的地
		mark = true;
		return;
	}
	if(map[x][y]!=0)return;
	if(wan[x][y]!=-1 && wan[x][y]<=cnt)return; //之前已访问并且
	wan[x][y] = cnt;  //转弯数
	for(i=1;i<=4;++i){
		tx = x + dirx[i];
		ty = y + diry[i];
		if(dir!=i){//当前方向与之前不同
			dfs(tx,ty,cnt+1,i);
		}
		else{
			dfs(tx,ty,cnt,i);
		}
	}
}
int main(){
	int i,j,t,ax,ay;
	while(scanf("%d %d",&n,&m)!=EOF){
		if(n==0 && m==0)break;
		for(i=1;i<=n;++i){
			for(j=1;j<=m;++j){
				scanf("%d",&map[i][j]);
			}
		}
		scanf("%d",&t);
		while(t--){
			memset(wan,-1,sizeof(wan));
			scanf("%d %d %d %d",&ax,&ay,&bx,&by);
			mark = false;
			if(map[ax][ay]!=map[bx][by] || map[ax][ay]==0){
				printf("NO\n");
				continue;
			}
			wan[ax][ay] = 0;
			for(i=1;i<=4;++i){
				dfs(ax+dirx[i],ay+diry[i],0,i);
			}
			if(mark){
				printf("YES\n");
			}else{
				printf("NO\n");
			}
		}
	}

    return 0;
}
