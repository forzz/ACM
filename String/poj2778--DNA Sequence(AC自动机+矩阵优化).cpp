#include<cstdio>
#include<cstring>
#include<queue>
#define INF 99999999
using namespace std;
const int MAX=100+10;//最大节点数
const int mod=100000;
long long array[MAX][MAX],sum[MAX][MAX];//进行矩阵乘法的初始矩阵和结果矩阵
int n,m,size;//size表示节点个数
char s[15];
int Map[MAX];//映射A,C,G,T = 0,1,2,3
struct TrieNode{
	int id;//表示该节点的序号
	bool mark;//标记是否是单词
	TrieNode *fail,*next[4];//失败指针和下一个节点
}*root,Node[MAX];//内存池和根节点
TrieNode *New_TrieNode(){//建立新节点
	memset(&Node[size],0,sizeof(TrieNode));
	Node[size].id=size;
	return &Node[size++];
}
void InsertNode(char *a){//加入新的DNA序列
	TrieNode *p=root;
	while(*a){
		if(!p->next[Map[*a]])p->next[Map[*a]]=New_TrieNode();
		p=p->next[Map[*a]];
		++a;
	}
	p->mark=true;
}
void Build_AC(){//建立AC自动机并且构造初始矩阵array
	memset(array,0,sizeof array);
	TrieNode *p=root,*next;
	queue<TrieNode *>q;
	q.push(root);
	while(!q.empty()){
		p=q.front();
		q.pop();
		for(int i=0;i<4;++i){//BFS
			if(p->next[i]){//如果存在值
				next=p->fail;
				while(next && !next->next[i])next=next->fail;//不断往上查找，直到fail指针对应的节点有相同的子节点
				p->next[i]->fail=next?next->next[i]:root;
//如果失败指针到达根节点（根节点fail指针为NULL），就是不存在最大前缀后缀和，队列中的节点的next[i]的fail指针只能是根节点
				if(p->next[i]->fail->mark)p->next[i]->mark=true;//防止ACG,AC这种一个病毒串的前缀是另一个病毒串的情况
				q.push(p->next[i]);
			}else p->next[i]=(p == root)?root:p->fail->next[i];//从这个点状态可以递推到失败指针节点的下一个节点状态
			if(!p->next[i]->mark)++array[p->id][p->next[i]->id];//表示下一个状态不是病毒串,则可以到达（构建矩阵）
		}
	}
}
void MatrixMult(long long a[MAX][MAX],long long b[MAX][MAX]){//矩阵乘法
	long long c[MAX][MAX]={0};
	for(int i=0;i<size;++i){
		for(int j=0;j<size;++j){
			for(int k=0;k<size;++k){
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	for(int i=0;i<size;++i){
		for(int j=0;j<size;++j)a[i][j]=c[i][j]%mod;
	}
}
long long MatrixPow(int k){//矩阵的k次方并求出结果
	for(int i=0;i<size;++i){
		for(int j=0;j<size;++j)sum[i][j]=(i == j);//单位矩阵
	}
	while(k){
		if(k&1)MatrixMult(sum,array);//sum=sum*array;
		MatrixMult(array,array);//array=array*array;
		k>>=1;
	}
	long long ans=0;
	for(int i=0;i<size;++i)ans+=sum[0][i];//从0状态到达其他状态的所有总和
	return ans%mod;
}
int main(){
        //因为n很大，若求两点之间的路，只能进行矩阵快速幂，普通dp无法实现
	Map['A']=0,Map['C']=1,Map['G']=2,Map['T']=3;
	while(scanf("%d%d",&m,&n)!=EOF){
		size=0;//节点个数初始化为0
		root=New_TrieNode();//创建根节点
		for(int i=0;i<m;++i){//加入字典树
			scanf("%s",s);
			InsertNode(s);
		}
		Build_AC();
		printf("%lld\n",MatrixPow(n));
	}
	return 0;
}
