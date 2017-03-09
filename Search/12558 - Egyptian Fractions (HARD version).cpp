#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
typedef long long LL;
const int maxn=10010;
int maxd,t,tt;
set<LL> sk;
LL ans[maxn],v[maxn];
LL gcd(LL a,LL b){
    return b?gcd(b,a%b):a;
}
LL get_first(LL a,LL b){//满足  1/c <= a/b 的最小c
    return b/a+1;
}
bool better(int d){//深度为d时判断
    for(int i=d;i>=0;--i)
        if(v[i]!=ans[i]) return ans[i]==-1||v[i]<ans[i];
        //没有此位或者该位分母更小（都是更优情况）
    return false;
}
bool dfs(int d,LL from,LL a,LL b){
    if(d==maxd){//到达深度上限
        if(b%a) return false; //分子必须为1，单位分数
        v[d]=b;
        if(sk.count(b)) return false;
        if(better(d)) memcpy(ans,v,sizeof(LL)*(d+1));  //维护最优解，d从0开始，需要+1
        return true;
    }
    bool ok=false;
    for(LL i=max(from,get_first(a,b));;++i){ //枚举的起点
        if(b*(maxd+1-d)<=i*a) break;
//剪枝：如果剩下的maxd+1-d 个分数全部都是 1/i ，加起来仍然不超过aa/bb，则无解
        if(sk.count(i)) continue; //禁止列表中
        v[d]=i; //更新解
        //计算 aa/bb - 1/i ，设结果为 a2/b2
        LL b2=b*i;
        LL a2=a*i-b;
        LL g=gcd(a2,b2);
        if(dfs(d+1,i+1,a2/g,b2/g)) ok=true;
    }
    return ok;
}
int main(){
    scanf("%d",&t);
    while(t--){
        LL a,b,k,sk0;
        sk.clear(); //禁止集合
        scanf("%lld%lld%lld",&a,&b,&k);
        while(k--) scanf("%lld",&sk0),sk.insert(sk0);
        for(maxd=0;;++maxd){ //迭代加深搜索
            memset(ans,-1,sizeof(ans));
            if(dfs(0,get_first(a,b),a,b)) break;//第一个返回的就是最优解
        }
        printf("Case %d: %lld/%lld=",++tt,a,b);
        for(int i=0;i<=maxd;++i){
            if(i) printf("+");
            printf("1/%lld",ans[i]);
        }
        printf("\n");
    }
    return 0;
}
