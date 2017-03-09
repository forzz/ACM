#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MAXN 100+10
#define INF (1<<30)
#define mod 123456789
struct now{
    int p; // 每袋价格
    int h; // 每袋的重量
    int c; // 袋数
};
int main (){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d%d",&n,&m);
        now s[MAXN];
        for(int i = 1; i <= m; i++)
            scanf("%d%d%d",&s[i].p,&s[i].h,&s[i].c);//s保存每种大米的信息
        LL d[4000] = {0};
        for(int i = 1; i <= m; i++){//每种米遍历
/*
某种米的价钱与数量的乘积大于钱数时，代表该种米是足量的，可以用多完全背包解，
当小于钱数时，代表该种米时不足够的，那么我们只能用01背包选择哪袋米选还是不选
*/
            if(s[i].c*s[i].p >= n){ //完全背包(顺序)
                for(int k = s[i].p; k <= n; k++) //n为钱数
                    d[k] = max(d[k],d[k-s[i].p]+s[i].h);
            }
            else{  //01背包（二进制优化） 除了完全背包，其他第二重循环都是逆序
                int j;
                for(j = 1; j <= s[i].c/2; j = (j<<1)){ //c表示袋数，j把c按照二进制拆分（1，2，4……）合并成另外一种大米
                    for(int k = n; k >= s[i].p*j; k--){
                            d[k] = max(d[k-s[i].p*j]+s[i].h*j,d[k]);
                    }
                }
                int x = s[i].c+1-j;//剩余袋数的大米也看成一种大米
                for(int k = n; k >= s[i].p*x; k--){
                        d[k] = max(d[k-s[i].p*x]+s[i].h*x,d[k]);
                }
            }
        }
        LL ma = 0;
        for(int i = n; i >= 0; i--)//钱可以不花完
            ma = max(ma,d[i]);
        printf("%lld\n",ma);
    }
    return 0;
}
