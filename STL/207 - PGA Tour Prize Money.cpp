#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=145;
int n,pos;
double sum,pri[maxn];
struct player{
    char name[25];
    double prize;
    bool amateur,t;//是否是业余
    int sc[4],pre,tot,dq,rk;//比赛成绩
} p[maxn];
bool cmp1(const player &a,const player &b){
    if(a.dq>-3&&b.dq>-3) return a.pre<b.pre;   //打了2场以上，前半场分越少越排名靠前
    return a.dq>b.dq;      //中途DQ，场数越多越靠前
}
bool cmp2(const player &a,const player &b){
    if(a.dq!=b.dq) return a.dq>b.dq;//场数多优先
    if(a.tot!=b.tot) return a.tot<b.tot;
    return strcmp(a.name,b.name)<0;
}
void init(){
    memset(p,0,sizeof(p));
    scanf("%lf",&sum);
    for(int i=0;i<70;++i){
        scanf("%lf",&pri[i]);
        pri[i]=pri[i]/100.0*sum;//每一名的奖金
    }
    scanf("%d\n",&n);
    char s[40];
    for(int i=0;i<n;++i){
        fgets(p[i].name,20,stdin);
        if(strchr(p[i].name,'*')) p[i].amateur=true;//查找字符串s中首次出现字符c的位置
        for(int j=0;j<4;++j){
            if(!scanf("%d",&p[i].sc[j])){p[i].dq=j-4;break;}//表示打了几场，0为满场
            if(j<2) p[i].pre+=p[i].sc[j];//前两轮的总成绩
            p[i].tot+=p[i].sc[j];//总分
        }
        fgets(s,40,stdin);//吃掉这一行
    }
    return;
}
void solve(){
    sort(p,p+n,cmp1);
    pos=0;
    while(pos<min(n,70)&&p[pos].dq>-3) ++pos;//打了3场以上并且前70名
    while(p[pos].dq>-3&&p[pos].pre==p[pos-1].pre) ++pos;//把并列的考虑进来
    sort(p,p+pos,cmp2);
    int k=0,rk=0,prk=0;
    while(k<pos){
        if(p[k].dq) break;   //不是满场，无法领奖
        int sta=k,prerk=rk+1,cnt=0;     //sta记录并列人数，prerk记录这些人的rank
        bool x=false;
        double sum=0;
        while(!p[sta].dq&&p[k].tot==p[sta].tot){//满场并且与k并列
            if(!p[sta].amateur) sum+=pri[prk+cnt++],x=true;//如果不是业余的话
            ++rk,++sta;  //查看下一个人是否并列。
        }
        sum/=cnt;//均分奖金
        for(int i=k;i<=sta;++i){//从k到sta都是并列人数
            p[i].rk=prerk;
            if(prk>69) p[i].amateur=true,p[i].t=false;
            if(!p[i].amateur) p[i].prize=sum,p[i].t=cnt>1;
        }
        k=sta-1,k++;
        prk+=cnt;
    }
}
void print_ans(){
    printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
    printf("-----------------------------------------------------------------------\n");
    for(int i=0;i<pos;++i){
        printf("%-21s",p[i].name);//左对齐共占21位
        if(p[i].dq) printf("          ");
        else{
            char t[5];
            sprintf(t,"%d%c",p[i].rk,p[i].t?'T':' ');//rk表示排名，t表示有无并列
            printf("%-10s",t);//左对齐共占10位
        }
        for(int j=-4;j<p[i].dq;++j) printf("%-5d",p[i].sc[4+j]);
        for(int j=p[i].dq;j<0;++j) printf("     ");//没打的比赛补全空格
        if(p[i].dq) printf("%s","DQ");//如果没打满场 tot栏是DQ
        else if(!p[i].amateur) printf("%-10d",p[i].tot);
        else printf("%d",p[i].tot);
        if(p[i].dq||p[i].amateur){printf("\n");continue;}
        printf("$%9.2lf\n",p[i].prize);
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        init();
        solve();
        print_ans();
        if(t) printf("\n");
    }
    return 0;
}
