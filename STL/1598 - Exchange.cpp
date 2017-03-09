#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include<iostream>
using namespace std;
struct CMD {
	string cmd;
	int size, price;
	CMD(string kind, int x = 0, int y = 0) :cmd(kind), size(x), price(y) {}
	//构造函数格式：   结构体名（形参和其初始值）：形参代表的每个变量｛｝
};
map<int, set<int> > BUY, SELL;     //可以构成双重排队，先按价格排，每个价格的指令按顺序排
map<int, int> BUY_VAL, SELL_VAL;   //因为这道题会取消指令，所以需要构建一个总的size，还有每个指令的size
vector<CMD> D;
void trade(int kind)
{
	while (!BUY.empty() && !SELL.empty()) {
		if (BUY.rbegin()->first >= SELL.begin()->first) {//最高买价和最低卖价
			set<int> &v1 = BUY.rbegin()->second;//该价格对应的指令集
			set<int> &v2 = SELL.begin()->second;
			int aid = *v1.begin(), bid = *v2.begin(); //两个指令的代号
			int z = min(D[aid].size, D[bid].size);//交易量
			printf("TRADE %d %d\n", z, kind ? D[aid].price : D[bid].price);//kind为0是买，为1是卖
			D[aid].size -= z, D[bid].size -= z;//货减少
			BUY_VAL[D[aid].price] -= z, SELL_VAL[D[bid].price] -= z;
			if (D[aid].size == 0)    //维护各个数据
				v1.erase(aid);
			if (D[bid].size == 0)
				v2.erase(bid);
			if (v1.size() == 0)
				BUY.erase(D[aid].price);
			if (v2.size() == 0)
				SELL.erase(D[bid].price);
		}
		else {
			return;
		}
	}
}
void print()
{
	while (BUY_VAL.size() && BUY_VAL.rbegin()->second == 0) {//最后维护_VAL数组
		BUY_VAL.erase(BUY_VAL.rbegin()->first);
	}
	while (SELL_VAL.size() && SELL_VAL.begin()->second == 0) {
		SELL_VAL.erase(SELL_VAL.begin()->first);
	}
	printf("QUOTE ");  //输出报价（当前最高买家与最低卖价）
	if (BUY_VAL.size()) {  //还有需求量
		printf("%d %d", BUY_VAL.rbegin()->second, BUY_VAL.rbegin()->first);//最高买量和买价
	}
	else { //否则输出0
		printf("0 0");
	}
	printf(" - ");
	if (SELL_VAL.size()) {//还有销售量
		printf("%d %d", SELL_VAL.begin()->second, SELL_VAL.begin()->first);
	}
	else {
		printf("0 99999");
	}
	cout << endl;
}

int main()
{
	int Q, cases = 0;
	char cmd[16];
	while (scanf("%d", &Q) == 1) {
		if (cases++)
		{
			cout << endl;
		}
		// 记得清空
		BUY.clear(), SELL.clear();
		BUY_VAL.clear(), SELL_VAL.clear();
		D.clear();
		int size, price, id;
		// 读入命令并处理交易
		for (int i = 0; i < Q; i++) {
			scanf("%s", cmd);
			if (!strcmp(cmd, "BUY")) {
				scanf("%d %d", &size, &price);
				BUY[price].insert(i);  //map会自动将price排列，然后set存入指令代号
				BUY_VAL[price] += size;  //把size存好，这个保存的是该价格的所有size
				D.push_back(CMD("BUY", size, price));//把数据存到D中
				trade(0);
			}
			else if (!strcmp(cmd, "SELL")) {
				scanf("%d %d", &size, &price);
				SELL[price].insert(i);
				SELL_VAL[price] += size;
				D.push_back(CMD("SELL", size, price));
				trade(1);
			}
			else if (!strcmp(cmd, "CANCEL")) {
				scanf("%d", &id), id--;  //实际id从0开始
				D.push_back(CMD("CANCEL", id));  //指令存入
				if (D[id].cmd == "BUY") {
					BUY[D[id].price].erase(id);    //清除掉该id
					if (BUY[D[id].price].size() == 0) //如果该价格没有货
						BUY.erase(D[id].price);    //清除该价格
					BUY_VAL[D[id].price] -= D[id].size;  //减少总量
					D[id].size = 0;
				}
				if (D[id].cmd == "SELL") {
					SELL[D[id].price].erase(id);
					if (SELL[D[id].price].size() == 0)
						SELL.erase(D[id].price);
					SELL_VAL[D[id].price] -= D[id].size;
					D[id].size = 0;
				}
			}
			print();
		}
	}
	return 0;
}
