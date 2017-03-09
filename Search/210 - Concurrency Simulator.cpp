#include<cstdio>
#include<queue>
#include<cstring>
#include<cstdlib>
#include<cctype>
using namespace std;
const int maxn = 1000;
deque<int> readyQ;         //执行队列
queue<int> blockQ;            //等待队列
int n, quantum, c[5], var[26], ip[maxn];
bool locked;
char prog[maxn][10];

void run(int pid) {
  int q = quantum;
  while(q > 0) {
    char *p = prog[ip[pid]];
    switch(p[2]) {
      case '=':
        var[p[0] - 'a'] = isdigit(p[5]) ? (p[4] - '0') * 10 + p[5] - '0' : p[4] - '0'; //var储存数值，最多就是两位
        q -= c[0];
        break;
      case 'i': // print
        printf("%d: %d\n", pid+1, var[p[6] - 'a']);
        q -= c[1];
        break;
      case 'c': // lock
        if(locked) { blockQ.push(pid); return; }  //lock前有lock，放入阻止队列，配额浪费
        locked = true;
        q -= c[2];
        break;
      case 'l': // unlock
        locked = false;
        if(!blockQ.empty()) {
          int pid2 = blockQ.front(); blockQ.pop();  //命令号读取
          readyQ.push_front(pid2);
        }
        q -= c[3];
        break;
      case 'd': // end
        return;
    }
    ip[pid]++;  //该程序的初始命令行加一
  }
  readyQ.push_back(pid);
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d %d %d %d %d %d %d\n", &n, &c[0], &c[1], &c[2], &c[3], &c[4], &quantum); //n个程序并行
    memset(var, 0, sizeof(var));

    int line = 0;
    for(int i = 0; i < n; i++) {
      fgets(prog[line++], maxn, stdin);  //读取命令
      ip[i] = line - 1;    //第i个程序的初始命令位置
      while(prog[line - 1][2] != 'd')  //若不是“end”
        fgets(prog[line++], maxn, stdin);
      readyQ.push_back(i);   //把程序号压入执行队列
    }

    locked = false;
    while(!readyQ.empty()) {
      int pid = readyQ.front(); readyQ.pop_front();
      run(pid);
    }
    if(T) printf("\n");  //输出格式
  }
  return 0;
}
