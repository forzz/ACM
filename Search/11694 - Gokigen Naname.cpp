#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string.h>
using namespace std;
char ans[10][10];
char mat[10][10];
char input[10][10];
bool vis[10][10];
int tR, tC,N;
bool isin(int r,int c){
    return r>=0&&r<=N&&c>=0&&c<=N;
}
bool dfs(int r, int c) {
  if (vis[r][c]) return false;
  if (r==tR && c==tC) return true;
  vis[r][c]=true;
  if (isin(r+1,c+1)&& ans[r][c]=='\\') if (dfs(r+1,c+1)) return true;
  if (isin(r-1,c-1)&& ans[r-1][c-1]=='\\') if (dfs(r-1,c-1)) return true;
  if (isin(r-1,c+1)&& ans[r-1][c]=='/') if (dfs(r-1,c+1)) return true;
  if (isin(r+1,c-1)&& ans[r][c-1]=='/') if (dfs(r+1,c-1)) return true;
  return false;
}
bool have(int r, int c, int tr, int tc) {
    int i,j;
  for (i=0;i<=N;i++)
    for (j=0;j<=N;j++) vis[i][j] = false;
  tR=tr;
  tC=tc;
  return dfs(r,c);
}
bool canput(int r, int c, char s) {
  if (s=='/' &&have(r,c+1,r+1,c)) return false;
  if (s=='\\' &&have(r,c,r+1,c+1)) return false;
  return true;
}
bool legal(int r,int c){
    if (input[r][c]!='.'&&mat[r][c]!=0) return false;
    if (r==N-1){
        if (input[r+1][c]!='.'&&mat[r+1][c]!=0) return false;
        if (c==N-1){

            if (input[r+1][c+1]!='.'&&mat[r+1][c+1]!=0) return false;
        }
    }
    if (c==N-1) {
        if (input[r][c+1]!='.'&&mat[r][c+1]!=0) return false;
    }
    if (mat[r][c+1]<0||mat[r+1][c]<0||mat[r+1][c+1]<0) return false;
    return true;
}
bool dfs(int now){
    if (now==N*N){
        return true;
    }
    int r = now/N,c = now%N;
    ans[r][c] = '.';
    if (canput(r,c,'/')){
        ans[r][c] = '/';
        mat[r][c+1]--;
        mat[r+1][c]--;
        if (legal(r,c)&&dfs(now+1))
            return true;
        mat[r][c+1]++;
        mat[r+1][c]++;
        ans[r][c] = '.';
    }
    if (canput(r,c,'\\')){
        ans[r][c] = '\\';
        mat[r][c]--;
        mat[r+1][c+1]--;
        if (legal(r,c)&&dfs(now+1))
            return true;
        mat[r][c]++;
        mat[r+1][c+1]++;
        ans[r][c]='.';
    }
    return false;
}
int main(){
    int tt;
    int i,j,st,next;
    scanf("%d",&tt);
    for (int tcas = 1;tcas<=tt;tcas++){
        scanf("%d",&N);
        for (i=0;i<=N;i++)
            scanf("%s",&input[i]);
        for (i=0;i<=N;i++)
            for (j=0;j<=N;j++)
            if (input[i][j]=='.') mat[i][j] = 4;
            else mat[i][j]=input[i][j]-'0';
        memset(ans,0,sizeof(ans));
        dfs(0);
        for (i=0;i<N;i++)
        {
            for (j=0;j<N;j++) printf("%c",ans[i][j]);
            printf("\n");
        }
    }
}
