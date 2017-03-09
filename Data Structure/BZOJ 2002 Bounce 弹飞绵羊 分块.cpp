#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=200000 + 10;
int n,m,cmd;
int k[maxn],nex[maxn],s[maxn],belong[maxn];
//k代表弹性系数，next代表该元素的后继，s表示中间的距离，belong的值表示属于哪一个块
void make(int i){//从后往前预处理
//分块算法通过预处理，使得每个点在经过一个块时如果下一步还是当前块，就可以直接跳到下一个块，节省了很多时间
        int t=i+k[i];//t为i的下一个节点
        if(t>=n) t=n;//到了n就是边界了
        if(belong[i]==belong[t]){//维护块内信息
                nex[i]=nex[t];//相同块内的后继都是一样的
                s[i]=s[t]+1;//这个距离是倒过来算的，从后面往前面算距离
        }
        else{
                nex[i]=t;//跨块的时候就是直接将后继指向下一个块
                s[i]=1;//跨块的时候的距离就是1了，这个距离后面总要加上
        }
}
int main(){
        while(scanf("%d",&n)==1){//n个装置
                for(int i=0;i<n;i++)
                        scanf("%d",&k[i]);
                int mod=(int)sqrt(n);//每块大小
                for(int i=(n-1);i>=0;i--)
                        belong[i]= (i/mod);//将每个元素所在的块进行分类，标记每个元素所在的块
                for(int i=(n-1);i>=0;i--)
                        make(i);//对该元素进行分块处理
                scanf("%d",&m);
                while(m--){
                        scanf("%d",&cmd);
                        if(cmd==1){//查询
                                int b,ans=0;
                                scanf("%d",&b);
                                for(int i=b;i<n;i=nex[i])
                                        ans+=s[i];//只需要不断地将这些距离进行相加即可
                                printf("%d\n",ans);
                        }
                        else{
                                int loc,t;
                                scanf("%d%d",&loc,&t);
                                k[loc]=t;
                                for(int i=loc;i>=0;i--){
                                        if(belong[i]==belong[loc]) make(i);
                                        else break;
                                }
                        }
                }
        }
        return 0;
}
