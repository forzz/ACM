#include<cstdio>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;
int gcd(int a,int b)//欧几里得
{
    return b? gcd(b, a % b) : a;
}
int n,st[17][120000];
void init(){//动态规划预处理ST表
    for(int i=1; i<17; ++i){//区间长度（2的倍数）  放在外面
        for(int j=1; j<=n; ++j){//区间起点，放在里面
            if(j+(1<<i)-1>n) continue;
            st[i][j]=gcd(st[i-1][j],st[i-1][j+(1<<i-1)]);
        }
    }
}
int logs[120000];
int query(int a,int b){//已知左右端点求其区间GCD
    int k=logs[b-a+1];
    return gcd(st[k][a],st[k][b-(1<<k)+1]);
}

int main(){
    //用RMQ即可搞定，因为GCD跟Min Max是一种极性，都是不增函数，每次最少除以二，一个数就可以代表整个区间的最值
    for(int i=1; i<=100000; ++i){//预处理log2值
        logs[i]=log2(i)+1e-6;//保证非负
    }
    int t;
    scanf("%d",&t);//t次
    for(int cse=1; cse<=t; ++cse){
        scanf("%d",&n);//n个数
        for(int i=1; i<=n; ++i){//读取每个数，放入st表中作为初始值
            scanf("%d",&st[0][i]);
        }
        init();//预处理ST表，考虑固定左端点，最多就nlogn种GCD，可以直接把所有区间GCD值预处理出来
        map<int,long long> rec;//用map存储各种GCD值的个数，查询时直接输出。
        for(int i=1; i<=n; ++i){
//枚举左端点 i 从1-n，对每个i，二分右端点，计算每种gcd值的数量，因为左端点固定，gcd值随着右端点往右，呈现单调不增，而且gcd值每次变化，至少除以2，
            int g=st[0][i],j=i;
            while(j<=n){
                int l=j,r=n;//j在二分查找中不会改变
                while(l<r){//进行若干次二分查找，看以端点i为首的区间GCD值最多能延伸到哪儿（第一个区间GCD不是g的点l）。
                    int mid=l+r+1>>1;//移位符比二目运算符优先级低
                    if(query(i,mid)==g) l=mid;//如果左边区间GCD为g，再找延伸更远的地方
                    else r=mid-1;//继续查找左边
                }//l为GCD延伸最远处
                rec[g]+=(l-j+1);//因为gcd单调不增 区间内数字个数就是gcd为g的区间数
                j=l+1;//下一个右端点
                g=query(i,j);//g成为新的gcd值，再次循环

            }
        }
        printf("Case #%d:\n",cse);
        int q,a,b;
        scanf("%d",&q);
        while(q--){
            scanf("%d%d",&a,&b);
            int g=query(a,b);//求得区间GCD
            printf("%d %lld\n",g,rec[g]);
        }
    }
    return 0;
}
//double比float 精绝度要高     精确到小数点6位
//等于0关系：  fabs(i)<=1e-6
//大于0关系：  i>1e-6
//小于0关系：  i<1e-6
