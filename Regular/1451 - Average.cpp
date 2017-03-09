#include<deque>
#include<cstdio>
using namespace std;
deque<int> q;//双端队列
int s[100005];
int ansl,ansr;
int great(int a,int b,int c,int d)//求ab斜率是否大于cd斜率
{
    return (s[a]-s[b])*(c-d) - (s[c]-s[d])*(a-b);
}
int main()
{
    int t,L,n,a;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d ",&n,&L);
        char cc;
        for(int i=1;i<=n;i++){
            cc=getchar();
            s[i]=s[i-1]+cc-'0';//这样读才不会超时
        }
        q.clear();
        ansl=0;
        ansr=L;
        for(int i=L; i<=n; i++)//以i做线段右端点
        {
            int j=i-L;
            while(q.size()>1)//把j作为线段左端点，加入单调队列，队列内必须包含2个元素
            {//（单调指斜率单调递增）保证都是凹点   q存放所有合法点
                int b1=q[q.size()-1];//倒数第1个
                int b2=q[q.size()-2];//倒数第2个
                if(great(b1,b2,j,b1)>0)//如果b1b2斜率比jb1更大
                    q.pop_back();//弹出b1，维护单调性
                else break;//
            }
            q.push_back(j);//j入队
            while(q.size()>1)//去掉队前头不优的起点（线段左端点）
            {//因为和i斜率最大的是下凹线的切点，切点前的点不优
                if(great(i,q[0],i,q[1])<=0)//以i做终点 q[0]i的斜率小于q[1]i的斜率
                    q.pop_front();//就弹出队头（若此点不是当前i点的切点，那么更不是i下一点的切点，可以直接删除）
                else break;
            }
            int tmp=great(i,q[0],ansr,ansl);//i和切点的斜率，也就是最大斜率
            if(tmp>0 || tmp==0 && i-q[0]<ansr-ansl)//斜率更大或者斜率相同但长度更小
            {
                ansl=q[0];//左端点更新
                ansr=i;//右端点更新
            }
        }
        printf("%d %d\n",ansl+1,ansr);//存的是左端点右1的点，故输出时+1
    }
    return 0;
}
