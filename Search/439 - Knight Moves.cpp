#include<stdio.h>
#include<string.h>
int a[10][10],qx[100],qy[100],vis[10][10];
int dx[]={-2,-2,-1,1,2,2,1,-1};
int dy[]={-1,1,2,2,1,-1,-2,-2};
char b1[5],b2[5];
int main()
{
    int i,j,k,ux,uy,vx,vy,front,rear,x,y,newx,newy;
    while(scanf("%s%s",b1,b2)!=EOF)
    {
        ux=b1[1]-'1';
        uy=b1[0]-'a';
        vx=b2[1]-'1';
        vy=b2[0]-'a';
        front=rear=0; //初始化队列指针
        memset(vis,-1,sizeof(vis));
        vis[ux][uy]=0; //起点步数为0
        qx[rear]=ux; //队列末尾压入起点
        qy[rear]=uy;
        rear++;
        while(front<rear)
        {
            x=qx[front];
            y=qy[front];
            if(x==vx&&y==vy)
                break;
            front++;
            for(i=0;i<8;i++)
            {
                newx=x+dx[i];
                newy=y+dy[i];
                if(vis[newx][newy]<0&&newx>=0&&newx<8&&newy>=0&&newy<8) //保证在棋盘中并且第一次访问
                {
                    vis[newx][newy]=vis[x][y]+1; //步数
                    qx[rear]=newx;
                    qy[rear]=newy;
                    rear++;
                }
            }
        }
        printf("To get from %s to %s takes %d knight moves.\n",b1,b2,vis[vx][vy]);
    }
    return 0;
}
