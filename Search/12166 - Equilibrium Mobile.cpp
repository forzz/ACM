#include <bits/stdc++.h>
using namespace std;
int cur = 0; //设为全局变量，更易在dfs中维护
char str[1024000];
map<long long, int> cnt;
void DFS(int dep)
{
    if(isdigit(str[cur])){ //仅进行1次判定，不是while
        long long a = 0;
        while(isdigit(str[cur]))
            a = a * 10 + str[cur++] - '0'; //char转化为int
        cnt[a<<dep]++; //记录总重量
    }
    else{
        cur++; DFS(dep + 1);  //cur++ 跳过[  然后找到左孩子
        cur++; DFS(dep + 1);  //cur++跳过 ， 然后找到右孩子
        cur++;                //cur++跳过 ]
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    //cin.get() 每次读取一整行并把由Enter键生成的换行符留在输入队列中
    //cin.getline() 每次读取一整行并把由Enter键生成的换行符抛弃
    while(cur = 0, cnt.clear(), T--) {
        cin >> str; DFS(0);
        int mx = INT_MIN, sum = 0;
/*在标准头文件limits.h中
        #define INT_MAX 2147483647
        #define INT_MIN (-INT_MAX - 1)
*/
        for(auto it = cnt.begin(); it != cnt.end(); it++)
            sum += it->second, mx = max(mx, it->second);
        cout << sum - mx << endl;
    }
    return 0;
}
/*
要使得改动的数量最少，那么就至少有一个秤砣不变，然后以这个秤砣为基准来调整整个天平。天平的结构是二叉树，
那么由此我们可以得出，如果以深度为d重量为w的秤砣为基准，那么整个天平的重量就是w * pow(2, d)，即w << d。
当然，可能会有一些秤砣算出的以各自为基准的天平总重量相同，设天平总重量为sumw，那么这些秤砣的数量就表示了
如果使天平的总重量为sumw需要使多少个秤砣保持不变。
*/
