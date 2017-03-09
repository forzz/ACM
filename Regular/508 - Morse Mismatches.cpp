#include <iostream>
#include<string>
#include<map>
using namespace std;
const int maxdif = 10000;
map<char, string> morse;
map<string, string> dict;

void encode(string &word)
{
	string res;
	for(int i = 0; i <= word.size(); i++)
		res += morse[word[i]];//将每个字符对应的摩斯码保存在res中
	dict[word] = res;        //dict保存的是每一行字符对应的准确摩斯码
}

int dif(string a, string b)
{
	if(a==b)   //如果a和b相等，返回0
		return 0;
	if(a.size() > b.size())//保证a为字符少的字符串
		swap(a, b);
	if(a == b.substr(0, a.size()))    //如果a为b的前一部分
		return b.size() - a.size();  //输出b比a多的字符数
	else
		return maxdif;    //无法匹配
}

string solve(const string &code)
{
	string x = dict.begin()->second; //第一行的准确摩斯码
	string ans = dict.begin()->first;//第一行字符
	int min_dif = maxdif;
	for(auto i = dict.begin(); i != dict.end(); i++)//每一行字符的所有摩斯码全部遍历
	{
		int d = dif(code, i->second);
		if(d < min_dif)//如果可以匹配且比之前的匹配更好
		{
			min_dif = d;  //保存最小不同数，越小，其字典序越小
			ans = i->first;//这是暂时结果
		}
		else if(d==0 && min_dif==0 && ans[ans.size()-1]!='!')//精确匹配
			ans += '!';
	}
	if(min_dif)//非精确匹配
		ans += '?';
	return ans;
}

int main()
{
	string a, b;
	while(cin >> a && a != "*")
	{
		cin >> b;
		morse[a[0]] = b;   //将摩斯码存到morse中，映射为其代表的字符
	}
	while(cin >> a && a != "*")
		encode(a); //把准确的摩斯码给写出来
	while(cin >> a && a != "*")//读入每一个摩斯码
		cout << solve(a) << endl;
	return 0;
}