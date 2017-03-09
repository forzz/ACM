#include <iostream>
#include <functional>//hash头文件
#include <string>
#include <cstdio>
using namespace std;
const int maxn=1000003;    //p选较大素数
int head[maxn],nextt[maxn];    //接下来必须都是maxn，这些模拟指针
string str[maxn];
int cnt;
hash <string> str_hash;
void initial(){
  cnt=0;
  for(int i=0;i<maxn;i++) head[i]=-1;
}

void add(string st){  //读入一个string
  int c=str_hash(st)%maxn;      //str_hash可以将st转化为hash值
  str[cnt]=st;        //保存到str中 cnt从0开始，增加1个st就增加cnt
  nextt[cnt]=head[c];//head代表c下标对应链表的头结点，初始为空-1，nextt表示cnt代表的st在链表中的下一个结点
  head[c]=cnt++; //c下标增加st存到str中的cnt，cnt++继续读入下一个string
}

bool canfind(string st){
  int c=str_hash(st)%maxn;     //str_hash可以将st转化为hash值
  for(int i=head[c];i!=-1;i=nextt[i]){
    if(str[i]==st) return true;
  }
  return false;
}

int main(){
  initial();    //初始化
  string st;
  while(cin>>st) add(st);
  for(int i=0;i<cnt;i++){
      for(int k=1;k<str[i].length();k++){//把str的每一个字符作为一个分割点进行遍历，寻找是否有符合。无法优化
        string sub1=str[i].substr(0,k); //返回从0开始，k个字符的字符串
        string sub2=str[i].substr(k,str[i].length()-k);
        if(canfind(sub1)  &&  canfind(sub2)){
          printf("%s\n",str[i].c_str());
          break;
        }
      }
  }
  return 0;
}
