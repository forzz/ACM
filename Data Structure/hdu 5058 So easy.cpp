#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX 107

using namespace std;

int n,cnt1,cnt2;
int a[MAX],b[MAX];
int c[MAX],d[MAX];

int main ( )
{

    while ( ~scanf ( "%d" , &n ) )
    {
        for ( int i = 1 ; i <= n ; i++ )
            scanf ( "%d" , &a[i] );
        for ( int i = 1 ; i <= n ; i++ )
            scanf ( "%d" , &b[i] );
        sort ( a+1 , a+n+1 );
        sort ( b+1 , b+n+1 );
        cnt1 = cnt2 = 0;
        a[0] = b[0] = -1;
        for ( int i = 1 ; i <= n ; i++ )
            if ( a[i] != a[i-1] )
                c[cnt1++] = a[i];
        for ( int i = 1 ; i <= n ; i++ )
            if ( b[i] != b[i-1] )
                d[cnt2++] = b[i];
        bool flag = true;
        if ( cnt1 == cnt2 )
        {
            for ( int i = 0 ; i < cnt1 ; i++ )
                if ( c[i] != d[i] )
                {
                    flag = false;
                    break;
                }
        }
        else flag = false;
        if ( flag ) puts ( "YES" );
        else puts ( "NO" );
    }
}
