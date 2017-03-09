#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 50010;
const int inf = 0x3f3f3f3f;
int a[maxn], pre[maxn], nxt[maxn], dp[maxn];
map<int, int> mp;//map查重
int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {//读入数据
            scanf("%d", &a[i]);
            pre[i] = i - 1;//初始化双向链表
            nxt[i] = i + 1;
        }
        mp.clear();
        memset(dp, inf, sizeof(dp));
        dp[0] = 0, pre[0] = -1;//边界条件
        for (int i = 1; i <= n; i++) {//将有用的节点转化为链表
            if (!mp.count(a[i])) mp[a[i]] = i;//之前不存在该颜色，记录位置
            else {
                int id = mp[a[i]];//id为之前存在该颜色的位置
                nxt[pre[id]] = nxt[id];//维护链表，把id从链表删除（因为从首到尾搜索，越往后得到的相同颜色对dp更优化）
                pre[nxt[id]] = pre[id];
                mp[a[i]] = i;
            }
            int cnt = 0;
            for (int j = pre[i]; j != -1; j = pre[j]) {//dp每个遍历以i为终点的链表（每个节点都是不同的颜色）
                cnt++;
                dp[i] = min(dp[i], dp[j] + cnt * cnt);//dp[i]表示涂完前i个所化的最小代价 j是i之前的不同的颜色的位置 cnt是j到i不同的颜色个数
                if (cnt * cnt > i)//剪枝:单个涂需要n次，如果累计次数超过n，不是最优解（对1 2 3 4 ... n优化）
                    break;
            }
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
