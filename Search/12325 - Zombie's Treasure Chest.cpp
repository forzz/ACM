#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
int main()
{
    int t,n,s1,v1,s2,v2;
    scanf("%d",&t);
    for(int tt=1; tt<=t; tt++)
    {
        //输入体积为n的箱子，和宝物1的体积、价值以及宝物2的体积、价值。
        scanf("%d%d%d%d%d",&n,&s1,&v1,&s2,&v2);
        //性价比=价/量
        if(s1>s2)
        {
            swap(s1,s2);
            swap(v1,v2);
        }
        printf("Case #%d: ",tt);
/*
此时s2肯定是比s1大的，但若如此n/s2都大于65536的话，说明不管是枚举宝物1还是宝物2的时间复杂度都是很大的！
int和long都是4个字节，长度，65536的二进制表示是:1111,1111,1111,1111,
65536 * 65536的二进制表示是:1111,1111,1111,1111,1111,1111,1111,1111，
long是有符号的，所以65536 * 65536的有符号表示就是0。
*/
        ll value=0;
        if(n/s2>=65536)   //当n/s1和n/s2都非常大的时候
        {
            for(ll i=0; i<=s1; i++)//宝物2从0到s1遍历
                value=max(value,v2*i+(n-i*s2)/s1*v1);
            for(ll i=0; i<=s2; i++)//宝物1从0到s2遍历
                value=max(value,v1*i+(n-i*s1)/s2*v2);
        }
        else//因为数据交换的原因，s2要大些，所以n/s2要小些，此时枚举宝物2的个数
        {
            for(ll i=0; s2*i<=n; i++)
            value=max(value,v2*i+(n-s2*i)/s1*v1);
        }
        printf("%lld\n",value);
    }
    return 0;
}
