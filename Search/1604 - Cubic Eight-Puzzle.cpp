#include <iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;
const int d1 = 21;
const int d2 = 9;
const int M = 100005;
const int N = 1679616;//6^8
bool flag[2][N][9];//3690kb
int fac[] = {1,6,36,216,1296,7776,46656,279936};

//6个状态：
//状态号   上   前  右
//0        W    R    B
//1        W    B    R
//2        R    W    B
//3        R    B    W
//4        B    W    R
//5        B    R    W
int roll[6][2] = {{2,5},{4,3},{0,4},{5,1},{1,2},{3,0}};
//6个状态分别往上下左右4个方向转一步到达的新状态

struct node
{
    int state;
    short int pos,step;
}ss,now;

struct que
{
    struct node t[M];
    int head,tail;
    void init()
    {
        head = tail;
    }
    bool empty()
    {
        return head == tail;
    }
    struct node top()
    {
        return t[head];
    }
    void pop()
    {
        head ++;
        if(head == M)
            head = 0;
    }
    void push(struct node a)
    {
        t[tail] = a;
        tail ++;
        if(tail == M)
            tail = 0;
        if(tail + 1 == head)
            printf("queue full\n");
    }
}q[2];
int x,y;
int endstate[10];
int endpos;

void dfs(int cur,int sum,int dp)
{
    if(cur == -1)
    {
        ss.state = sum;
        ss.pos = endpos;
        ss.step = 0;
        q[1].push(ss);
        flag[1][ss.state][ss.pos] = 1;
        return;
    }
    if(endstate[cur] == -1)
        dfs(cur - 1,sum,dp);
    else
    {
        int i;
        for(i = endstate[cur];i <= endstate[cur] + 1;i ++)
            dfs(cur - 1,sum + i * fac[dp],dp + 1);
    }
}

int getdigit(int a,int b)//从6进制数a中得到低位第b+1位
{
    int ret;
    a /= fac[b];
    ret = a % 6;
    return ret;
}

int main()
{
    int i,j,k;
    char s[3];
    while(scanf("%d%d",&y,&x),(x + y))
    {
        for(i = 0;i < 3;i ++)
        {
            for(j = 0;j < 3;j ++)
            {
                scanf("%s",s);
                switch(*s)
                {
                    case 'W':endstate[i * 3 + j] = 0;break;
                    case 'R':endstate[i * 3 + j] = 2;break;
                    case 'B':endstate[i * 3 + j] = 4;break;
                    case 'E':endstate[i * 3 + j] = -1;
                    endpos = i * 3 + j;break;
                }
            }
        }
        x --;
        y --;
        q[0].init();
        q[1].init();
        memset(flag,0,sizeof(flag));
        ss.pos = x * 3 + y;
        ss.state = ss.step = 0;
        q[0].push(ss);
        flag[0][0][ss.pos] = 1;
        dfs(8,0,0);//
        if(flag[1][q[0].top().state][q[0].top().pos])
        {
            printf("0\n");
            continue;
        }
        int ans = -1;
        int t1,t2;
        k = 0;
        for(j = 0;j < d1 && ans < 0;j ++)
        {
            for(i = 0;i <= 1;i ++)//2个队列  0正向搜  1反向搜
            {
                while(!q[i].empty())// && q[i].top().step == j)
                {
                    if(i)//反向
                    {
                        if(!(q[i].top().step == k && k < d2))
                            break;
                    }
                    else
                    {
                        if(!(q[i].top().step == j))
                            break;
                    }
                    now = q[i].top();
                    q[i].pop();
                    if(now.pos >= 3)//empty up
                    {
                        ss = now;
                        ss.step ++;
                        t1 = getdigit(now.state,10 - now.pos);
                        t2 = roll[t1][0];
                        ss.pos -= 3;
                        ss.state -= (t1 * fac[10 - now.pos]);//
                        t1 = getdigit(now.state,9 - now.pos);
                        ss.state -= (t1 * fac[9 - now.pos]);
                        ss.state += (t1 * fac[10 - now.pos]);
                        t1 = getdigit(now.state,8 - now.pos);
                        ss.state -= (t1 * fac[8 - now.pos]);
                        ss.state += (t1 * fac[9 - now.pos]);
                        ss.state += (t2 * fac[8 - now.pos]);//
                        if(!flag[i][ss.state][ss.pos])
                        {
                            flag[i][ss.state][ss.pos] = 1;
                            if(flag[1 - i][ss.state][ss.pos])
                            {
                                ans = i?j + k + 2:j + k + 1;
                                break;
                            }
                            q[i].push(ss);
                        }
                    }
                    if(now.pos <= 5)//empty down
                    {
                        ss = now;
                        ss.step ++;
                        ss.pos += 3;
                        t1 = getdigit(now.state,5 - now.pos);
                        t2 = roll[t1][0];
                        ss.state -= (t1 * fac[5 - now.pos]);
                        t1 = getdigit(now.state,6 - now.pos);
                        ss.state += (t1 * fac[5 - now.pos]);
                        ss.state -= (t1 * fac[6 - now.pos]);
                        t1 = getdigit(now.state,7 - now.pos);
                        ss.state += (t1 * fac[6 - now.pos]);
                        ss.state -= (t1 * fac[7 - now.pos]);
                        ss.state += (t2 * fac[7 - now.pos]);
                        if(!flag[i][ss.state][ss.pos])
                        {
                            flag[i][ss.state][ss.pos] = 1;
                            if(flag[1 - i][ss.state][ss.pos])
                            {
                                ans = i?j + k + 2:j + k + 1;
                                break;
                            }
                            q[i].push(ss);
                        }
                    }
                    if(now.pos % 3)//empty left
                    {
                        ss = now;
                        ss.step ++;
                        ss.pos --;
                        t1 = getdigit(now.state,8 - now.pos);
                        t2 = roll[t1][1];
                        ss.state -= (t1 * fac[8 - now.pos]);
                        ss.state += (t2 * fac[8 - now.pos]);
                        if(!flag[i][ss.state][ss.pos])
                        {
                            flag[i][ss.state][ss.pos] = 1;
                            if(flag[1 - i][ss.state][ss.pos])
                            {
                                ans = i?j + k + 2:j + k + 1;
                                break;
                            }
                            q[i].push(ss);
                        }
                    }
                    if((now.pos + 1) % 3)//empty right
                    {
                        ss = now;
                        ss.step ++;
                        ss.pos ++;
                        t1 = getdigit(now.state,7 - now.pos);
                        t2 = roll[t1][1];
                        ss.state -= (t1 * fac[7 - now.pos]);
                        ss.state += (t2 * fac[7 - now.pos]);
                        if(!flag[i][ss.state][ss.pos])
                        {
                            flag[i][ss.state][ss.pos] = 1;
                            if(flag[1 - i][ss.state][ss.pos])
                            {
                                ans = i?j + k + 2:j + k + 1;
                                break;
                            }
                            q[i].push(ss);
                        }
                    }
                }
                if(ans > 0)
                    break;
            }
            if(k < d2)
                k ++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
