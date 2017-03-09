#include<stdio.h>
#include<string.h>
#include<math.h>
#include<queue>
#include<algorithm>
using namespace std ;
const int maxn = 333333 ;
int c[maxn*10] ;//内存池
const int mod = 1000000009 ;
int dp[1111][111][15] ;
char s[15] ;
int l[15] ;
int get ( char c ) {
    if ( c == 'A' ) return 0 ;
    if ( c == 'C' ) return 1 ;
    if ( c == 'G' ) return 2 ;
    return 3 ;
}
struct ac_auto {
    queue<int> Q ;
    int tot , c[4][111] ;
    int val[111] , fail[111] ;
    int new_node () {//创建新节点
        int i ;
        for ( i = 0 ; i < 4 ; i ++ ) c[i][tot] = 0 ;
        fail[tot] = val[tot] = 0 ;//初始化所有fail指针都指向root
        return tot ++ ;
    }
    void init () {//创建根节点
        tot = 0 ;
        new_node () ;
    }
    void insert ( char *s , int id ) {//将字符串加入字典树
        int now = 0 ;
        for ( ; *s ; s ++ ) {
            int k = get ( *s ) ;
            if ( !c[k][now] ) c[k][now] = new_node () ;//创建新节点
            now = c[k][now] ;//维护now为当前子节点，进行下一次for循环
        }
        val[now] = max ( val[now] , l[id] ) ;//创建结尾标记，记录当前节点能够达到的最长后缀
    }
    void get_fail () {////BFS求出所有结点的fail指针
        int i , u = 0 ;
        for ( i = 0 ; i < 4 ; i ++ )
            if ( c[i][u] )
                Q.push ( c[i][u] ) ;//压入root的所有子节点（BFS从第二层节点开始）
        //对于根结点下所有的子结点，失败指针一定是指向root，在初始化的时候就已经预处理
        while ( !Q.empty () ) {
            u = Q.front () , Q.pop () ;
            for ( i = 0 ; i < 4 ; i ++ ) {
                if ( c[i][u] ) {//子节点存在
                    int e = c[i][u] ;//e是子节点
                    int j = fail[u] ;//j是父节点的fail指针指向的节点
//对于非根节点及其子节点，如果now->next[i]不等于NULL，则需要构造now->next[i]的失败指针。now的失败指针一定存在一个i号子结点（由下面的else语句）
//即now->fail->next[i]，那么我们将now->next[i]的失败指针指向它，即now->next[i]->fail = now->fail->next[i]；
                    fail[e] = c[i][j] ;
                    val[e] = max ( val[e] , val[fail[e]] );//维护val值（fail指针的唯一作用，后面不直接使用fail）
//往fail指针查找，记录当前匹配串的前缀是不是所查找的某个字符串的结尾
                    Q.push ( e ) ;
                }
                else c[i][u] = c[i][fail[u]] ;//如果该节点不存在，不必维护其fail指针，直接将其值转移到其fail指针上
            }
        }
    }
    void solve ( int n ) {
//开始的时候想的是dp[i][j]表示长度为i，走到自动机的j节点的答案。
//但是显然既然是可以重复覆盖的，那么每一个节点的dp值都并不是最优的，因为可以从一个地方截断去连接另外一个串
//我可以当前这个字符没匹配上，但是下一个在加入下一个字符的时候，构成的字符串把当前这个字符给匹配进去了。
//dp[len][x][k]表示长度len且后缀状态为自动机结点x且后k位还不满足要求的方案数，因为DNA最长10，所以第三维k不会超过10。
//转移就是向自动机上四个方向的结点走，如果下一步结点x'是某DNA的后缀且长度比k大，那就是转移到dp[len+1][x'][0]否则转移到dp[len+1][x'][k+1]。
        int i , j , k , p ;
        for ( i = 0 ; i < n ; i ++ ) {//i为总长度
            for ( j = 0 ; j < tot ; j ++ )//j为当前尾结点，每位一共有tot种可能（j为树中的节点）这个串是由所给的串相连接构成，
                for ( k = 0 ; k <= 10 ; k ++ ) {//k为不满足要求的位数
                    if ( dp[i][j][k] ) {//防止重复dp
                        for ( p = 0 ; p < 4 ; p ++ ) {
                            int t = c[p][j] ;//t为j节点的孩子
                            if ( val[t] >= k + 1 )//如果当前结点是某个字符串的结尾并且可能在当前位+后K位中实现匹配（字符串可以逆序）
                                dp[i+1][t][0] = ( dp[i+1][t][0] + dp[i][j][k] ) % mod ;
//此时t是某个字符串的结尾且该字符串匹配成功，这种情况方案数可以由当前i j k的情况得到
                            else dp[i+1][t][k+1] = ( dp[i+1][t][k+1] + dp[i][j][k] ) % mod ;
//t匹配不成功，以当前t节点继续dp，维护新的i和k，新状况可由当前dp得到，加在一起。（又多一个无用后缀 K+1）
                        }
                    }
                }
        }
        int ans = 0 ;
        for ( i = 0 ; i < tot ; i ++ )
            ans = ( ans + dp[n][i][0] ) % mod ;//总长度为n，以任意字符结尾，满足当前字符串
        printf ( "%d\n" , ans ) ;
    }
} ac ;
int main () {
    int n , m , i , j , k , p , r , t ;
    while ( scanf ( "%d%d" , &n , &m ) != EOF ) {
        ac.init () ;//创建根节点
        j = 0 ;
        while ( m -- ) {//把字符串存入字典树
            scanf ( "%s" , s ) ;
            l[++j] = strlen ( s ) ;//根据字符串长度进行编号
            ac.insert ( s , j ) ;
        }
        ac.get_fail () ;//求fail指针
        memset ( dp , 0 , sizeof ( dp ) ) ;
        dp[0][0][0] = 1 ;//边界初始值，根节点本身算一个串
        ac.solve ( n ) ;
    }
}
