#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdio>
#include<cmath>
#define EPS 1e-7
using namespace std;
double X,Y; //某个位置的坐标
struct MAP
{
    string name;
    double x1,x2,y1,y2,area,Ratio,level;
    pair<double,double>center;
    MAP(double _x1, double _y1, double _x2, double _y2, string _name):
         x1(_x1), y1(_y1), x2(_x2), y2(_y2), name(_name){
         if(x1 > x2)swap(x1,x2);
         if(y1 > y2)swap(y1,y2);
         area = (x2-x1)*(y2-y1);
         Ratio = (y2 - y1) / (x2 - x1);
         center.first = (x1+x2)/2.0;
         center.second = (y1+y2)/2.0;
    }
    bool operator <(const MAP &b) const
    {
        if(level != b.level) return level > b.level;
        double d1 = (center.first-X)*(center.first-X) + (center.second-Y)*(center.second-Y);
        double d2 = (b.center.first-X)*(b.center.first-X) + (b.center.second-Y)*(b.center.second-Y);
        if(fabs(d1-d2) > EPS) return d1 < d2;
        d1 = fabs(Ratio-0.75),d2 = fabs(b.Ratio-0.75);
        if(fabs(d1-d2) > EPS) return d1 < d2;
        d1 = (X-x2)*(X-x2)+(Y-y1)*(Y-y1);
        d2 = (X-b.x2)*(X-b.x2)+(Y-b.y1)*(Y-b.y1);
        if(fabs(d1-d2) > EPS) return d1 > d2;
        return x1 < b.x1;
    }
};
vector<MAP>maps;
map<string,pair<double,double> >site; //存储位置及其坐标
vector<int>cover; //包含点（X,Y）的地图下标
vector<double>area; //面积
vector<MAP>yes;   //包含点（X,Y）的地图
int no_contain(string s)  //判断有没有地图包含这个位置（X,Y）
{
    double x = site[s].first, y = site[s].second;
    int sum = 0;
    for(int i = 0; i < maps.size(); i++)
        if(x >= maps[i].x1 && x <= maps[i].x2 && y >= maps[i].y1 && y <= maps[i].y2)
           sum++, cover.push_back(i);
    return sum;
}
int main()
{
    string s;
    cin >> s;
    while(cin >> s && s != "LOCATIONS"){
        double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        maps.push_back(MAP(x1,y1,x2,y2,s));
    }
    while (cin >> s, s != "REQUESTS"){
        double x,y;
        cin >> x >> y;
        site[s] = make_pair(x,y);
    }
    while(cin >> s && s != "END"){
        int level; cin >> level;
        cover.clear();area.clear();yes.clear();
        printf("%s at detail level %d ",s.c_str(),level);
        if(!site.count(s)) {printf("unknown location\n");}
        else if(!no_contain(s)) {printf("no map contains that location\n");}
        else{
            for(int i = 0; i < cover.size(); ++i)
              {yes.push_back(maps[cover[i]]); area.push_back(maps[cover[i]].area);}
            X = site[s].first, Y = site[s].second;
            sort(area.begin(),area.end(),greater<double>());
            unique(area.begin(),area.end()); //面积去重
            int num = area.size(), temp = 0;
            for(int i = 0; i < yes.size(); i++)
                for(int j = 0; j < num; j++)
                  if(yes[i].area == area[j]) {yes[i].level = j+1;break;}
            sort(yes.begin(),yes.end());
            if(num < level) printf("no map at that detail level; ");
            for(int i = 0;i < yes.size();i++)if(level == yes[i].level) {temp = i;break;}
            cout << "using " << yes[temp].name << endl;
        }
    }
}
