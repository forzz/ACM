#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
#define nodesize 4000004      //节点个数（100000*4）
#define dictsize 10           //字符集大小
typedef struct node1
{
        int    id;     //表示路径
        int    flag;            //表示值存在
        node1* next[dictsize];//保存指针
}tnode;
tnode  dict[nodesize];
int    ID[256];
class Trie  //构造一棵字典树,比对前缀需要字典树
{
    private:
        int    size;
        tnode* root;
    public:
        Trie() {makeID(); initial();}//构造函数包括两个
        void makeID() {
            for ( int i = 0 ; i < 10 ; ++ i )//256个字符进行标号
                ID['0'+i] = i;
        }
        void initial() {//初始化root
            memset( dict, 0, sizeof( dict ) );
            root=NULL; size=0; root=newnode();
        }
        tnode* newnode() {return &dict[size ++];}//定义了newnode函数 返回下一个tnode所在的地址
        void insert( char* word, int L, int id ) {
            tnode* now = root;                 //从根节点开始找
            for ( int i = 0 ; i < L ; ++ i ) {//逐个存储
                if ( !now->next[ID[word[i]]] )        //如果没有该子节点
                    now->next[ID[word[i]]] = newnode();    //建立一个新节点
                if ( !now->id && !now->flag ) now->id = id;  //因为目标是输出最小的数，如果之前没路径才标记路径（fibonacci数是从小到大求的）
                now = now->next[ID[word[i]]];
            }
			if ( !now->flag ) {  //flag代表存在一个值
				now->flag = 1;
				now->id = id;
			}
        }
        int query( char* word ) {  //查找
            tnode* now = root;
            for ( int i = 0 ; word[i] ; ++ i ) {
                if ( !now->next[ID[word[i]]] ) return -1;
                now = now->next[ID[word[i]]];
            }
			return now->id;
        }
}trie;
int  F[2][21000];//因为每个斐波那契数都存到字典树中，这里直接滚动数组，用整型数组形式处理大数，单独考虑进位
char FF[42],In[42];
int main(){
    memset(F, 0, sizeof(F));
    F[0][0]  = F[1][0] = 1;    //初始化前两个数
    trie.insert("1", 1, 0);
    int s=0, l=1, r, count, p, q;   //s表示数组的起始位置，l表示数组的结束位置(l不存数)，并不是完整的fibonacci数，至多截取前50位，剩下全部舍弃
    for(int i=2;i<100000; i++){
        p = i%2, q = (i+1)%2;     //生成100000个Fibonacci数，滚动数组
        for(int j=s; j<l; ++j)
            F[p][j] = F[p][j] + F[q][j];   //将前两个数每一位都相加
        for(int j=s; j < l; ++j)
        if(F[p][j] >= 10){//判断每一位相加后是否大于10，如果是，说明要进位；注意，这里是反向存储数字的,也就是说，{4,3,2,1}，表示的是1234
            F[p][j+1]+=1;
            F[p][j] -= 10;
        }
        if(F[p][l]) l++;//更新最大位置，因为l最多只能增加一位，用if足够
        if(l-s>50) s++;   //只需要前40个数，为了保证前40位的精度，需要取到前50位
        r=l-1; count=0;  //r表示首位数字
        while(r>=0 && count < 40)
            FF[count ++] = F[p][r--]+'0';//把F中的数按照正序取出并保存到FF字符数组中，存到字典树中，同时count保存数位
        trie.insert(FF, count, i);
    }
    int T;
    while(scanf("%d", &T)!=EOF)
    for(int t=1; t<=T; ++t){
        scanf("%s",In);
        printf("Case #%d: %d\n",t,trie.query(In));
    }
    return 0;
}

