#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 10100
using namespace std;
int n=10000,m;
int fa[M],v[M],max_num[M];
int Find(int x)
{
  if(!fa[x])
    fa[x]=x,max_num[x]=x;
  if(fa[x]==x)
    return x;
  return fa[x]=Find(fa[x]);
}
int main()
{
  int i,x,y;
  cin>>m;
  for(i=1;i<=m;i++)
  {
    scanf("%d%d",&x,&y);
    x=Find(x);y=Find(y);
    if(x==y)
      v[x]=1;
    else
    {
      fa[x]=y;
      v[y]|=v[x];
      max_num[y]=max(max_num[x],max_num[y]);
    }
  }
  for(i=1;i<=n;i++)
  {
    int temp=Find(i);
    if(v[temp]) continue;
    if(max_num[temp]==i) break;
  }
  cout<<i-1;
}
