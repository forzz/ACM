#include <cstdio>
#include<cstring>
int n = 0, c[33000];
int level[16000];
int lowbit(int x)
{
    return x&(-x);
}
void add (int x)     //x+1    x处增加一颗星星
{
    for(int i=x;i<=33000;i+=lowbit(i))
    {
        c[i]++;
    }
}
int sum(int x)
{
    int s = 0;
    for(int i=x;i>0;i-=lowbit(i))
    {
        s += c[i];
    }
    return s;
}
int main()
{
    int i = 0, x = 0, y = 0;
    while(~scanf("%d",&n))
    {
        memset(level, 0, sizeof(level));
        memset(c, 0, sizeof(c));
        for(i = 0; i<n; i++)
        {
            scanf("%d %d", &x, &y);//y已排好序，不需要考虑y，只考虑x
            x++;          //因为树状数组处理的时候，不能处理0
            level[sum(x)]++;//查找在x之前的星星总数，确定等级
            add(x);//x放入数组
        }
        for(i = 0; i<n; i++)
            printf("%d\n",level[i]);
    }
    return 0;
}
