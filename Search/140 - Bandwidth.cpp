#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 10;
int id[256], letter[maxn];
int main() {
  char input[1000];
  while(scanf("%s", input) == 1 && input[0] != '#') {
    // 计算结点个数并给字母编号
    int n = 0;
    for(char ch = 'A'; ch <= 'Z'; ch++)
      if(strchr(input, ch) != NULL) {//extern char *strchr(const char *s,char c);查找字符串s中首次出现字符c的位置。
        id[ch] = n++;        //每一个字母都有按顺序排列的对应编号
        letter[id[ch]] = ch; //编号对应ch
      }
    int len = strlen(input), p = 0, q = 0;
    vector<int> u, v;
    while(1) {
      while(p < len && input[p] != ':') p++;  //找到:
      if(p == len) break;
      while(q < len && input[q] != ';') q++;  //找到;
      for(int i = p+1; i < q; i++) {  //每个关系看作有向边
        u.push_back(id[input[p-1]]);  //起点，编号储存
        v.push_back(id[input[i]]);    //终点
      }
      p++; q++;
    }

    // 枚举全排列
    int P[maxn], bestP[maxn], pos[maxn], ans = n;
    for(int i = 0; i < n; i++) P[i] = i;   //最初所有字母按字典序排序，p[i]表示i号位置的字母
    do {
      for(int i = 0; i < n; i++) pos[P[i]] = i; // i号位置的字母的位置
      int bandwidth = 0;
      for(int i = 0; i < u.size(); i++)
        bandwidth = max(bandwidth, abs(pos[u[i]] - pos[v[i]])); // 计算带宽
      if(bandwidth < ans) {
        ans = bandwidth;
        memcpy(bestP, P, sizeof(P));
      }
    } while(next_permutation(P, P+n));

    // 输出
    for(int i = 0; i < n; i++) printf("%c ", letter[bestP[i]]);
    printf("-> %d\n", ans);
  }
  return 0;
}
