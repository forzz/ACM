#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#define Max 4010
#define INF 0x3f3f3f3f
using namespace std;
int Long[Max],Next[202];
char ch[Max][202];
struct snode{//字符串放入结构体中，就可以用sort进行整体排序
    char ch3[202];
}chtemp[Max];
bool cmp(struct snode a,struct snode b)
{
    int temp=strcmp(a.ch3,b.ch3);
    if(temp>=0)
        return 0;
    return 1;
}
void Get_next(char ch1[],int Tlen)//对匹配串进行预处理
{
    int i=0,j=-1;       //i表示模板字符串下标（下标为0时无字符），j表示当前最大前后缀长度（由于nxt数组是从0开始，所以j表示最大前缀的下一位）
    Next[0]=-1;
    while(i<Tlen)
    {
        if(j==-1||ch1[j]==ch1[i])
        {
            i++; j++;
            Next[i]=j;
        }
        else
            j=Next[j];
    }
}

int Kmp(char ch1[],int ii,int Tlen)     //ii为当前主串，ch1为匹配串  Tlen为匹配串长度  匹配过程中主串不进行移动，匹配串移动
{
    int i=-1,j=-1;//与求nxt不同，i初始化为-1，因为j初始化为-1 实际是从i=0开始，i只增加，不回退     i和j表示当前主串匹配串的失配位
    while(i<Long[ii]&&j<Tlen)
    {
        if(j==-1||ch1[j]==ch[ii][i])//会出现j退回到首字符的前一位-1，这时i与匹配串的任何一个字符都不相等，需要把i++
        {
            i++; j++;
        }
        else
            j=Next[j];
    }
    if(j>=Tlen)//找到ii中的ch1子串
        return 1;
    return 0;
}

int main()
{
    char ch1[202];
    int min,mini,i,j,j1,j2,temp,n,m,k,pd,pdi,End;
    while(scanf("%d",&n)!=EOF&&n)
    {
        min=INF;        //min保存最短行长度
        memset(ch,0,sizeof(ch));
        for(i=1;i<=n;i++)
        {
            scanf("%s",ch[i]);
            temp=strlen(ch[i]);
            Long[i]=temp;       //long数组保存每行长度
            if(temp<min)
                min=temp,mini=i;
        }
        for(i=Long[mini],pd=0,m=0;i>=1;i--)
        {
            End=Long[mini]-i;
            for(j=0;j<=End;j++)//i为字符串长度，j为起点，暴力枚举min字符串的所有子串
            {
                memset(ch1,0,sizeof(ch1));
                for(j1=j,j2=0;j2<i;j2++,j1++)   //把ch中从j到i+j的字符串复制到ch1
                {
                    ch1[j2]=ch[mini][j1];//
                }
                ch1[j2]='\0';//补0，使之前保存在ch1中的数据无效
                memset(Next,0,sizeof(Next));
                Get_next(ch1,i);//求每个匹配串的next数组
                for(j1=1,k=1;j1<=n;j1++)//暴力枚举
                {
                    if(j1==mini)
                        continue;
                    if(Kmp(ch1,j1,i))
                    {
                        k++;
                    }
                    else
                        break;
                }
                if(k==n)//找到符合子串，存入chtemp
                {
                    strcpy(chtemp[m++].ch3,ch1);
                    pd=1;
                    pdi=i;
                }
            }
            if(pd==1)//输出字典序最小的子串
            {
                sort(chtemp,chtemp+m,cmp);
                printf("%s\n",chtemp[0].ch3);
                break;
            }
        }
        if(pd==0)
            printf("IDENTITY LOST\n");
    }
    return 0;
}

