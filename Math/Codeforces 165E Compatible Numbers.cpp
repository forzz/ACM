#include <cstdio>
int a[1000010],vis[1<<22];
int main(){
    int n,mask = (1<<22)-1;
    scanf("%d",&n);
    for(int i = 0;i < n;i++){
        scanf("%d",&a[i]);
        vis[mask^a[i]] = a[i];    //mask^a[i]为a[i]的补集
    }
    for(int i = mask;i >= 0;i--){//遍历每种可能
        if(vis[i])  continue;       //i与某个数与为0
        for(int j = 0;j < 22;j++){
            if(vis[i|(1<<j)]){//找到将i的某位0补成1的数，如果该数符合结果，那么这个数的1变为0的结果（也就是当前i）肯定符合
                vis[i] = vis[i|(1<<j)];//记录该数得到的结果
                break;
            }
        }
    }
    for(int i = 0;i < n;i++){
        if(vis[a[i]])   printf("%d ",vis[a[i]]);
        else    printf("-1 ");
    }
}
