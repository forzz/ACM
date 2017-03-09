/*
设原数字长为n，那么除去m个数字后还剩n-m个数字。
（1）因为有n-m个数字，那么在1到m+1位置中最小的那个数字必是结果中的第一个数字，记录其位置为pos
（2）然后从这个位置的下个位置pos+1开始到m+2位置的数字中最小的那个数字必定是结果中第二个数字，以此类推下去向后找。
（3）为了保证数字最小,所以要保证高位最小,还要保证数字长度满足条件
*/
#include<cstdio>
#include<cstring>
#include<cmath>
char s[1010];
char ans[1020];
int st[1010][20];
int Min(int x,int y)
{
    return s[x] <= s[y] ? x : y;
}

void ST(int len)
{
    for(int i = 0; i < len; i++)
    st[i][0] = i;
    for(int j = 1; (1<<j) < len; j++)
    for(int i = 0; i+(1<<j)-1 < len;i++)
    st[i][j] = Min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}

int RMQ(int l,int r)
{
    int k = (int)(log((double)(r-l+1))/log(2.0));
    return Min(st[l][k],st[r-(1<<k)+1][k]);
}

int main()
{
    int len, m, i;
    while(scanf("%s%d",s, &m)!=EOF)
    {
        len = strlen(s);
        ST(len);
        m = len - m;
        int pos = 0, num = 0;
        while(m--)//按顺序找到每个数字的位置，保存到ans中
        {
            pos = RMQ(pos, len - m - 1);
            ans[num++] = s[pos++];
        }
        for(i = 0; i < num; i++)
            if(ans[i]!='0')//消去前面的0
                break;
        if(i == num)//如果全是0，输出0
            printf("0");
        else
        {
            while(i < num)
                printf("%c",ans[i++]);
        }
        printf("\n");
    }
    return 0;
}
/*
区间最值查询（RMQ），对于长度为n的数列A，回答若干询问RMQ（A,i,j）(i,j<=n)，返回数列A中下标在i，j之间的最小/大值。
1.预处理
        DP状态：设A[i]是要求区间最值的数列，[i, j]表示从第i个数起连续2^j个数中的最大值
        DP初值：[i,0]=A[i]
        状态转移方程：[i, j]=max（[i，j-1], [i + 2^(j-1)，j-1]）
        for循环外层是j，内层是i，不可以互换。
                状态转移方程的含义是：先更新所有长度为[i,0]即1个元素，然后通过2个1个元素的最值，获得所有长度为[i,1]
                即2个元素的最值，再通过2个2元素的最值，获得所有长度为[i,2]即4个元素的最值，以此类推更新所有长度的最值。
                而如果是i在外，j在内的话，我们更新的顺序就是[1,0],[1,1],[1,2],[1,3],表示更新从1开始1个元素，
                2个元素，4个元素，8个元素（A[0],A[1],....A[7]）的最值，
                这里[1,3] = max(max(A[0],A[1],A[2],A[3]),max(A[4],A[5],A[6],A[7]))的值，
                但是我们根本没有计算max(A[0],A[1],A[2],A[3])和max(A[4],A[5],A[6],A[7])，所以这样的方法肯定是错误的。
2.查询
假如我们需要查询的区间为(i,j)，那么我们需要找到覆盖这个闭区间(左边界取i，右边界取j)的最小幂
（可以重复，比如查询5，6，7，8，9，我们可以查询5678和6789）。
因为这个区间的长度为j - i + 1,所以我们可以取k=log2( j - i + 1)，
则有：RMQ(A, i, j)=max{[i , k], [ j - 2 ^ k + 1, k]}。
举例说明，要求区间[2，8]的最大值，k = log2（8 - 2 + 1）= 2，
即求max([2, 2]，[8 - 2 ^ 2 + 1, 2]) = max([2, 2]，[5, 2])；
*/
