# include<iostream>
# include<cstdio>
# include<cstring>
# include<algorithm>
using namespace std;
int vis[10];
char mp[8][15],p1[8][15];
bool judge() //是否符合原图
{
    for(int i=0;i<5;++i)
        for(int j=0;j<9;++j)
            if(mp[i][j]!=p1[i][j])
                return false;
    return true;
}
bool dfs(int step)
{
    if(judge())
        return true;
    if(step>=6)
        return false;
    char p2[6][10];
    for(int i=0;i<5;++i)    //初始化p2为p1，备份当前图形状态
        for(int j=0;j<9;++j)
            p2[i][j]=p1[i][j];

    for(int i=0;i<9;++i){//9种摆放形式
        if(vis[i])
            continue;
        vis[i]=1;
        int r=i/3,c=2*(i%3)+1; //左上角横的坐标
        p1[r][c]=p1[r][c+2]=p1[r+2][c]=p1[r+2][c+2]='_';//四条横边
        p1[r+1][c-1]=p1[r+2][c-1]=p1[r+1][c+3]=p1[r+2][c+3]='|'; //4条竖边,比横边靠外
        p1[r+1][c]=p1[r+1][c+1]=p1[r+1][c+2]=p1[r+2][c+1]=' ';
        if(dfs(step+1))//5个图形都dfs
            return true;

        vis[i]=0; //恢复状态
        for(int i=0;i<5;++i)
            for(int j=0;j<9;++j)
                p1[i][j]=p2[i][j];
    }

    return false;
}

int main()
{
    int cas=0;
    while(1)
    {
        for(int i=0;i<5;++i){ //读入5行
            gets(mp[i]);
            if(mp[i][0]=='0')
                return 0;
        }
        printf("Case %d: ",++cas);
        for(int i=0;i<5;++i)//6个图形 9种摆放
            for(int j=0;j<9;++j)
                p1[i][j]=' ';
        memset(vis,0,sizeof(vis));//初始化vis数组
        if(dfs(0))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
