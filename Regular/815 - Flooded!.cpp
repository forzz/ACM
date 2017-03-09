#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N m * n
#define V_WATER (water[i + 1] - water[i])
using namespace std;
int water[1000];
int main() {
	int m, n, times = 0;//times表示第几组数据
	double V;
	while(cin >> m >> n&& m) {
		double k = m * n, d = 1, sum = 0;
		double vegion = 0, tall = 0;
		for(int i = 0; i < N; i++)
			cin >> water[i];        //读入每个网格的海拔
		cin >> V;                //水总体积为V
		V /= 100;                       //V直接进行转化 变成总高度
		sort(water, water + N);  //排序
		tall = water[0];          //初始tall为最小的海拔
		for(int i = 0; i < N - 1; i++) {//遍历
			sum += d * (V_WATER);   //sum为增加i+1格子后能存多少水
			if(sum < V) {
				vegion = sum;
				tall += V_WATER; //这时tall就是i+1个格子中最高的海拔
				d++;  //d是已经有水的格子数
			} else {
				tall += (V - vegion) / d;  //如果i+1格子不需要完全浸没，那么需要计算一下需要多高
				sum += d * (V - vegion);
				break;
			}
		}
		if(sum < V)
			tall += (V - sum) / d;
		cout << "Region " << ++times << endl;
		printf("Water level is %.2lf meters.\n", tall);
		printf("%.2lf percent of the region is under water.\n\n", d * 100 / k);
		memset(water, 0, sizeof(water));
	}
}
