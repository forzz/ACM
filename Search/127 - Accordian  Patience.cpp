#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
//CARD结构体，存储一张牌，Face[0]表示花色，Face[1]表示点数
struct CARD {char Face[2];} Src;
//比较两张牌是否匹配。花色或点数相同即匹配
typedef vector<CARD> PILE;
bool Match(const CARD &c1, const CARD &c2) {
    return (c1.Face[0] == c2.Face[0] || c1.Face[1] == c2.Face[1]);
}
int main(void) {
    char Pack[256]; //用于存储输入的一副牌，下面循环读取输入的数据
    for (string Line; getline(cin, Line) && Line[0] != '#'; cout << endl) {
        strcpy(Pack, Line.c_str()); //读取并处理输入的数据
        while (getline(cin, Line) && Line.empty()); //读取第二行
        strcat(Pack, Line.c_str()); //后者拼接到前者
        *remove(&Pack[0], &Pack[strlen(Pack)], ' ') = '\0'; //删除行中的空格
        vector<PILE> Piles;   //两个vector嵌套
        for (int i = 0; i < 52; ++i) { //循环发出每一张牌，保证这张牌之前的所有牌无法再移动
            PILE pl(1, ((CARD*)&Pack)[i]); //对Pack地址进行强制转换，然后pl初始化为1个CARD[i]
            Piles.push_back(pl); //将新发的牌放在最后一叠
            //j表示当前牌的位置，k表示j左边与之匹配的牌的位置
            for (size_t j = Piles.size() - 1, k; j < Piles.size(); ++j) {
        //size_t 类型表示C 中任何对象所能达到的最大长度。它是无符号整数，用于sizeof和strlen
                for (k = j, Src = Piles[j].back(); k > 0; --k) {//向左查找可以移到的最左边的位置
                    if (k >= 3) { //先判定左边是否存在第3张
                        if (Match(Src, Piles[k - 3].back())) {
                            //如果与左边第3张匹配，则将k指向这张牌
                            k -= 2;
                            continue;
                        } //虚拟移到k指向的位置，继续向左查找
                    }
                    if (!Match(Src, Piles[k - 1].back())) {
                        break; //如果左边第3张和第1张都失配，跳出循环
                    }
                }
                if (k != j) { //k与原位置j不相等表示可以移动
                    Piles[k].push_back(Piles[j].back()); //移动牌
                    Piles[j].pop_back();
                    if (Piles[j].empty()) { //如果牌叠被移空则删除之
                        Piles.erase(Piles.begin() + j);
                    }
                    j = k; //将移动牌查找的起点定为k
                }
            }
        } //以下按要求的格式输出结果。注意到Pile有单复数的区分
        int nSize = Piles.size();
        cout << nSize << " pile" << (nSize > 1 ? "s " : " ") << "remaining:";
        for (int i = 0; i < nSize; cout << ' ' << Piles[i++].size());
    }
    return 0;
}
