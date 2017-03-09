#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define lson (rt<<1)
#define rson ((rt<<1)|1)
#define mid ((l+r)>>1)
using namespace std;
const int MAX = 5000+10;
int a[MAX<<2], b[MAX], n;
void pushup(int rt)
{
  a[rt] = a[lson] + a[rson];//求和
}
void build(int l, int r, int rt) {//左孩子，右孩子，根节点(根节点随便找，只要不重复就行)
  if (l == r)    {a[rt] = 0; return;}//到达叶子节点，初始化并结束递归
  build(l,mid,lson);
  build(mid+1, r, rson);
  pushup(rt);
}
void update(int p, int l, int r, int rt) {//元素 查找范围 根节点 a[p]代表p存在
  if (l == r)
        {a[rt]++; return;}
  if(p<=mid)
        update(p, l,mid,lson);
  if(p>mid)
        update(p, mid+1, r, rson);
  pushup(rt);
}
//询问区间[L, R]中目前的数字个数
int query(int L, int R,int l, int r, int rt) //目标范围 查找范围 根节点
{
  if (L <= l && R >= r)     {return a[rt];}//目标范围包括当前查找范围，直接返回
  int ret = 0;
  if (L <= mid)
        ret += query(L,R,l,mid,lson);
  if (R > mid)
        ret += query(L,R,mid+1,r,rson);
  return ret;
}
int main() {
    while (~scanf("%d", &n))
 {
    int i, sum = 0, ans;
    build(0, n - 1, 1);//创建线段树（线段树a[i]保存值为i的数的个数）（利用快速求和）
    for (i = 0; i < n; ++i) {//读入数据到b数组
      scanf("%d", b+i);
      sum += query(b[i]+1, n-1, 0, n-1, 1);//遍历树，判断前面有几个比a[i]大的，并且记录
      update(b[i], 0, n-1, 1);//将每个序列的值放入线段树对应位置
    }
    ans = sum;
    for (i = 0; i < n; ++i) {
      sum += (n-1-2*b[i]);
      if (sum < ans) ans = sum;
    }
    printf("%d\n", ans);
 }
  return 0;
}
