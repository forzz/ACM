#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <cstdio>
#include <cctype>

using namespace std;

int r, c, size;

vector<pair<int, int> > pt[256];
int ss[256];
string ss_s[256];

bool ok_all;
set<int> put_false;

bool ok[256];
bool vis[256];
int dfs(const int &pos) {
    if(!ok[pos]) {
        ok_all = false;
        return 0;
    }
    if(pt[pos].empty()) return ss[pos];
    if(vis[pos]) {
        ok[pos] = false;
        ok_all = false;
        put_false.insert(pos);
        return 0;
    }

    vis[pos] = true;
    for(auto it = pt[pos].begin(); it != pt[pos].end(); ++it) {
        if(ok[it->first]) ss[pos] += (it->second) * dfs(it->first);
        if(!ok[it->first]) {
            ok[pos] = false;
            ok_all = false;
            put_false.insert(pos);
        }
    }
    pt[pos].clear();
    return ss[pos];
}

int main() {
    ios::sync_with_stdio(false);
    while(cin >> r >> c && r && c) {
        size = r * c;
        for(int i = 0; i != size; ++i) {
            pt[i].clear();
            ss[i] = 0;

            string ele; cin >> ele;
            ss_s[i] = ele;

            vector<int> sign;

            if(ele[0] == '-') sign.push_back(-1);
            else sign.push_back(1);
            for(auto it = ele.begin(); it != ele.end(); ++it) {
                if(*it == '-') sign.push_back(-1), *it = ' ';
                else if(*it == '+') sign.push_back(1), *it = ' ';
            }

            istringstream line(ele); auto it = sign.begin();
            while(line >> ele) {
                if(isdigit(ele[0])) {
                    istringstream t(ele);
                    int d; t >> d; ss[i] += d * (*it++);
                } else {
                    int pos = (ele[0] - 'A') * c + ele[1] - '0';
                    pt[i].push_back(pair<int, int>(pos, *it++));
                }
            }
        }

        ok_all = true;
        put_false.clear();
        for(int i = 0; i != size; ++i) ok[i] = true, vis[i] = false;

        for(int i = 0; i != size; ++i) dfs(i);

        if(!ok_all) {
            for(auto it = put_false.begin(); it != put_false.end(); ++it) cout << (char)(*it / c + 'A') << *it % c << ": " << ss_s[*it] << endl;
        } else {
            cout << ' '; for(int i = 0; i != c; ++i) cout << setw(6) << i; cout << endl;
            for(int i = 0; i != r; ++i) {
                cout << (char)(i + 'A');
                for(int j = 0; j != c; ++j) cout << setw(6) << ss[i * c + j]; cout << endl;
            }
        }

        cout << endl;
    }
}
