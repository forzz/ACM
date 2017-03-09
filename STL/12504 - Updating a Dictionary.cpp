#include<bits/stdc++.h>
using namespace std;
map<string, string> d[2];
map<string, string>::iterator it;//建立map类型的迭代器 类似指针
const int N = 105;
string s, a, b, t[N];

void print(char c, int n)
{
    sort(t, t + n), cout << c << t[0];
    for(int i = 1; i < n; ++i) cout << ',' << t[i];
    cout<<"\n";
}

int main()
{
    int cas, n, c1, c2, c3;
    cin >> cas;
    while(cas--)
    {
        d[0].clear(), d[1].clear();
        for(int i = 0; i < 2; ++i)
        {
            cin >> s;
            int j = 1, l = s.size();
            while(l > 2 && j < l)
            {
                while(s[j] != ':')
                        a += s[j++]; //a为键
                ++j;
                while(s[j] != ',' && s[j] != '}')
                        b += s[j++];//b为值
                ++j;
                d[i][a] = b, a = b = "";//重新初始化
            }
        }
        c1 = c2 = c3 = 0;   //所有公用一个数组t，因为知道个数，不会出现错误
        for(it = d[1].begin(); it != d[1].end(); ++it)//遍历新的字典
            if(!d[0].count(it->first)) t[c1++] = it->first;//如果不存在it键，把it的键存到t数组中
        if(c1) print('+', c1);

        for(it = d[0].begin(); it != d[0].end(); ++it)//遍历旧的字典
            if(!d[1].count(it->first)) t[c2++] = it->first;//如果不存在it键，把it的键存到t数组中
        if(c2) print('-', c2);

        for(it = d[1].begin(); it != d[1].end(); ++it)
            if(d[0].count(it->first) && d[0][it->first] != it->second) t[c3++] = it->first;
        if(c3) print('*', c3);

        if(!(c1 || c2 || c3)) puts("No changes");
        cout<<"\n";
    }
    return 0;
}
/*
while(~scanf("%d",&n))
<=>  while(scanf("%d",&n)!=EOF)
1.正常输入的时候，scanf返回输入的数字如1,2,3等等，对这些数字取非，不会成为0，就会执行循环；
2.错误输入指的就是没有输入的时候，scanf返回的是EOF（End Of File），EOF=-1，对EOF取非，就是对-1取非
[~是位运算，它是将数据在内存中的每一位（当然是二进制）取反。-1在内存中所有位全部为1，~(-1)=0,即对-1取非就是0]
*/
