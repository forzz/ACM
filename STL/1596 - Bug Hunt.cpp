#include <bits/stdc++.h>  //包含所有c++头文件，国外OJ可用
using namespace std;
int bug = -1;
vector<string> code;
map<char, int> a;   //名称和个数
map<string, int> val;
/*
<algorithm>头文件定义了一个count的函数，其功能类似于find。这个函数使用一对迭代器和一个值做参数，
返回这个值出现次数的统计结果。编写程序读取一系列int型数据，并将它们存储到vector对象中，然后统计
某个指定的值出现了多少次。
*/
int get_val(string str){
	if (str.find("[") == string::npos)        //不存在[  str只是一个单纯的整数
		return stoi(str);  //检测到非数字停止转化
	if (count(str.begin(), str.end(), '[') == 1){
		if (!val.count(str)) return -1;//如果之前不存在str，返回-1
		return val[str];//存在str，返回str
	}
	if (count(str.begin(), str.end(), '[') >= 2){  //是a[b[n]]类
		string cur = str.substr(str.find('[') + 1);//拆掉最外层 [
		int v = get_val(cur);//递归再求值
		if (!val.count(str.substr(0, 2) + to_string(v)))//to_string(v)将整型的数字，转化为字符串。
			return -1;                    //转化为a[n
		return val[str.substr(0, 2) + to_string(v)];
	}
}
void add_arr(const string str){
	stringstream ss(str.substr(2));
	int v; ss >> v;   //查到初始化数组个数
	a[str[0]] = v;//初始化数组名称
}
int main()
{
	ios::sync_with_stdio(false);//取消cin与stdin的同步，使io与scanfprintf速度基本相同
	while (code.clear(), val.clear(), code.clear(), bug = -1, true){
		string line; cin >> line;
		if (line == ".") break;
		while (true){//不断读入code
			code.push_back(line);
			cin >> line;
			if (line == ".") break;
		}
		for (size_t i = 0; i != code.size(); i++){
			if (code[i].find("=") == string::npos)//返回一个名为 string::npos，说明查找没有匹配
				add_arr(code[i]);            //处理初始化语句
			else{    //处理赋值语句
				string l = code[i].substr(0, code[i].find('='));//截取从0到=的字符串（双地址）
				string r = code[i].substr(code[i].find('=') + 1);//截取从=+1到结尾的字符串（单地址）
				int rval = get_val(r.substr(0, r.find(']')));
	/*左值去掉最外层括号*/	int lval = get_val(l.substr(l.find('[') + 1, l.find(']') - l.find('[') - 1));
				if (rval == -1 || lval == -1) {bug = i; break; }//使用未初始化变量
				if (!a.count(code[i][0]) || lval >= a[code[i][0]]) { bug = i; break; }//数组越界
				string name = code[i].substr(0, 2) + to_string(lval);//a[n+lval
				val[name] = rval;  // ↑ 地址+字符数
			}
		}
		cout << bug + 1 << endl;
	}
	return 0;
}
