#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long int LL;
const int maxn=1100;
LL dpr[maxn*maxn],dpc[maxn*maxn];
LL col[maxn],row[maxn];
LL a[maxn][maxn];
priority_queue<LL> qc,qr;
int n,m,k; LL p;
int main()
{
    scanf("%d%d%d%I64d",&n,&m,&k,&p);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%lld",&a[i][j]);
            col[j]+=a[i][j];
            row[i]+=a[i][j];
        }
    }
    for(int i=0;i<n;i++)
        qr.push(row[i]);
    for(int i=0;i<m;i++)
        qc.push(col[i]);
    dpr[0]=dpc[0]=0;
    for(int i=1;i<=k;i++)
    {
        LL cc=qc.top(); qc.pop();
        LL rr=qr.top(); qr.pop();
        dpr[i]=dpr[i-1]+rr;
        dpc[i]=dpc[i-1]+cc;
        qc.push(cc-p*n);
        qr.push(rr-p*m);
    }
    LL ans=dpr[0]+dpc[k];
    for(int i=1;i<=k;i++)
        ans=max(ans,dpr[i]+dpc[k-i]-1LL*i*(k-i)*p);
    printf("%lld",ans);
    return 0;
}
