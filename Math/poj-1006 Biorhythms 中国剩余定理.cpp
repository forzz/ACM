#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

int a[4], m[4];

void extend_Euclid(int a, int b, int &x, int &y)//扩展欧几里得
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    extend_Euclid(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}

int CRT(int a[],int m[],int n)
{
    int M = 1;
    int ans = 0;
    for(int i=1; i<=n; i++)//M=m1*m2*m3…………*mn
        M *= m[i];
    for(int i=1; i<=n; i++)
    {
        int x, y;
        int Mi = M / m[i];
        extend_Euclid(Mi, m[i], x, y);//扩展欧几里得求逆元x，因为mi互素，此处直接普通扩展欧几里得就可求得逆元
        ans = (ans + Mi * x * a[i]) % M;
    }
    if(ans < 0) ans += M;
    return ans;
}
int main()
{
    int p, e, i, d, t = 1;
    while(cin>>p>>e>>i>>d)
    {
        if(p == -1 && e == -1 && i == -1 && d == -1)
            break;
        a[1] = p;
        a[2] = e;
        a[3] = i;
        m[1] = 23;
        m[2] = 28;
        m[3] = 33;
        int ans = CRT(a, m, 3);
        if(ans <= d)
            ans += 21252;
        cout<<"Case "<<t++<<": the next triple peak occurs in "<<ans - d<<" days."<<endl;
    }
    return 0;
}
