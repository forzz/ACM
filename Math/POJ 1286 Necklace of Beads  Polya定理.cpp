#include <iostream>
#include <map>
#include <vector>
using namespace std;
#define LL long long
inline LL power(LL p, LL n)//快速幂
{
	LL sum = 1;
	while (n)
	{
		if (n & 1)
			sum *= p;
		p *= p;
		n /= 2;
	}
	return sum;
}
vector<int> divisor(const int& n)//枚举所有的约数
{//n很大时，对大多数i， gcd(n,i)的值都相同，都是n的约数，用sqrt(n)的复杂度枚举n的约数
	vector<int> res;
	for (int i = 1; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			res.push_back(i);
			if (i != n / i)
			{
				res.push_back(n / i);
			}
		}
	}

	return res;
}
map<int, int> prime_factor(int n)//整数分解成多个约数相乘
{
	map<int, int> res;
	for (int i = 2; i * i <= n; ++i)
	{
		while (n % i == 0)
		{
			++res[i];
			n /= i;
		}
	}
	if (n != 1)
	{
		res[n] = 1;
	}
	return res;
}

LL polya(const int& m, const int& n)
{
	map<int, int> primes = prime_factor(n);//整数分解成多个约数相乘(数组中每个元素保存该约数的个数)
	vector<int> divs = divisor(n);//约数枚举
	LL res = 0;
	for (int i = 0; i < divs.size(); ++i)
	{// 求divs[i]的欧拉函数值,也代表了循环节长度为i的置换个数
		LL euler = divs[i];
		for (map<int, int>::iterator it = primes.begin(); it != primes.end(); ++it)
		{
			int p = it->first;//约数
			if (divs[i] % p == 0) euler = euler / p * (p - 1);
		}
		res += euler * power(m, n / divs[i]);
	}
	return res;
}
int main()
{
//gcd（i,n)表示了循环节的个数。用L表示循环节的长度L=n/gcd(i,n)，
//如果我们枚举L，求出对于每一个L有多少个i, 使得 L = n / gcd (i,n)， 那么我们实际上也得到了循环节个数为 n / L 的置换个数。
//循环节长度为L的置换有Euler(L)个
	int n; const LL m = 3;
	while (~scanf("%d", &n) && n != -1)
	{
		if (n == 0)
		{
			puts("0");
			continue;
		}

		LL count = polya(m, n);//旋转情况3^gcd(n,i)
		if (n & 1)//奇数
			count += n * power(m, n / 2 + 1);
		else//偶数
			count += (power(m, n / 2 + 1) + power(m, n / 2)) * (n / 2);
		count /= 2 * n;
		printf("%lld\n", count);
	}

	return 0;
}
/*
旋转：n个点顺时针旋转i个位置的置换，循环数为gcd(n,i)，方案数为3^gcd(n,i)
翻转：n为偶数时， 对称轴不过顶点的循环数为n/2，方案数为3(n/2)
                  对称轴过顶点的循环数为n/2+1，方案数为3^(n/2+1)
    n为奇数时，循环数为(n+1)/2，方案数为3^((n+1)/2)
*/
