#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <deque>
#include <map>
using namespace std;
struct state {
	int v[70];
	state() { //构造函数
		memset(v, 0, sizeof(v));
	}
	bool operator <(const state &x) const {  //有<才能保存在map中
		return memcmp(v, x.v, sizeof(state)) < 0;
	}
};
deque<int> pile[10];
queue<int> hand;
map<state, int> record;
void reduce(deque<int> &pile) {
	while (pile.size() >= 3) {
		int n = pile.size();
		if ((pile[0]+pile[1]+pile[n-1]) % 10 == 0) {
			hand.push(pile[0]);
			hand.push(pile[1]);
			hand.push(pile[n-1]);
			pile.pop_front();
			pile.pop_front();
			pile.pop_back();
		} else if ((pile[0]+pile[n-2]+pile[n-1]) % 10 == 0) {
			hand.push(pile[0]);
			hand.push(pile[n-2]);
			hand.push(pile[n-1]);
			pile.pop_front();
			pile.pop_back();
			pile.pop_back();
		} else if ((pile[n-3]+pile[n-2]+pile[n-1]) % 10 == 0) {
			hand.push(pile[n-3]);
			hand.push(pile[n-2]);
			hand.push(pile[n-1]);
			pile.pop_back();
			pile.pop_back();
			pile.pop_back();
		}
		else {
			return;
		}
	}
}
int main() {
	int x;
	while (1) {
		while (!hand.empty()) //队列清空只有这一种方法
			hand.pop();
		for (int i = 0; i < 7; i++)
			pile[i].clear();

		for (int i = 0; i < 52; i++) {//读取数据
			scanf("%d", &x);
			if (x == 0) return 0;
			hand.push(x);
		}
		for (int i = 0; i < 7; i++)//先拿出7张牌
			pile[i].push_back(hand.front()), hand.pop();
		for (int i = 0; i < 7; i++)
			pile[i].push_back(hand.front()), hand.pop();
			int flag = 0, step = 14;
			while (!flag) {
				for (int i = 0; i < 7; i++) {
					if (pile[i].size() == 0)
						continue;
					step++;  //步骤增加
					pile[i].push_back(hand.front());
					hand.pop();
					reduce(pile[i]);
					if (hand.size() == 52) {//所有牌堆被清除
						printf("Win : %d\n", step);
						flag = 1;
						break;
					}
					if (hand.size() == 0) {//没有手牌
						printf("Loss: %d\n", step++);
						flag = 1;
						break;
					}

					state s;
					int m = 0;
					for (int j = 0; j < 7; j++) {//s.v保存牌堆
						for (int k = 0; k < pile[j].size(); k++)
							s.v[m++] = pile[j][k];
						s.v[m++] = 15; //每个牌堆用15分割
					}
					queue<int> q = hand;
					while (!q.empty()) {   //s.v保存手牌
						s.v[m++] = q.front();
						q.pop();
					}
					s.v[m++] = 15;
					if (record.find(s) != record.end()) {//存在与之前一样的情况
						printf("Draw: %d\n", step);
						flag = 1;
						break;
					}
					record[s]++;
				}
			}
	}
	return 0;
}
