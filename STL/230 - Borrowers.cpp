#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;
struct book{
    string author;
    int status;  //是否借出
};
map<string, book> books;//每一个书名对应一本书
vector<string> name;//将名字存到vector中
bool compare(string a, string b){           //先按作者排，再按书名排
    if(books[a].author == books[b].author) return a < b;
    else return books[a].author < books[b].author;
}
int main()
{
    string x,z,m;
    book y;
    while(getline(cin,m)){
        if(m == "END") break;
        x = m.substr(0, m.find_last_of("\"")+1);
        y.author = m.substr(m.find_last_of("\"")+1);
        name.push_back(x);
        books[x]= y;
    }
    sort(name.begin(), name.end(), compare);
    for(int i = 0; i < name.size(); i++)//默认未借出
        books[name[i]].status = 1;
    while(cin >> x){
        if(x == "END") break;
        if(x == "BORROW"){
            getchar();  //读入空格
            getline(cin, z);
            books[z].status = 0; //借出标志
        }
        if(x == "RETURN"){
            getchar();
            getline(cin, z);
            books[z].status = -1;//归还标志
        }
        if(x == "SHELVE"){
            for(int i = 0; i < name.size(); i++)
                if(books[name[i]].status == -1){//i是归还书籍
                    int j;
                    for(j = i; j >= 0; --j)   //从i开始找未借出过的书
                        if(books[name[j]].status == 1) break;
                    if(j > -1) cout << "Put " << name[i] << " after " << name[j] << endl;//j>-1代表存在一个j
                    else cout << "Put " << name[i] << " first" << endl;
                    books[name[i]].status = 1;  //把这本书的状态重置
                }
                cout << "END" << endl;

        }
    }
    return 0;
}
