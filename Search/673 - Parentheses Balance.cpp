#include<iostream>
#include<string>
using namespace std;
const int maxn = 10;
int n, v[maxn];//映射表
string leaves;
int solve(const string& q) {
  int u = 1;
  for(int i = 0; i < n; i++) {    //v[i]表示第i层对应字符串序号
    if(q[v[i]] == '0') u *= 2; else u = u*2+1;
  } //u代表目标在二叉树数组中的位置
  return leaves[u-(1<<n)] - '0';  //(1<<n)表示非叶子结点的个数
}

int main() {
  int kase = 0;
  while(cin >> n && n) {
    string s;
    cout << "S-Tree #" << ++kase << ":\n";
    for(int i = 0; i < n; i++) { cin >> s; v[i] = s[1] - '1'; } //v保存x，按顺序每一层的代号-1
    //0层3  1层2   2层1
    int m;
    cin >> leaves >> m;  //leaves保存每个叶子的值
    while(m--) {
      string q;
      cin >> q;
      cout << solve(q);
    }
    cout << "\n\n";
  }
  return 0;
}
