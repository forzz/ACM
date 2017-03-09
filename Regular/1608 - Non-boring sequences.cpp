#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int MAX = 200010;
int N,T;
int a[MAX],l[MAX],r[MAX];
bool solve(int left, int right)
{//如果某个序列中包含唯一数字，那所有跨过该数字的序列都是不无聊的，所以我们只需判断其左右是否是不无聊的序列即可。
    if(left >= right)//左比右大，直接返回
        return true;
    for(int i = 0; i <= (right - left) / 2; ++i){//枚举每一个没有重复的数字
        if(l[left + i] < left && r[left + i] > right)//从左边到中间搜索
            return solve(left, left + i - 1) && solve(left + i + 1,right);
        if(l[right - i] < left && r[right - i] > right)//从右边到中间搜索
            return solve(left,right - i - 1) && solve(right - i + 1, right);
    }
    return false;
}

int main(void)
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&N);
        for(int i = 0; i < N; ++i)
            scanf("%d",&a[i]);
        map<int, int> M;
        for(int i = 0; i < N; ++i){//正序遍历
            if(!M.count(a[i])) l[i] = -1;
            else l[i] = M[a[i]];//记录在i之前的最近的相同元素的编号
            M[a[i]] = i;//cur保存A[i]的编号
        }
        M.clear();
        for(int i = N - 1; i >= 0; --i){//逆序遍历
            if(!M.count(a[i])) r[i] = N;
            else r[i] = M[a[i]];//记录在i之后的最近的相同元素的编号
            M[a[i]] = i;//cur保存A[i]的编号
        }
        if(solve(0,N-1))
            puts("non-boring");
        else
            puts("boring");
    }
    return 0;
}
