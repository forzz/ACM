#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int mod=1e9+7;
int len;
LL n,k;
LL c[45][45];
struct matrix{
    LL m[100][100];
}mc;
matrix multi(matrix a,matrix b){ //矩阵乘法
    matrix ans;
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            ans.m[i][j]=0;
            for(int k=0;k<len;k++){
                ans.m[i][j]=(ans.m[i][j]+a.m[i][k]*b.m[k][j]%mod)%mod;
            }
        }
    }
    return ans;
}
matrix quick(matrix a, LL n){//矩阵a^n
    matrix ans,t=a;
    for(int i=0;i<=40;i++)
        ans.m[i][i]=1;
    while(n>0){
        if(n&1) ans=multi(ans,t);//矩阵相乘
        t=multi(t,t);
        n>>=1;
    }
    return ans;
}
int main()
{
    c[0][0]=1;
    c[1][0]=c[1][1]=1;
    for(int i=2;i<=40;i++){   //构造组合数c   k最大为40
        for(int j=0;j<=i;j++){
            if(j==0 || j==i) c[i][j]=1;
            else  c[i][j]=c[i-1][j-1]+c[i-1][j];
        }
    }
    while(cin>>n>>k){
        memset(mc.m,0,sizeof(mc.m));  //构造矩阵
        len=2*k+3;//最后矩阵的总列数
        mc.m[0][0]=1;
        for(int j=0;j<=k;j++){  //第一行
            mc.m[0][j+1]=c[k][j];
            mc.m[0][j+k+2]=c[k][j];
        }
        mc.m[1][1]=mc.m[1][k+2]=1; //第2到k+1行
        for(int i=1;i<=k;i++){
            for(int j=0;j<=i;j++){
                mc.m[i+1][j+1]=c[i][j];
                mc.m[i+1][j+k+2]=c[i][j];
            }
        }
        mc.m[k+2][1]=1;
        for(int i=1;i<=k;i++){
            for(int j=0;j<=i;j++){
                mc.m[i+k+2][j+1]=c[i][j];
            }
        }
        mc=quick(mc,n-1);
        LL ans=0;
        for(int i=0;i<len;i++){//求和
            ans=(ans+mc.m[0][i]%mod)%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
