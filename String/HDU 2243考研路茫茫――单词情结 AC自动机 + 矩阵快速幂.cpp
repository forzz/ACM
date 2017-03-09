//POJ 2778中我们求的是长度为L的不包含模式串的文本个数，现在这里我们要求长度为长度不超过L的不包含模式串的文本串个数。
//令f[i][n]==x表示当前在i点，已经走了n步且没有走过单词节点的总方法数。我们依然求出(m为自动机节点数目):
//f[i][n] =a0*f[0][n-1]+a1*f[1][n-1]+a2*f[2][n-1]+…+am-1*f[m-1][n-1]的递推矩阵。
//不过这里我们假想在AC自动机中加一个节点,该节点表示符号’\0’即结束符.然后任何其他有效字符包括’\0’自己都可以到达’\0’,
//但是’\0’的后继只能是自己.也就是说无论走到了第几步,当前节点都可以选择去走’\0’,只要它选择了走’\0’,那么以后只能继续走’\0’了。
//假设’\0’的节点序号为sz,那么其转移方程为:f[sz][n] =f[0][n-1]+f[1][n-1]+….+f[sz][n-1]
//初值f[i][0]=1 其中i为非单词节点(包括表示'\0'的sz节点)，f[j][0]=0 其中j为单词节点。
//最终长度<=L且不包含任何模式串的文本个数为：f[0][L]+f[1][L]+f[2][L]+...f[sz][L]。其中f[sz][L]表示所有那些真实长度<L，
//所以只能以'\0'结尾的合法字符串。即把以前的矩阵从sz-1*sz-1规模变成了sz*sz的规模，添加了最后一行和最后一列，
//其中最后一列除了末尾为1其他都为0，最后一行都是1(仔细想想是不是)。
//注意我们最后算出来的结果还有一个是非法的，因为最后mat^L取第一列，最后节点包含了空串的情况，所以我们还要-1才是不包含模式串且长度不超过L的串数。
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#define ll unsigned long long
//因为对2^64取模，所以定义数据类型为unsigned long long就可以了，这样就实现了自动取模。
using namespace std;
const int N = 55;
const int SIGMA_SIZE = 26;
struct Mat {
    ll a[N][N];
}ori, res;
int Next[N][SIGMA_SIZE], fail[N], val[N], sz, n, L;
char str[N];
void init() {//初始化根节点
    sz = 1;
    memset(Next[0], 0, sizeof(Next[0]));
    val[0] = 0;
}
void insert(char *s) {//字典树中插入串
    int u = 0, len = strlen(s);
    for (int i = 0; i < len; i++) {
        int k = s[i] - 'a';
        if (!Next[u][k]) {
            memset(Next[sz], 0, sizeof(Next[sz]));
            val[sz] = 0;
            Next[u][k] = sz++;
        }
        u = Next[u][k];
    }
    val[u] = 1;//结尾标记
}
void getFail() {//BFS求fail指针
    queue<int> Q;
    fail[0] = 0;
    for (int i = 0; i < SIGMA_SIZE; i++)//root的子节点的fail指针为0
        if (Next[0][i]) {
            fail[Next[0][i]] = 0;
            Q.push(Next[0][i]);
        }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (val[fail[u]])
            val[u] = 1;//判断当前串的后缀是否是其他词根
        for (int i = 0; i < SIGMA_SIZE; i++) {
            if (!Next[u][i])
                Next[u][i] = Next[fail[u]][i];//该节点为NULL时直接把其与fail指针相连，构成trie图
            else {
                fail[Next[u][i]] = Next[fail[u]][i];
                Q.push(Next[u][i]);
            }
        }
    }
}
Mat multiply(const Mat &x, const Mat &y) {//矩阵乘法
    Mat temp;
    for (int i = 0; i <= sz; i++)
        for (int j = 0; j <= sz; j++) {
            temp.a[i][j] = 0;
            for (int k = 0; k <= sz; k++)
                temp.a[i][j] += x.a[i][k] * y.a[k][j];
        }
    return temp;
}

void calc(int m) {//矩阵快速幂
    while (m) {
        if (m & 1)
            res = multiply(res, ori);
        m >>= 1;
        ori = multiply(ori, ori);
    }
}
int main() {
    while (scanf("%d%d", &n, &L) == 2) {
        init();//创建根节点
        for (int i = 0; i < n; i++) {//词根串放入字典树中
            scanf("%s", str);
            insert(str);
        }
        getFail();
        for (int i = 0; i <= sz; i++)//初始化矩阵
            for (int j = 0; j <= sz; j++)
                res.a[i][j] = ori.a[i][j] = 0;
        for (int i = 0; i <= sz; i++)//res为单位矩阵
            res.a[i][i] = 1;
        for (int i = 0; i < sz; i++)//i为树上的某个节点（共sz个）      创建路径矩阵
            for (int j = 0; j < SIGMA_SIZE; j++)//j为该节点的某个孩子
                if (!val[Next[i][j]])
                    ori.a[i][Next[i][j]]++;//如果不是词根，维护到ori中
        for (int i = 0; i <= sz; i++)//
            ori.a[i][sz] = 1;
        calc(L);
        ll ans = 0;
        for (int i = 0; i <= sz; i++)//求出长度不超过L的不包含模式串的文本串个数（多1）
            ans += res.a[0][i];
        ori.a[0][0] = ori.a[1][0] = 26;
//求长度不超过L的文本串总数26^1+26^2+…26^L-x即可.本题要用unsigned long long.
//注意:26^1+26^2+…26^L是个等比数列,但是因为要求余,所以用公式肯定不行.这里我们依然用矩阵幂来算
        ori.a[0][1] = 0;
        ori.a[1][1] = 1;
        res.a[0][1] = 1;
        res.a[0][0] = res.a[1][1] = res.a[1][0] = 0;
        sz = 1;
        calc(L);
        ll ans2 = res.a[0][0];//Sn+1
        printf("%llu\n", ans2 - ans + 1);
    }
    return 0;
}
/*
26^1+...+26^n可以用快速幂求出h或者矩阵快速幂求出。
|1 26| |Sn  | |Sn+1    |
|0 26|*|26^n|=|26^(n+1)|;//Sn=26^1+26^2+...+26^n
【Sn+1=Sn+26^(n+1)    26^(n+1)=26*26^n】

|A 1| |Sn| |Sn+1|
|0 1|*| A|=|A   |;//Sn=A+A^2+A^3+...+A^n

只要:|A 1|
     |0 1| 自乘n次与|S0|相乘即可,则可以用矩阵快速幂求
                    |A |
*/
