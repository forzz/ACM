#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <map>
#define MAX 307
using namespace std;
int n;
map<int,int> dp;
pair<int,int> a[MAX];
int gcd ( int a , int b )    {  return !b?a:gcd(b,a%b);  }
int main ( )
//dp[i][gcd] i从1到n gcd从1到最大值 数组太大，无法直接dp
{
    while ( ~scanf ("%d" , &n ) )
    {
        for ( int i = 0 ; i < n ; i++ )
            scanf ( "%d" , &a[i].first );
        for ( int i = 0 ; i < n ; i++ )
            scanf ( "%d" , &a[i].second );
        dp.clear();
        dp[0] = 0;
        for ( int i = 0; i < n ; i++ ) //遍历每张卡片
        {
            int x = a[i].first;    //宽度
            int c = a[i].second;   //花费
            for (auto it=dp.begin();it!=dp.end(); it++ )
            {
                int y = it->first;      //最大公约数
                int d = gcd ( x , y );  //最大公约数和当前宽度的最大公约数
                int temp = it->second+c; //新花费
                if ( dp[d] && dp[d] < temp ) continue;//不存在gcd为d的情况
//map的下标运算符[]的作用是：将关键码作为下标去执行查找，并返回对应的值；
//如果不存在这个关键码，就将一个具有该关键码和值类型的默认值的项插入这个map，并返回NULL
                dp[d] = temp;//更新最优解
            }
        }
        if ( !dp[1] ) puts ( "-1" );
        else printf ( "%d\n" , dp[1] );
    }
}
/*
1. map.end()指向map的最后一个元素之后的地址，无论执行map.erase(iter)还是map.add(key, value)，map.end()所返回的值永远不会发生变化，都是指向同一块内存。
2. map.begin()指向map的第一个元素，map.begin()可能随着map.erase(iter)或是map.add(key, value)操作而发生改变。例如当第一个元素被删除后，map.begin()就发生了改变，
指向原来第一个元素之后的那个元素了。或是如果新插入一个键值对,该键值对的key放到btree（我们假设map内部是由btree实现的，实际上也可能有别的实现方式）中会排在
map.begin()->first的前面，那么map.begin()也会指向新插入的这个键值对了。
3. map.erase(iter)执行后，当前iter就失去意义了，再执行++iter就会出问题。
*/
