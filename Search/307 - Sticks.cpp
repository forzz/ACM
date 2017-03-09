#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n,sum,tmax,s[100],used[100],ans; //防止走回头路 需要用used函数保存已访问
bool Dfs(int num,int pos,int len){//num为拼接的木棍号 pos为第pos个木棍 len为当前已拼接的长度（递归主要用后两者）
//枚举目标长度的范围控制在MAX到SUM，所有不能被sum整出的目标长度都要被跳过。
    if(num * ans == sum)//拼接成功（dfs中带num的原因）
        return true;
    for(int i = pos; i < n; ++i){//从第pos个木棍开始遍历（和普通的递归暴力枚举不同）
        if(used[i] || (i && s[i] == s[i - 1] && !used[i - 1])) continue;      //判断下一次递归的合法性
   //如果某根木棍和上一根木棍长度一样，而且上一根没有被选上，则这根木棍也不会被选上。
        if(len + s[i] < ans){//未拼接完成 选中此木棍
            used[i] = 1;
            if(Dfs(num,i + 1,len + s[i])) return true; //所有dfs包含的状态量都在此语句中更新
            used[i] = 0;//递归出口恢复状态
            if(len == 0) return false;//第一截未使用最长木棒（在此递归全部失败后执行这句）
/*
如果当前是在拼一根新木棒的第一截，但如果把可用的最长的一根木棒用上后不能拼成功的话，
那么就不用再试后面的木棒了，肯定是前面拼的过程出了问题。（因为在之后的递归过程中这第一截木棍总要被用到）
*/
        }
        else if(len + s[i] == ans){//选中此木棍后拼接完成
            used[i] = 1;
            if(Dfs(num + 1,0,0)) return true;//更新
            used[i] = 0;
            return false;
/*
如果当前可用的木棒恰好能补上一根原木棒的最后一截，但用它补上之后却不能用剩下的木棒完成后续的任务，
那么也不用再试后面的木棒了，肯定是前面拼的过程出了问题。
*/
        }
    }
    return false;
}

int main(){
    while(scanf("%d",&n) == 1 && n){
        sum = 0;
        tmax = -1;
        for(int i = 0; i < n; ++i){
            scanf("%d",&s[i]);
            sum += s[i];  //总和
            tmax = max(tmax,s[i]);//最大值
        }
        sort(s,s + n,greater<int>());//将s从大到小排序更快，因为优先找大的len，更快达到目标以减少递归层数。
/*
升序：sort(begin,end,less<data-type>());
降序：sort(begin,end,greater<data-type>()).
*/
        memset(used,0,sizeof(used));
        for(ans = tmax; ans <= sum; ++ans)  //第一个for，开始dfs暴力搜索(枚举原木棒的长度)
            if(sum % ans == 0)  //拼成木条的长度必须是所有木棒长度总和的约数，并且大于等于木条中的最大值
                if(Dfs(0,0,0)) //已知原木棒的长度，暴力搜索出所有拼接方法（需要当前木棍的编号和）
                    break;
        printf("%d\n",ans);
    }
    return 0;
}
