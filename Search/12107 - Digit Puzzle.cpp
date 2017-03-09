#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
char s[3][6];//因数与积
char change[11] = {'*','0','1','2','3','4','5','6','7','8','9'};//*指代空格 只有11种字符
int len[3],maxd;
int check_result() //判断积是否正确
{
    char check_str[10];
    char ss[10];
    int t0=0,t1=0,t2;
    for(int i=0;i<len[0];i++)  //t0
        t0=t0*10+s[0][i]-'0';
    for(int i=0;i<len[1];i++)  //t1
        t1=t1*10+s[1][i]-'0';
    t2=t0*t1;                  //t2
    for(int i=0;i<len[2];i++)  //t2转化为字符串形式
    {
        check_str[len[2]-i-1]=t2%10+'0';
        t2/=10;
    }
    if(t2!=0||check_str[0]=='0')return 0;//t2不存在或者t2位数大于积
    for(int i=0;i<len[2];i++)
        if(check_str[i]!=s[2][i]&&s[2][i]!='*')return 0;
    return 1;
}
int check(int a,int b)//a代表第几组 b代表第几个数
{
    int flag=0;   //flag只有在为1的时候才算是唯一解，可以被判断是成功的
    if(a==2)
        {return check_result();}  //到达第二组，可以进行判断 成功返回1
    int ta,tb;
    char ch=s[a][b];  //备份s[a][b]
    if(b==len[a]-1){  //当前数组枚举完毕
        ta=a+1;
        tb=0;
    }else{            //数组枚举未完毕
        ta=a;
        tb=b+1;
    }
    if(s[a][b]=='*'){//需要填数的空格
        for(int i=1;i<=10;i++)
        {
            if(b==0&&i==1)continue;   //忽略前导0
            s[a][b]=change[i];
            flag+=check(ta,tb);   //每一个check函数都会返回flag，确保flag不丢失
            if(flag>1)
                break;//多解时直接剪枝,不再次填数
        }
    }else{
        flag+=check(ta,tb);
    }
    s[a][b]=ch;   //恢复状态
    return flag;
}
int dfs(int a,int b,int d) //a代表从第几组开始枚举 b代表是从第几个数开始枚举
{
    int flag;  //标志，判断是否成功
    if(d==maxd){
        if(check(0,0)==1)   return 1;  //仅有一个解
        else return 0;
    }
    if(a==3)return 0;//枚举完毕
    int ta,tb;
    char tmp=s[a][b];
    if(b==len[a]-1){//当前组枚举完毕，下一组
        ta=a+1;
        tb=0;
    }else{  //当前组枚举未完毕，下个数
        ta=a;
        tb=b+1;
    }
    for(int i=0;i<=10;i++)
    {
        if(b==0&&i==1)continue;//忽略前导0
        if(tmp==change[i]){
            s[a][b]=tmp;
            flag=dfs(ta,tb,d);//相同不做更改
        }else{
            s[a][b]=change[i];
            flag=dfs(ta,tb,d+1);//不同深度增加
        }
        if(flag)break;//找到解
    }
    if(!flag)s[a][b]=tmp;//没有找到解，恢复原样。
    return flag;
}
int main()
{
    int kase=0;
    memset(s,0,sizeof(s));
    while(scanf("%s%s%s",s[0],s[1],s[2])==3)
    {
        for(int i=0;i<3;i++)len[i]=strlen(s[i]);//每个因数的长度
        printf("Case %d: ",++kase);
        for(maxd=0;;maxd++){
            if(dfs(0,0,0)){
                printf("%s %s %s\n",s[0],s[1],s[2]);
                break;
            }
        }
        memset(s,0,sizeof(s));
    }
    return 0;
}
