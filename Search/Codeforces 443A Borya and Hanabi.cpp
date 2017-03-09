#include <cstdio>
#include <algorithm>
using namespace std;
int n,i,j,k,r,a[111],b[111],x[111],c[1111];
char s[7];
int main()
{
    while(~scanf("%d",&n)) //a[i]表示花色    b[i]表示牌号
    {
        for (i=0; i<n; i++)
        {
            scanf("%s",s);
            if (s[0]=='R')
                a[i]=0;
            if (s[0]=='G')
                a[i]=1;
            if (s[0]=='B')
                a[i]=2;
            if (s[0]=='Y')
                a[i]=3;
            if (s[0]=='W')
                a[i]=4;
            b[i]=s[1]-'1';
        }
        for (r=10, i=0; i<(1<<10); i++)
//暴力枚举需要问的花色和数字，用i的二进制位上是否为1来表示（前5位是牌号，后5位是花色），时间复杂度为2^10,然后枚举两两判断是否可以被区分
        {
            if(i)
                c[i]=c[i/2]+(i&1);//c[i]表示枚举i时询问的次数（上一次+1）
            for(j=0; j<n; j++)//遍历每一张牌
            {
                x[j]=0;
                if((i>>a[j])&1) //该牌的花色被询问
                    x[j]|=1<<a[j];  //x[j]表示第j张牌该花色已知
                if((i>>(b[j]+5))&1) //该牌的牌号被询问
                    x[j]|=1<<(b[j]+5);//该牌号已知
                for(k=0; k<j; k++)//遍历之前已访问过的牌（每张牌都要和其他所有牌比较，直接放到循环中更好）
                    if (x[j]==x[k] && (a[j]!=a[k] || b[j]!=b[k]))
                    //无法区分k牌和j牌
                        break;
                if (k<j)//无法全部区分前j张牌
                    break;
            }
            if(j==n)//所有牌都可被区分
                r=min(r,c[i]); //维护最小值
        }
        printf("%d\n",r);
    }
    return 0;
}
