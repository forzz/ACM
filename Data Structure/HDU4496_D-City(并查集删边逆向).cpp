#include<cstdio>
int f[10001];
int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}
int main()
{
    int n,m,i,u[100001],v[100001],sum[100001];

    while(~scanf("%d%d", &n,&m))
    {
        for(i=0; i<n; i++) f[i] = i;//初始化f
        for(i=0; i<m; i++)
            scanf("%d%d", u+i,v+i);
        int num = 0, g = 0;
        for(i=m-1; i>=0; i--)//从后往前读入，不需要再次处理
        {
            sum[g++] = num;//保存未加入i时的总集合数
            int x = find(u[i]);
            int y = find(v[i]);
            if(x != y) f[x] = y, num++; //两者没在同一集合，合并集合，集合数+1
        }
        for(i=g-1; i>=0; i--)
            printf("%d\n", n-sum[i]);
    }
    return 0;
}
