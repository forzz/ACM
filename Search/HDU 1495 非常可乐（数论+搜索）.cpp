#include <queue>
#include <cstring>
using namespace std;
int b[3],book[101][101][101],half;
struct node
{
    int cur[3],s;          //cur表示现在瓶子里的水，b表示水的容量
}p,temp;          //p获取当前的“head”，temp用于6个动作的记录。
void bfs()
{
    queue<node> q;
    //如果把这句放在bfs（）外边，因为有多组测试数据，如果不把之前队列里的数据清空就会带到下一组测试
    p.cur[0]=b[0];
    p.cur[1]=p.cur[2]=p.s=0;
    q.push(p);
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        for(int i=0;i<3;i++)     //控制哪个杯子往外倒水
        {
            if(p.cur[i]>0)      //如果有水才可以给别的倒水。
            {
                for(int j=0;j<3;j++)   //接受水的杯子
                {
                    temp=p;            //这很重要！之前没加这句一直wa，因为这6个动作是”平行“的，即都是从前一步状态开始的，如果没有
                    if(i==j)  continue ;   //这一句，就不是平行的，相互叠加的。这个很重要！
                    if(temp.cur[i]>b[j]-temp.cur[j])   //判断能不能倒满了，这是可以倒满的情况
                    {
                        temp.cur[i]-=b[j]-temp.cur[j];      //这两句话一定不要颠倒，之前因为这个一直不出答案，先运算后赋值。。。
                        temp.cur[j]=b[j];
                    }
                    else     // 不可以倒满的情况
                    {
                        temp.cur[j]+=temp.cur[i];
                        temp.cur[i]=0;
                    }
                    if(!book[temp.cur[0]][temp.cur[1]][temp.cur[2]])  //判断这种情况是否出现过
                    {
                        book[temp.cur[0]][temp.cur[1]][temp.cur[2]]=1;  //标记为出现过，说明这一步“有效”，step+1；
                        temp.s++;
                        if((temp.cur[0]==half&&temp.cur[1]==half)||(temp.cur[0]==half&&temp.cur[2]==half)||(temp.cur[1]==half&&temp.cur[2]==half))
                            {
                                cout << temp.s << endl;  // step里的每一个“动作”都要判断是否符合条件，因为这动作是平行的 所以放在内循环里面！
                                return ;             //直接跳出bfs
                            }
                            q.push(temp);// 如果不是所求，就把他加到队列里。之后在从每一个“动作调用”
                    }
                }
            }
        }


    }
      cout <<"NO"<<endl;  //如果整个循环结束还是没有找到说明不可以平分；
}
int main()
{
    while(cin >> b[0]>>b[1]>>b[2],b[0]+b[1]+b[2])   //如果相加都等于0 即000 用于结束
    {
        memset(book,0,sizeof(book));  //多组数据每一组都要赋初值，想用book【】【】=｛0｝，必须要在声明book数组时候用；
        book[b[0]][b[1]][b[2]]=1;   //把初始点标记来过，这一点在调用bfs之前做 很多题都要注意这一点。
        if(b[0]%2)  cout << "NO"<<endl;
        else {half=b[0]/2;bfs();}
    }
    return 0;
}
/*
#include<cstdio>
#include<iostream>
using namespace std;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    int a,b,c;
    while(scanf("%d%d%d",&a,&b,&c),a+b+c)
    {
        a/=gcd(b,c);
        if(a&1)printf("NO\n");
        else printf("%d\n",a-1);
    }
    return 0;
}
*/
