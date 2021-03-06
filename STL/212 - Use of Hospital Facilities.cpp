#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define a(i) patients[i]
int MAX = 0;
struct ROOM_BED
{
    int minutes;
    double used;
    ROOM_BED(int x = 0,double y = 0):minutes(x),used(y){}
}Room[50],Bed[50];
struct PATIENT
{
    string name;
    int room, bed, id;
    int o_begin,o_end,r_begin,r_end,time_o,time_r;

};
struct ROOM
{
    int id,start,end;
    ROOM(int a = 0, int b = 0):start(a),end(b){}
};
struct cmp1   //对手术室排序,按结束时间排序，结束时间相同按编号排序
{
    bool operator () (const ROOM a, const ROOM b) const  //返回真值代表a比b的优先级小
    {
        if(a.end != b.end) return a.end > b.end;
        return a.id > b.id;
    }
};
bool cmp2(const PATIENT a, const PATIENT b) //对病人排序（按照进入恢复室的顺序）
{

        if(a.o_end != b.o_end) return a.o_end < b.o_end;   //返回真值代表a<b
        return a.room < b.room;

};
bool cmp3(const PATIENT a, const PATIENT b)  //按花名册排序
{
    return a.id < b.id;             //返回真值代表a<b
}
vector<PATIENT>patients;
priority_queue<ROOM,vector<ROOM>,cmp1> operating; //用队列对各手术室排序
vector<ROOM>bed;
int main()
{
    int n,m,T,t1,t2,t3,i,j,k;
    while(cin >> n >> m >> T >> t1 >> t2 >> t3 >> k){
      MAX = 0;
      patients.clear();bed.clear();
      while (!operating.empty())operating.pop();
      for(i = 0; i < 50; i++){Room[i].minutes = 0,Bed[i].minutes = 0;}//清空所有数据
      for(i = 0; i < k; i++){//k个患者赋值
         PATIENT p;
         cin >> p.name;
         cin >> p.time_o >> p.time_r;
         p.id = i;
         patients.push_back(p);
     }
     //模拟手术过程，先考虑所有人做手术
      for(i = 0; i < n; i++){//n个手术室初始化并进入队列
         ROOM a;
         a.id = i+1,a.start = a.end = 0;
         operating.push(a);
      }
      for(i = 0; i < k; i++){ //遍历所有患者
         ROOM x = operating.top();  //x为编号最小的ROOM
         operating.pop();
         if(x.end == 0) x.start = T*60;  //手术室未使用过
         else x.start = x.end + t2;      //手术室使用过
         x.end = patients[i].time_o + x.start;  //维护ROOM patients数据
         Room[x.id].minutes += patients[i].time_o;
         patients[i].o_begin = x.start, patients[i].o_end = x.end, patients[i].room = x.id;
         operating.push(x);  //把x再次压入栈
      }
      //模拟恢复过程，考虑所有人进恢复室
      sort(patients.begin(),patients.end(),cmp2);
      for(i = 0; i < m; i++){            //m个恢复室初始化并进入队列
         ROOM a;
         a.id = i+1,a.start = a.end = 0;
         bed.push_back(a);
      }
      for(i = 0; i < k; i++){   //遍历所有患者
         int end1 = patients[i].o_end;
         for(j = 0; j < m; j++)   //遍历每个休息室（优先找编号小的休息室）
                 if(patients[i].o_end >= (bed[j].end == 0 ? bed[j].end : bed[j].end+t3)){//如果休息室空闲
                    patients[i].bed = j+1;
                    bed[j].start = patients[i].o_end + t1;
                    bed[j].end = bed[j].start + patients[i].time_r;
                    patients[i].r_begin = bed[j].start;
                    patients[i].r_end = bed[j].end;
                    Bed[j+1].minutes += patients[i].time_r;
                    break;
                  }
    }
     for(i = 0; i < k; i++) MAX = max(MAX,patients[i].r_end-T*60);//找到最大时间
     sort(patients.begin(),patients.end(),cmp3);   //按花名册排序
     //输出
     puts(" Patient          Operating Room          Recovery Room");
     puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
     puts(" ------------------------------------------------------");
     for(i = 0; i < k; i++)// %02d  2是宽度。如果整数不够2列就补上0
         printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n", i+1,a(i).name.c_str(),a(i).room,a(i).o_begin/60,a(i).o_begin%60,a(i).o_end/60,a(i).o_end%60,a(i).bed,a(i).r_begin/60,a(i).r_begin%60,a(i).r_end/60,a(i).r_end%60);
     printf("\n");
     for(i = 0; i < m; i++){
        if(MAX == 0) Bed[i+1].used = 0.00;
        else Bed[i+1].used = (double)Bed[i+1].minutes*100 / MAX;
     }
     for(i = 0; i < n; i++){
        if(MAX == 0) Room[i+1].used = 0.00;
        else Room[i+1].used = (double)Room[i+1].minutes*100 / MAX;
     }
     puts("Facility Utilization");
     puts("Type  # Minutes  % Used");
     puts("-------------------------");
     for(i = 0; i < n; i++) printf("Room %2d %7d %7.2lf\n", i + 1, Room[i+1].minutes, Room[i+1].used);
     for(i = 0; i < m; i++) printf("Bed  %2d %7d %7.2lf\n", i + 1, Bed[i+1].minutes, Bed[i+1].used);
     cout << endl;
  }
 return 0;
}
