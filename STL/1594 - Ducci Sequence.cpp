#include <stdio.h>
#include <stdlib.h>
int a[20];
int sum(int n)//这个题唯一的技巧
{
 int i;
 for (i=0;i<n;i++)
    if (a[i]!=0)  return 0;
  return 1;
}
int main()
{
 int t;
 scanf("%d",&t);
 while (t--)
 {
  int n;
  int i,f=1;//标志变量的设定
  scanf("%d",&n);
  for (i=0;i<n;i++)
    scanf("%d",&a[i]);
  int ans=0;
  while (ans<=500)
  {
   int c=a[0];
   for (i=0;i<n-1;i++)
     a[i]=abs(a[i]-a[i+1]);
   a[n-1]=abs( a[n-1]-c);
   if (sum(n)) {f=0;break;}
   ans++;
  }
  if (!f) printf("ZERO\n");
  else printf("LOOP\n");
 }
 return 0;
}
