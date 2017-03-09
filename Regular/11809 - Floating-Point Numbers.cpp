#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	double M[20][40];//多留一些空间
	long long E[20][40];

	// 打表，一共只有300种不同情况
	for(int i = 0; i <= 9; ++i) //当前位数为i和j
		for(int j = 1; j <= 30; ++j) {
		double m = 1 - pow(2, -1 - i), e = pow(2, j) - 1;//m为十进制表示 e也为十进制表示
		double t = log10(m) + e * log10(2);//m * 2^e = A * 10^B        t = log10(A) + B
		E[i][j] = t;   //B整数部分（E数组是long long int 直接向下取整）
		M[i][j] = pow(10, t - E[i][j]); //A = 10^(t - B)。
	}

	// 输入并输出结果
	string in;
	while(cin >> in && in != "0e0") {
		// 处理输入
		for(auto i = in.begin(); i != in.end(); ++i) if(*i == 'e') *i = ' ';//稍微进行一下处理，让输入流更方便
		istringstream ss(in);
		double A; int B;
		ss >> A >> B;
		while(A < 1) A *= 10, B -= 1;//A不是科学计数法时需要再次操作
		// 在打好的表中寻找答案，遍历
		for(int i = 0; i <= 9; ++i) for(int j = 1; j <= 30; ++j) {
			if(B == E[i][j] && (fabs(A - M[i][j]) < 1e-4 || fabs(A / 10 - M[i][j]) < 1e-4)) {
				cout << i << ' ' << j << endl;
				break;
			}
		}
	}
}
