#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 100010;
struct Block
{
    int ct[10][10];
}block[400];
int _, n, m, a[N], cnt, pp[11];
void build()
{
    int tmp = (int)sqrt(n*1.0), id;
    cnt = n/tmp + 1;
    memset(block, 0, sizeof(block));
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
        id = i/cnt, tmp = a[i];
        for(int j=0; j<10; j++)
        {
            block[id].ct[j][tmp%10]++;
            tmp /= 10;
        }
    }
}

void update(int u, int v)
{
    int id = u/cnt;
    for(int i=0; i<10; i++)
    {
        block[id].ct[i][a[u]%10]--;
        a[u] /= 10;
    }
    a[u] = v;
    for(int i=0; i<10; i++)
    {
        block[id].ct[i][v%10]++;
        v /= 10;
    }
}

int query(int l, int r, int d, int p)
{
    int L = l/cnt, R = r/cnt;
    int res = 0, div = pp[d];
    if(L==R)
    {
        for(int i=l; i<=r; i++) if(a[i]/div%10==p) res++;
        return res;
    }

    for(int i=L+1; i<R; i++)
    {
        res += block[i].ct[d][p];
    }

    for(int i=l; i<(L+1)*cnt; i++)
    {
        if(a[i]/div%10==p) res++;
    }

    for(int i=R*cnt; i<=r; i++)
    {
        if(a[i]/div%10==p) res++;
    }
    return res;
}

void solve()
{
    scanf("%d%d", &n, &m);
    build();

    char str[5];
    int u, v, d, p;
    while(m--)
    {
        scanf("%s", str);
        if(str[0]=='S')
        {
            scanf("%d%d", &u, &v);
            u--;
            update(u, v);
        }
        else
        {
            scanf("%d%d%d%d", &u, &v, &d, &p);
            u--, v--, d--;
            printf("%d\n", query(u, v, d, p));
        }
    }
}

void init()
{
    pp[0] = 1;
    for(int i=1; i<10; i++) pp[i] = pp[i-1]*10;
}

int main()
{
    init();
    cin>>_;
    while(_--) solve();
    return 0;
}
