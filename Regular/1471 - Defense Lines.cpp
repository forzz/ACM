#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 200000
int t,n,a[maxn],f[maxn],g[maxn],d[maxn],ans;
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++) scanf("%d",a+i);
        a[n]=-inf;
        for(int l=0,r=0;r<n;r++)
        {
            if(a[r+1]<=a[r]){
                for(int i=l;i<=r;i++) f[i]=r-i+1,g[i]=i-l+1;
                    /*这句代码写的好！*/
                l=r+1;
            }
        }
        memset(d,inf,sizeof(d));
        ans=0;


        for(int i=0;i<n;i++)
        {
            int j=lower_bound(d+1,d+n+1,a[i])-d-1;
            ans = max(ans,f[i]+j);
            d[g[i]]=min(d[g[i]],a[i]);
        }
        /*看不懂了*/


        printf("%d\n",ans);
    }
    return 0;
}
