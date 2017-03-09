#include <cstdio>
#include <cstring>
char s[10005][80], rs[80][10005];
int R[10005], C[10005];
int r, c;
void get_nextR()
{
    R[0] = -1;
    int j = -1, i = 0;//i表示模板字符串下标，j表示当前最大前后缀长度（由于nxt数组是从0开始，所以j表示最大前缀的下一位）
    while(i < r)//i表示失配位的前一位 也就是需要寻找前后缀的字符串的尾部
    {
        if(j == -1 || strcmp(s[i], s[j]) == 0)  ////j=-1表示比较到空位0，i和j如果相等，那么最大相同前后缀长度加1
        {
            i++;
            j++;
            R[i] = j;//失配位nxt值求出
        }
        else
            j = R[j];
    }
}
void get_nextC()
{
    C[0] = -1;
    int j = -1, i = 0;
    while(i < c)
    {
        if(j == -1 || strcmp(rs[i], rs[j]) == 0)
        {
            i++;
            j++;
            C[i] = j;
        }
        else
            j = C[j];
    }
}
int main()
{
    while(scanf("%d %d", &r, &c) != EOF)
    {
        for(int i = 0; i < r; i++)
            scanf("%s", s[i]);
        get_nextR();        //把每行字符串看作一个整体对行求next数组
        for(int i = 0; i < r; i++)      //将矩阵转置
            for(int j = 0; j < c; j++)
                rs[j][i] = s[i][j];
        get_nextC();//进行操作1，注意这里的行是原来的列，列是原来的行，相当于求原来列的next数组
        printf("%d\n", (r - R[r]) * (c - C[c]));
//最小覆盖子串(最小循环节)：n-next[n]
    }
}

