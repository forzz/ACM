#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxm = 500 + 5;
int m, k, p[maxm];
int solve(long long maxp) {//划分为最小最大值为maxp的序列需要的区间数
  long long done = 0;
  int ans = 1;
  for(int i = 0; i < m; i++) { //m个数字遍历
    if(done + p[i] <= maxp) done += p[i];
    else { ans++; done = p[i]; } //区间数+1
  }
  return ans;
}
int last[maxm];
void print(long long ans) {
  long long done = 0;
  memset(last, 0, sizeof(last));
  int remain = k;    //剩余区间为remain
  for(int i = m-1; i >= 0; i--) {//从右往左划分
    if(done + p[i] > ans || i+1 < remain) {//加上i值大于ans  当前未分数字个数小于剩余区间数（接下来每个数字一个区间）
      last[i] = 1; remain--; done = p[i];  //积累量更新 last[i]表示i号数字的左侧划分
    }
    else {
      done += p[i];//积累量增加
    }
  }
  for(int i = 0; i < m-1; i++) {
    printf("%d ", p[i]);
    if(last[i]) printf("/ ");
  }
  printf("%d\n", p[m-1]);
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &m, &k);  //m个正整数，k个区间
    long long tot = 0;
    int maxp = -1;
    for(int i = 0; i < m; i++) {
      scanf("%d", &p[i]);
      tot += p[i]; //总和
      maxp = max(maxp, p[i]); //最大值
    }
//所要求的最小的最大值必定是从[maxp,tot(总和)]中取得的，那么我们可以二分法猜测一个数字，
    long long L = maxp, R = tot;  //int最大值为2.1*10^9
    while(L < R) {
      long long M = L + (R-L)/2;//靠近区间起点取整，求平均值
      if(solve(M) <= k) R = M; else L = M+1;  //划分区间越多，最大值越小（<=是判断第一个符合的最小最大值）
    }
    print(L);
  }
  return 0;
}
