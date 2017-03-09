#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cstdio>
using namespace std;
struct topic
{
    int tid,num,t0,t,dt,num1;  //num1代表初始请求个数
    int is_exe, time, time_between, first;
};
struct member
{
    int pid,k,last,busy,time,leixing,time1;
    vector<int>pidk;
    bool operator < (const member&a) const
     {
         if(a.last == last) return a.pid > pid;    //处理时间相同，id小的优先
         else return a.last > last;           //上次处理请求的时间早的优先
     }
};
vector<topic>topics;   //主题
vector<member>staff;   //客服
map<int,int>ha;  //将任务主题的顺序与tid对应
map<int,vector<member> >num; //做每个工作的人，int是tid，后面的vector是做这个工作的客服
map<int,int>ren;   //将客服的顺序与pid对应
int can_exe(int x, int t)
{
    if(t < topics[x].t0) return 0;//如果该时间还没到第一个请求的时间，返回0
    if(topics[x].dt == 0) return topics[x].num > 0;  //相邻间隔为0，到了第一个请求的时间，只要请求不为0，无限执行
    if(topics[x].num == 0)return 0;//到了第一个请求的时间，间隔不为0，但请求个数为0
    if((t+topics[x].dt-topics[x].t0)/topics[x].dt == (topics[x].num1-topics[x].num)) return 0;
    //（当前时间+时间间隔-初次请求时间）/间隔时间==已执行请求数
    //（执行任务总时间+时间间隔）/时间间隔   这个除法保留整数，可以直接排除掉任务执行过程中的情况
    return 1;
}
int main()
{
    int m, n, kase = 0, i, j, k;  //m是主题数，n是客服数
    while(cin >> m && m){
        int time = 0;
        topics.clear();
        staff.clear();
        ha.clear();
        ren.clear();
        for(i = 0; i < m; i++){
            topic a;
            cin>>a.tid>>a.num>>a.t0>>a.t>>a.dt;
            a.num1 = a.num;
            topics.push_back(a);
            ha[a.tid] = i;
        }
        cin >> n;
        for(i = 0; i < n; i++){
            member a;
            a.pidk.clear();
            a.time1 = a.last = a.busy = a.time = 0;
            int x;
            cin >> a.pid >> a.k;
            ren[a.pid] = i;
            for(j = 0; j < a.k; j++){
                cin >> x;
                a.pidk.push_back(x);
            }
            staff.push_back(a);
        }
        for(time = 0; time < 500000; time++){//时间不断改变
            num.clear();//每个任务有多少空闲客服可以做
            for(i = 0; i < n; i++)   //先以每个客服为主体循环，找到每个空闲客服所能做的全部任务
                if(!staff[i].busy)
                  for(j = 0; j < staff[i].k; j++)  //找到此人能够执行的工作（按照优先级）
                     if(can_exe(ha[staff[i].pidk[j]],time)){//这个工作可以执行
                        if(!num.count(staff[i].pidk[j])) num[staff[i].pidk[j]] = vector<member>();
                        //如果该工作没人接手，那么建立一个空的vector（如果是基本类型可以直接赋值）
                        num[staff[i].pidk[j]].push_back(staff[i]);//已经有vector，push
                        break;
                     }
           map<int,vector<member> >::iterator it;
           for(it = num.begin(); it != num.end(); ++it){  //再以每个可执行任务为主题循环，找到合适的客服
              sort(it->second.begin(),it->second.end());  //每个客服sort
              int temp = ren[it->second[0].pid];//temp为目标客服的顺序
              staff[temp].busy = 1;
              staff[temp].last = time;
              staff[temp].leixing = it->first;
              topics[ha[it->first]].num--;
           }
           int all_zero = 1;
           for(i = 0; i < n; i++){
              if(staff[i].busy) staff[i].time++;
              if(staff[i].busy && staff[i].time == topics[ha[staff[i].leixing]].t) //时间到了就还原
                {staff[i].time = 0;staff[i].busy = 0;}
           }
           for(i = 0; i < m; i++) if(topics[i].num > 0) {all_zero = 0;break;}
           for(i = 0; i < n; i++) if(staff[i].time > 0) {all_zero = 0;break;}
           if(all_zero) break;
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n",++kase, time+1);
    }
    return 0;
}
