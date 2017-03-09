#include <cstdio>
#include <cstring>
#include <cassert>
const int maxn = 100000 + 10;
int a[maxn], s, n, cnt[maxn * 2];
bool ok[maxn * 3];
inline bool in(int x) { return x >= 1 && x <= n; }
int main()
{
    int T; scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &s, &n);//s为歌数
        memset(a, -1, sizeof(a));
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);//数组从1开始
        memset(cnt, 0, sizeof(cnt));
        int tot = s;//初始为s就是为了让第一个else扣
        for(int i = 1; i < n + s; i++)
        {
            if(in(i-s)) { cnt[a[i-s]]--; if(!cnt[a[i-s]]) tot--; }
             //若之前仅出现过1次，则tot--（i边前进边清除i-s对于tot的影响）
            else tot--; //i<=s时（到i=s+1时正好扣s）
            if(in(i)) { cnt[a[i]]++; if(cnt[a[i]] == 1) tot++; }
            //cnt数组来记录每个数出现的次数和用tot记录一共有多少个不同的数出现
            else tot++;    //i>n时（什么都有可能，默认为出现不同的数）
            ok[i] = (tot == s); //ok[i]表示以i为结尾的前s个数是否能构成一个1~s的排列。
        }
        int ans = 0;
        for(int x = 1-s; x <= 0; x++)//也就是枚举第一首歌会出现的位置，注意要考虑到不完整的序列。
        {
            bool flag = true;
            for(int i = x; i < n+s; i += s)
            {
                if(i <= 0) continue;
                if(!ok[i]) { flag = false; break; }
            }
            if(flag)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
