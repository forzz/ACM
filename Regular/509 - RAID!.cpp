#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=6500;
int d,s,b,n;
char data[7][maxn];
bool parity;
bool read(){
	scanf("%d%d%d\n",&d,&s,&b);//d为行
	if(!d) return false;
	memset(data,0,sizeof(data));
	parity=getchar()=='O',n=s*b;//n是列
	for(int i=0;i<d;++i)
		scanf("%s",data[i]);//读入每一行
	return true;
}
bool solve(){
	for(int i;i<n;++i){
		bool k=false;
		int broke=-1;
		for(int j=0;j<d;++j){
			char& c=data[j][i];  //c为代指
			if(c=='1') k=!k;  //k=1为奇数  k=0为偶数
			if(c=='x'){
				if(broke!=-1) return false;//只能检查1个x
				else broke=j;
			}
		}
		if(broke==-1&&k!=parity) return false;//校验不合法。
		if(broke!=-1) data[broke][i]=k==parity?'0':'1';//修复。
	}
	return true;
}
void print_ans(bool v){
	if(!v) {printf("invalid.\n");return;}
	printf("valid, contents are: ");
	int num=0,cnt=0;
	for(int i=0;i<b;++i){    //b每行的数据块数
		int pos=i*s;     //  数据位置
		for(int j=0;j<d;++j){//d是行数
			if(i%d==j) continue;//校验块跳过。
			for(int k=0;k<s;++k){//k是每个数据块的字符数
				num<<=1,num+=(data[j][pos+k]=='1'),++cnt;//每4位代表1个数
				if((cnt%=4)==0) printf("%X",num),num=0;
			}
		}
	}
	if(cnt) printf("%X",num<<(4-cnt));//补0。
	printf("\n");
	return;
}
int main(){
	int t=0;
	while(read()){
		printf("Disk set %d is ",++t);
		print_ans(solve());
	}
	return 0;
}