#include<iostream>
#include<stdio.h>
using namespace std;
const int maxn=100005;
int n,m,d,cnt,num,ans,sta,a[1<<21],k[maxn],fal[1<<21];
int main(void)
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=0;i<m;i++)//有m个集合
    {
        scanf("%d",&cnt);//集合数字个数
        while(cnt--)
        {
            scanf("%d",&num);
            k[num]=i;  //k数组保存每个数字的编号
        }
    }
    ans=m+1;
    for(int i=1;i<d;i++) //1到d   a数组代表某个集合中包含的数字个数
        a[k[i]]++;
    for(int i=d;i<=n;i++)//d到n  数组不断滚动，遍历每一种可能
    {
        if(i>d)a[k[i-d]]--;//数组滚动
        a[k[i]]++;sta=0;
        for(int j=0;j<m;j++)     //每个集合遍历
            if(!a[j])sta|=(1<<j);  //a[j]为0时 sta集合组中加入集合j  找到最大补集
                fal[sta]=1;  //标记最大补集组
    }
    for(int i=(1<<m)-1;i>=0;i--)  //二进制保存集合状态
    {//如果对于某个区间，某个集合组的数全部不存在于该区间，这个集合组以及这个集合组的子集一定都不满足条件。
        if(fal[i])//该集合组不符合状态
        {
            for(int j=0;j<m;j++)  //每个集合遍历
            if(i & (1<<j))    fal[i^(1<<j)]=1;  //所有子集合全部不满足条件
        }
        else//符合状态，计算当前集合组包含多少个集合，更新结果
        {
            cnt=0;
            for(int j=0;j<m;j++)
                if(i & (1<<j))cnt++;
            ans=min(ans,cnt);
        }
    }
    printf("%d\n",ans);
    return 0;
}
