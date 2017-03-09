#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 100000+10
using namespace std;
char key[8][5] = {{"abc"}, {"def"}, {"ghi"}, {"jkl"}, {"mno"}, {"pqrs"}, {"tuv"}, {"wxyz"}};//每行保存一个数字键所含的字母（数字键2到9）
int next[MAXN][30], time[MAXN];
int L, root;//L记录当前结点总数  root保存根节点
int newnode()//创建新节点L
{
    for(int i = 0; i < 26; i++)
        next[L][i] = -1;
    time[L++] = 0;
    return L-1;//返回节点所在的编号（但L又指向了新节点）
}
void init()//初始化根节点
{
    L = 0;
    root = newnode();
}
void Insert(char *s, int num)//把字符串和对应概率放入字典树
{
    int len = strlen(s);
    int now = root;//从根节点开始
    for(int i = 0; i < len; i++)
    {
        if(next[now][s[i]-'a'] == -1)//节点为空
            next[now][s[i]-'a'] = newnode();
        now = next[now][s[i]-'a'];//更新父节点
        time[now] += num;//沿途记录概率
    }
}
char ans[1010];
int Mp;//记录节点最大概率值
char str[1010], temp[1010];
void DFS(int goal, int now, int ROOT)//goal表示目标数字位置 now表示当前数字位置 ROOT表示字典树中当前位置
{
    if(now == goal + 1)//查找到目标数字位置
    {
        if(time[ROOT] > Mp)//当前查找结果更优，维护ans
        {
            Mp = time[ROOT];
            strcpy(ans, temp);
        }
    }
    else
    {
        int num = str[now] - '0' - 2;//当前按键 可能出现的字符串下标
        int len = strlen(key[num]);//可能出现的字符个数
        for(int i = 0; i < len; i++)//遍历
        {
            int v = key[num][i] - 'a';
            if(next[ROOT][v] == -1) continue;//v不是ROOT的子节点，进行下一次遍历
            temp[now] = key[num][i];
            DFS(goal, now+1, next[ROOT][v]);
        }
    }
}
int main()
{
    int t, k = 1;
    int n, m;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        init(); int num;
        for(int i = 0; i < n; i++)//读入初始数据并建树
            scanf("%s%d", str, &num), Insert(str, num);
        scanf("%d", &m);
        printf("Scenario #%d:\n", k++);
        while(m--)//dfs搜索每个询问
        {
            scanf("%s", str);
            int len = strlen(str);
            for(int i = 0; i < len-1; i++)//遍历询问字符串
            {
                memset(temp, 0, sizeof(temp));
                Mp = 0;//最大概率记录
                DFS(i, 0, root);
                if(Mp == 0)
                    printf("MANUALLY\n");
                else
                    printf("%s\n", ans);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
