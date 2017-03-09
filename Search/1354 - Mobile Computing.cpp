#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct Tree {
  double L, R; // L是平衡点到最左边的距离，R类似
  Tree():L(0),R(0) {}
};
const int maxn = 6;
int n, vis[1<<maxn];
double r, w[maxn], sum[1<<maxn];
vector<Tree> tree[1<<maxn];  //根节点代表的二叉树
void dfs(int subset) {
  if(vis[subset]) return;
  vis[subset] = true;
  bool have_children = false;
  for(int left = (subset-1)&subset; left; left = (left-1)&subset) {
//自顶向下构造二叉树，每次枚举左子树用的哪个子集，则右子树就是使用剩下的子集
    have_children = true;
    int right = subset^left;//按位异或，每位不相同为1
    double d1 = sum[right] / sum[subset];//左边长度
    double d2 = sum[left] / sum[subset];//右边长度 解方程可得
    dfs(left); dfs(right);
    for(int i = 0; i < tree[left].size(); i++) //该根节点下所有可能的排列形式遍历
      for(int j = 0; j < tree[right].size(); j++) {
        Tree t;
        t.L = max(tree[left][i].L + d1, tree[right][j].L - d2);
        t.R = max(tree[right][j].R + d2, tree[left][i].R - d1);
        if(t.L + t.R < r) tree[subset].push_back(t); //合法情况压入
      }
  }

  if(!have_children) tree[subset].push_back(Tree());
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%lf%d", &r, &n);
    for(int i = 0; i < n; i++) scanf("%lf", &w[i]);
    for(int i = 0; i < (1<<n); i++) {      //最多只有2^n种可能
      sum[i] = 0;
      tree[i].clear();
      for(int j = 0; j < n; j++)
        if(i & (1<<j)) sum[i] += w[j];
        //利用位运算的集合表示方法，sum表示总重量
    }
    int root = (1<<n)-1;        //  n-1位全是1
    memset(vis, 0, sizeof(vis));
    dfs(root);
    double ans = -1;
    for(int i = 0; i < tree[root].size(); i++)//遍历求出最宽
      ans = max(ans, tree[root][i].L + tree[root][i].R);
    printf("%.10lf\n", ans);
  }
  return 0;
}
