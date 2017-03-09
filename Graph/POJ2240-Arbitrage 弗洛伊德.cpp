#include<cstdio>
#include<cstring>
#include<cstdlib>
const int MAXN = 1 << 5;
double r[MAXN][MAXN];
int n, m;
char s[MAXN][MAXN];
int findbuf( char *buf)//查找符合字符串所在的编号
{
    int i;
    for( i = 0; i < m; i ++)
        if( !strcmp( buf, s[i]))
            return i;
}
void Read_Gragh()//读入处理，转化为图
{
    char buf1[MAXN], buf2[MAXN];
    double rate;
    for( int i = 0; i < n; i ++)
        scanf( "%s", s[i]);
    memset( r, 0, sizeof r);
    for( int i = 0; i < n; i ++) r[i][i] = 1;//预处理，自身到自身的初始权值是1
    scanf( "%d", &m);
    for( int i = 0; i < m; i ++)
    {
        scanf( "%s%lf%s", buf1, &rate, buf2);
        r[ findbuf( buf1)][ findbuf(buf2)] = rate;
    }
}
bool floyd()
{
    for( int k = 0; k < n; k ++)//每次求中间点标号不超过k的i到j最短路
        for( int i = 0; i < n; i ++)//枚举头
            for( int j = 0; j < n; j ++)//枚举尾
                if( r[i][j] < r[i][k] * r[k][j])
                    r[i][j] = r[i][k] * r[k][j];
    for( int i = 0; i < n; i ++)
        if( r[i][i] > 1) return true;//如果自身到自身的权值大于1则可认为盈利
    return false;
}
int main()
{
    int cas = 0;
    while( scanf( "%d", &n), n)
    {
        Read_Gragh();
        printf( "Case %d: ", ++ cas);
        bool ok = floyd();
        if( ok) printf( "Yes\n");
        else printf( "No\n");
    }
    return 0;
}
