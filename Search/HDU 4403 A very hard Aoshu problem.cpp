#include<stdio.h>
#include<string.h>
int cnt,flag[22],num[22],len;
char s[22];
void DFS(int id) //   “+”的位置
{
    int i,j,k;
    if(id==len-1)//已经到最后一个可以放“+”位置
    {
        int c=0,mid=0;
         for(i=0;i<len;i++) //每个数字遍历
         {
             if(flag[i]==1) ////flag[i]=1表示i后有加号
             {
                   mid=mid*10+s[i]-'0';
                   num[c++]=mid;
                   mid=0;
             }
             else
             {
                 mid=mid*10+s[i]-'0';
             }
         }
         if(mid!=0)  num[c++]=mid;//最后一个数
         int left=0,right=0; //等号左边和右边
         for(k=0;k<c;k++)   //判断当前组合能否构成相等，k为分界点
         {
             left=right=0;
             for(i=0;i<=k;i++) left+=num[i];
             for(i=k+1;i<c;i++) right+=num[i];
             if(left==right) cnt++;
         }
         return;

    }
    flag[id]=1;
    DFS(id+1);
    flag[id]=0;
    DFS(id+1);
}
int main()
{
    while(scanf("%s",s)!=EOF)
    {
        if(strcmp(s,"END")==0) break;
        len=strlen(s);
        memset(flag,0,sizeof(flag));
        cnt=0;
        DFS(0);
        printf("%d\n",cnt);
    }
    return 0;
}
