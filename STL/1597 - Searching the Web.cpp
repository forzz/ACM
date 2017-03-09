#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include<cstring>
using namespace std;
#define rep(i,b) for(int i=0; i<(b); i++)//遍历一个数组
#define foreach(i,a) for(__typeof((a).begin()) i=a.begin(); i!=(a).end(); ++i)//每一行遍历
#define FOR for (int j = limit[i]; j < limit[i + 1]; j++)//每一篇文章的每一行遍历
typedef bool Bit[1505];//Bit代表bool[1505]

int n, lines, m;          // n文档数, lines行数, m请求数
int limit[105];           // limit[i]: 第i篇文档从第几行开始

string doc[1505];         // 存储内容
map<string, Bit> Index;   // Index[单词]: B标记了哪些行出现过

// 用s来更新Index
void upDate(string s, int p) {
    string word;
    foreach(it, s) {
        if (isalpha(*it)) *it = tolower(*it); // 变小写
        else *it = ' '; // 非字母变空白
    }

    stringstream ss(s);
    while (ss >> word) Index[word][p] = true;
}

int main() {
    //文档数据输入
    scanf("%d ", &n);
    rep(i, n) {
        limit[i] = lines;
        while (getline(cin, doc[lines]), doc[lines] != "**********") {
            upDate(doc[lines], lines);
            lines++;
        }
    }
    limit[n] = lines;
    //{section: 对获取的请求输出对应的内容
    string  s;                      // s存储每次得到的请求
    Bit     mark;                   //{记录哪些行应该输出
                                    //}mark的解释: 因为每篇文档要用10个'-'隔开,比较麻烦,最后统一处理
    bool    *A, *B;      //A和B代表两个数组指针
    scanf("%d ", &m);//m个请求
    for (int iii = 0; iii < m; iii++) {
        getline(cin, s);//读取命令

        //{subsection: 计算出mark中介
        if (s[0] == 'N') {
            A = Index[s.substr(4)];//从第4个字符开始，A代表map对应的数组
            rep(i, n) {     //n个文档遍历
                bool logo = true;//默认出现
                FOR if (A[j]) { logo = false; break; }//该行存在该字符，该文章存在该字符，换下一个文档
                FOR mark[j] = logo;//判断是否输出，不出现该字符，则要输出整篇文章
            }
        } else if (s.find("AND") != string::npos) {
            int p = s.find(" AND ");//为了去掉空格
            A = Index[s.substr(0, p)];
            B = Index[s.substr(p + 5)];
            memset(mark, 0, sizeof(mark));
            bool hasA, hasB;    // 在同一文章中, 两个词是否都出现
            rep(i ,n) {//每一篇文章遍历
                hasA = hasB = false;    // 默认没出现
                FOR if (A[j]) { hasA = true; break; }//找到第一个为止
                FOR if (B[j]) { hasB = true; break; }
                if (!(hasA&&hasB)) continue;//如果有一个字符根本没有，直接换下一个文档，不输出到mark
                FOR mark[j] = (A[j] || B[j]);
            }
        } else if (s.find("OR") != string::npos) {
            int p = s.find(" OR ");  //返回OR前面空格的下标
            A = Index[s.substr(0, p)];//从0开始p个字符
            B = Index[s.substr(p + 4)];
            rep(i, lines) mark[i] = (A[i] || B[i]);
        } else memcpy(mark, Index[s], sizeof(mark));//如果没有and和or还有not 可以直接拷贝过去}

        //输出mark
        bool hasOut = false, needOut = false;    // 记录上一轮是否有输出文档
        rep(i, n) {//rep和FOR组合可以遍历每一行
            if (hasOut) needOut = true;
            hasOut = false;
            FOR if (mark[j]) {//需要输出
                if (needOut) {//上一轮有输出文档
                    cout << "----------\n";
                    needOut = false;
                }
                cout << doc[j] << "\n";
                hasOut = true;
            }
        }
        if (!(needOut||hasOut)) cout << "Sorry, I found nothing.\n";
        cout << "==========\n";//}
    }//}

    return 0;
}
