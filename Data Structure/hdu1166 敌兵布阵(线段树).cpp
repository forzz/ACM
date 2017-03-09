#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int a[50001];//存储结点的位置
struct node{
  int left,right;//线段区间
  int sum;//区间上的人数
}b[150005];
void Build(int left,int right,int i){//建树
  int mid;
  b[i].left=left;
  b[i].right=right;
  if(left==right){//先用数组存下该队的人
    b[i].sum=a[left];
    return ;
  }
  mid=(left+right)/2;
  Build(left,mid,2*i);//递归建立左子树
  Build(mid+1,right,2*i+1);//递归建立右子树
  b[i].sum=b[2*i].sum+b[2*i+1].sum;//记录该结点左右子树的值
}

void Add(int j,int num,int i){
  if(b[i].left==b[i].right){//到达叶子结点
    b[i].sum+=num;
    return ;//注意返回
  }
  else{
    b[i].sum+=num;//他的所有父节点都增加
    if(j<=b[i*2].right) Add(j,num,2*i);//递归左子树
    else Add(j,num,2*i+1);//建立右子树
  }
}

int Query(int left,int right,int i){//查询
  int mid;
  if(b[i].left==left&&b[i].right==right) return b[i].sum;
  mid=(b[i].left+b[i].right)/2;
  if(right<=mid) return Query(left,right,2*i);//在左子树
  else if(left>mid) return Query(left,right,2*i+1);//在右子树
  else return Query(left,mid,2*i)+Query(mid+1,right,2*i+1);//否则在中间
}
int main()
{
  int t,k=0,i,j,num,n;
  char s[10];
  scanf("%d",&t);
  while(t--){
    scanf("%d",&n);
    for(i=1;i<=n;i++){
      scanf("%d",&a[i]);
    }
    printf("Case %d:\n",++k);
    Build(1,n,1);//建树
    while(1){
      scanf("%s",s);
      if(!strcmp(s,"End")) break;
      scanf("%d%d",&j,&num);
      if(!strcmp(s,"Query")){
        printf("%d\n",Query(j,num,1));
      }
      if(!strcmp(s,"Add")) Add(j,num,1);//从根结点开始
      if(!strcmp(s,"Sub")) Add(j,-num,1);

    }
  }
  return 0;
}
/*线段树的简单应用,用scanf和printf输入输出
 *cin和cout会超时
 *树状数组过不去
