#include <iostream>
#include<cstdio>
using namespace std;
long long  n;
int main()
{
    cin>>n;
    while(n%3==0)
    n/=3;
    cout<<n/3+1<<endl;
    return 0;
}
