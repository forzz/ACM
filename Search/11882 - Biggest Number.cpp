#include<algorithm>
#include<vector>
#include<cstring>
#include<cstdio>
using namespace std;
struct Node
{
	int val, x, y;
	bool operator<(const Node&r)const
	{
		return val>r.val;
	}
};
int cnt;
int n, m, maxd;//maxd表示答案的长度
#define N 35
#define For(i,n) for(int i=0;i<(n);i++)
int b[N], c[N];//b数组存放答案，c数组是当前待尝试的结果
int vis[N][N];
int a[N][N];//存放输入的数字，'#'均用0表示
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };
int find(int x, int y)//寻找(x,y)后面最多还有多少个可连接数
{
	int ret = 0;
	vis[x][y] = cnt;
	For(k, 4){    //四种方向
		int i = x + dx[k], j = y + dy[k];
		if (!a[i][j] || vis[i][j] == cnt)continue;//如果是障碍或者在该次寻找中被访问
		ret += find(i, j) + 1;//递归寻找
	}
	return ret;
}
bool dfs(int cur, int val, int x, int y, bool same)//当前位置为cur,待填入的值为val,坐标为(x,y)，same表示cur之前的数字和目前的答案是否完全一致,返回是否更新过答案
{
	if (same&&val < b[cur])return 0;//如果cur之前所有位都相等 且 当前cur位置的数<以往找到的数，剪枝（1）
	if (val>b[cur])same = 0;//如果大于，说明不相等
	c[cur] = val;
	if (cur == maxd){//满足目标长度
		for (int i = 1; i <= maxd; i++)
			b[i] = c[i];
		return 1;//找到了一个答案，返回1，表示更新过答案
	}
	int res = maxd - cur; cnt++;//res表示还需要找的数字个数，cnt表示查找的次数，也作为标记数
	if (find(x, y) < res)return 0;//如果剩余的可连接数字个数<需要的数字个数，剪枝（2）
	vector<Node>L;//每个dfs中都会建立一个vector
	For(k, 4){
		int i = x + dx[k], j = y + dy[k];
		if (!a[i][j])continue;
		L.push_back(Node{ a[i][j], i, j });//后继结点都放入L中
	}
	sort(L.begin(), L.end());//排序，从较大的后继结点开始搜索
	bool o = 0;
	For(i, L.size()){
		int&t = a[L[i].x][L[i].y]; //搜索格的值
		int tmp = t; t = 0;  //暂时清0
		o |= dfs(cur + 1, L[i].val, L[i].x, L[i].y, same); //如果返回1，则o为1；如果返回0，则o为0
		if (o)same = 1;
		t = tmp;
	}
	return o;
}
char st[100];
void solve()
{
	vector<Node>L;
	memset(a, 0, sizeof(a));
	memset(vis, 0, sizeof(vis));
	memset(b, 0, sizeof(b)); cnt = 0;
	maxd = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", st + 1);
		for (int j = 1; j <= m; j++)
		{
			if (st[j] != '#'){//将障碍忽略
				a[i][j] = st[j] - '0';
				L.push_back(Node{ a[i][j], i, j }); //读入全部数据
				maxd++;
			}
		}
	}
	sort(L.begin(), L.end());//将数值较大的结点放到前面
	for (; maxd >= 1; maxd--)//从长度最大的开始尝试，如果无解，换为小一点的，这样的一个好处是容易比较大小，可以进行剪枝
	{
		bool o = 0;
		for (int i = 0; i < L.size(); i++){
			int&t = a[L[i].x][L[i].y];
			int tmp = t; t = 0;//暂时让(x,y)处的值消失，递归结束后恢复
			o |= dfs(1, L[i].val, L[i].x, L[i].y, 1);//默认same初始值为1
			t = tmp;//恢复该位置的值
		}
		if (o)break;//当前答案长度的限制下找到了解，直接break
	}
	for (int i = 1; i <= maxd; i++)
		printf("%d", b[i]);
	puts("");
}
int main()
{
	while (~scanf("%d%d", &n, &m) && (n || m))
		solve();
	return 0;
}
