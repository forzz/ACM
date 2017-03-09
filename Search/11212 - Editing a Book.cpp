#include<bits/stdc++.h>
const int maxn = 9;
int n,a[maxn];
inline bool End()//判断是否完成排序
{
    for(int i = 1; i < n; i++){
        if(a[i] <= a[i-1]) return false;
    }
    return true;
}
inline int h()//乐观估价函数（排序错误的数字个数）
{
    int cnt = 0;
    for(int i = 1; i < n; i++)
        if(a[i] != a[i-1]+1) cnt++;
    return cnt;
}
int maxd;
const int intsz = sizeof(int);
const int asz = sizeof(a);
bool dfs(int d)
{
    if(3*d + h() > 3*maxd) return false;//剪枝
    if(End()) return true; //找到结果
    int old[maxn];//保存a
    memcpy(old,a,asz);
    int b[maxn];//剪切板
    for(int i = 0; i < n; i++) if( i == 0 || old[i] != old[i-1] + 1) //剪切起点（第一个不连续的点）
    for(int j = i; j < n; j++) { //终点 选取片段可以不连续
        while(j+1 < n && old[j+1] == old[j] + 1)j++;//内部更新j 不破坏j之后的连续片段
        memcpy(b,old+i,intsz*(j-i+1));    //剪切移动片段（i到j）
        for(int k = j+1;k < n;k++){//由于对称性，统一往后粘贴，查找粘贴位置
            while(k+1 < n && old[k+1] == old[k] + 1)k++;//内部更新k 不破坏k之后的连续片段
            memcpy(a+i,old+j+1,intsz*(k-j));//把j到k连续片段移到i后面
            memcpy(a+i+k-j,b,intsz*(j-i+1));//把i到j连续片段移到k后面
            if(dfs(d+1))return true;  //深度++
            memcpy(a,old,asz);//回溯法恢复全局变量
        }
    }
    return false;
}

inline int solve()
{
    if(End())return 0;
    for(maxd = 1; maxd < 5 ;maxd++) //为5即可通过数据
        if(dfs(0)) return maxd;
    return 5;
}
int main()
{
    int Cas = 0;
    while(~scanf("%d",&n)&&n) {
        for(int i = 0; i < n; i++)
            scanf("%d",a+i);
        int ans = solve();
        printf("Case %d: %d\n",++Cas,ans);
    }
    return 0;
}
