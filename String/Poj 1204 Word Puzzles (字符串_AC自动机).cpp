#include <stdio.h>
#include <string.h>
#define INF 1001
struct node {
    int flag;
    node *fail,*next[26];
}*root,*q[INF*INF],arr[INF*INF];//arr为内存池 q为队列
struct location {//结果数组
    int x,y,dir;
}ans[1001];
int  n,l,w,total,head,tail;
int dir[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};//八个方向
char str[INF][INF],tp[INF];
char tar[12*INF][INF];
node *new_node(){
    node *p = &arr[total++];
    p->flag = -1;
    p->fail = NULL;
    memset(p->next,0,sizeof(p->next));//可以给任何结构赋值0和-1
    return p;//返回新节点的指针
}
void Insert(char *str,int in) {
    node *p = root;
    int i = strlen(str) - 1,k;
    for ( ;i >= 0; --i) {//要输出第一次出现的位置，而AC自动机不能回溯，所以将串反着构造进字典树里
        k = str[i] - 'A';
        if (p->next[k] == NULL) p->next[k] = new_node();
        p = p->next[k];
    }
    p->flag = in;
    //结尾标记 每个模式串在插入过程中，对模式串进行一次线性遍历，当遍历完毕即表示将整个串插入完毕，结尾结点表示它是一个模式串的末尾，
}
void Ac_automation() {//BFS求出所有结点的fail指针
    node *p = root,*temp;
    root->fail = NULL;
    int i,head = tail = 0;//队列的头尾指针
    q[head++] = root;
    while (tail < head) {
        p = q[tail++];
        for (i = 0; i < 26; ++i) {//遍历所有子节点
            if (p->next[i] != NULL) {//该子节点有值时
                //对于根结点root的失败指针，我们将它直接指向NULL，对于根结点下所有的子结点，失败指针一定是指向root的
                //因为当一个字符都不能匹配的时候，自然也就不存在更短的能够与之匹配的前缀了
                if (p == root) p->next[i]->fail = root;
                else{
                    temp = p->fail;//父节点的失败指针
                    while (temp != NULL)  {//失败指针没有到达根节点时
                        if (temp->next[i] != NULL) {//不断往上查找，直到fail指针对应的节点有相同的子节点，结束当前结点的BFS
                            p->next[i]->fail = temp->next[i];
                            break;
                        }
                        temp = temp->fail;//如果该失败指针指向的节点没有与i相同的孩子，继续往上找
                    }
                    if (temp == NULL) //如果失败指针到达根节点，就是不存在最大前缀后缀和，队列中的节点的next[i]的fail指针只能是根节点
                        p->next[i]->fail = root;
                }
                q[head++] = p->next[i];//把当前结点存入队列
            }
        }
    }
}
int ifchecked(int x,int y) {//判断是否界内
    return x >= 0 && x < n && y >= 0 && y < l;
}
void AC(int xx,int yy,int t) {//以xx，yy为起点，t为方向，查找有无匹配串
    int x = xx,y = yy;
    node *p = root,*temp;
    while (ifchecked(x,y)) {
        int k = str[x][y] - 'A';
    //fail是用来寻找下次跳转的位置的，跳转时的 next一定是为空的。通过下面3条语句让p的next指针直接指向下一个跳转节点
        while (p->next[k] == NULL && p != root)//如果父节点P没有符合的子节点，就看点p的Fail点的孩子有无符合节点，直到p的fail指向根节点为止
            p = p->fail;
        p = (p->next[k] != NULL ? p->next[k] : root);
//由上一行while循环，现在只有2种可能：如果找到符合节点，那么更新p为下一个父节点；如果没找到，那么当前字符从来没有出现过，直接回到root
        temp = p;
        while (temp != root) {//如果之前找到符合字符，不断往fail指针查找，判断当前匹配串的后缀是不是所查找的单词
            if (temp->flag != -1) {//如果该字符是某个单词的结尾，存入ans，把当前单词的结尾标记重置
                ans[temp->flag].x = x;
                ans[temp->flag].y = y;
                ans[temp->flag].dir = t;
                temp->flag = -1;
            }
            temp = temp->fail;
        }
//如果temp=root，那么说明这个字符不属于任何一个单词，不做任何处理，等着下一个字符与字典树从root匹配（此时查找位置p已经变为root，不需要再重置）
        x += dir[t][0],y += dir[t][1];
    }
}
int main()
{
    int i,j,k,t;
    while (scanf("%d%d%d",&n,&l,&w) != EOF) {
        total = 0;
        root = new_node();//建立根节点
        for (i = 0; i < n; ++i)
            scanf("%s",str[i]);
        for (i = 0; i < w; ++i)//建立字典树
            scanf("%s",tp),Insert(tp,i);
        Ac_automation();
//从这个矩阵四周的每个点开始.每个点.八个方向扫过去~~边扫边在树中查找...八个方向就定义一个二维数组~~存下八个方向的x,y的走势
        for (i = 0; i < l; ++i) {
            AC(0,i,4),AC(0,i,3),AC(0,i,5);//上边界（只能往左下，下，右下走）
            AC(n-1,i,1),AC(n-1,i,0),AC(n-1,i,7);//下边界（只能往左上，上，右上走）
        }
        for (i = 0; i < n; ++i) {
            AC(i,0,1),AC(i,0,2),AC(i,0,3);//左边界（只能往右上，右，右下走）
            AC(i,l-1,5),AC(i,l-1,6),AC(i,l-1,7);//右边界（只能往左上，左，左下走）
        }
        for (i = 0; i < w; ++i)
            printf("%d %d %c\n",ans[i].x,ans[i].y,(ans[i].dir + 4) % 8 + 'A');
    }
}
