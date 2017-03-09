#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXD 20 + 10
int n,m,k;
int Mat[MAXD][MAXD];   //网格
int State[21][21][21];  /*走到x，y 连穿z个墙*/
int ans;
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
void dfs(int x,int y,int step,int have_go){
    if(x == n - 1 && y == m - 1){  //到达目的地
        ans = min(ans,step);  //更新最小步数
        return ;
    }
    for(int i = 0 ; i < 4 ; i++){
        int _x = x + dir[i][0];
        int _y = y + dir[i][1];
        int st = have_go;
        if(Mat[_x][_y] == 1) st++;  //维护穿墙数
        else
        st = 0;
        if(_x >= 0 && _x < n && _y >= 0 && _y < m){   //在网格中，dfs结束条件
            if((State[_x][_y][st] < 0 || State[_x][_y][st] > step + 1) && st <= k){  //未访问且更优且合格
                State[_x][_y][st] = step + 1; //维护数据
                dfs(_x,_y,step + 1,st); //步数+1
            }
        }
    }
    return ;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(State,-1,sizeof(State));
        ans = 1 << 30;      //ans定成最大值
        scanf("%d%d%d",&n,&m,&k);
        for(int i = 0 ; i < n ; i++)
          for(int j = 0 ; j < m ; j ++)
            scanf("%d",&Mat[i][j]);
        dfs(0,0,0,0); /*从左上角出发,当前走了0步，已经连续穿过了0层墙*/
        if(ans != 1 << 30)printf("%d\n",ans); //存在结果
        else
        printf("-1\n"); //无结果
    }
    return 0;
}
