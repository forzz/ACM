#include<stdio.h>
int stb[102][102];
int min(int x,int y){return x<y?x:y;}//求最小值
void Floyd(int n)  //用floyd算法求出所有结点对的最短路径
{
      int i,j,k;
      for(k=1;k<=n;k++)
          for(i=1;i<=n;i++)
              for(j=1;j<=n;j++)
                  stb[i][j]=min(stb[i][j],stb[i][k]+stb[k][j]);
}
int main()
{
    int i,j;
    int num,num1,n,dis;
    int line,ansmix,linemax;
    while(scanf("%d",&num)&&num)//输入，num为0结束
    {
        for(i=1;i<=num;i++)//数组初始化
            for(j=1;j<=num;j++)
                stb[i][j]=1000010;
        for(i=1;i<=num;i++)
        {
            scanf("%d",&num1);
            stb[i][i]=0;
            for(j=0;j<num1;j++)
            {
                scanf("%d %d",&n,&dis);
                stb[i][n]=dis;//输入数据
            }
        }
        Floyd(num);//找出每两个点的最短路径
        ansmix=1000010;
        for(i=1;i<=num;i++)
        {
            linemax=0;
            for(j=1;j<=num;j++)
            {
                /*找出所有最短路径最长的长度，也就是第i个人向其他人发出
                消息，所有人都收到消息的最短时间*/
                if(stb[i][j]>linemax)
                {
                    linemax=stb[i][j];
                }
            }
            if(linemax<ansmix)
            {
                ansmix=linemax;//找出最短时间
                line=i;//确定是哪个人
            }
        }
        if(ansmix==1000010)
            printf("disjoint\n");
        else
            printf("%d %d\n",line,ansmix);
    }
}
