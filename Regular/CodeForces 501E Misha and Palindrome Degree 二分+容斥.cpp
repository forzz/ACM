#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
using namespace std;
#define LL long long
const int maxn=100005;
map<int,int> mp,mp1,mp2;
struct sw{
	int l,r;
	sw(int ll=0,int rr=0):l(ll),r(rr){}
}ans[2];
int n;
int num[maxn];
int flag,cou=0,cou2=0,now,key;
unsigned LL res=0;
bool check(int l,int r){//这里的l和r表示以考虑区间为零点的区间
	mp1.clear();
	int len1=r-l+1,len2=n-2*now-len1;//len1表示当前区间长度，len2表示另一半区间长度
	if(len2<len1){//len1区间更大，将l和r替换为len2代表的区间
		if(l==now+1){//len1为左区间
			r=n-l+1;  //
			l=r-len2+1;
		}
		else {//len1为右区间
			l=n-r+1;
			r=l+len2-1;
		}
	}
	for(;l<=r;l++)   //统计该区间各个数字出现次数
		mp1[num[l]]++;
	for(auto it=mp1.begin();it!=mp1.end();it++){
		if(it->second>mp[it->first]/2) //该区间有数字出现次数大于该数字出现总次数的一半即为不满足
			return 0;
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i]);
		mp[num[i]]++;        //mp保存该数字在数组中出现的次数
	}
	flag=n%2; //标记数组的奇偶性
	for(auto it=mp.begin();it!=mp.end();it++){
		if(it->second%2) cou++,key=it->first; //如果该数字出现奇数次，key为数字
                if(cou>flag) {//若n为奇数个，则只能有一个数字个数是奇数个，n为偶数则不能有数字个数是奇数个的。否则肯定构不成回文，答案为0
		printf("0\n");
		return 0;
                }
	}
	for(int s=1,e=n;s<e;s++,e--){//从两头往中间判断
		if(num[s]!=num[e]){//当找到两个数字不同的时候，就需要两头各找出一个最小重排区间，再找到包含这个区间的所有方案数。
			now=s-1;
			int l=1,r=e-s;
			for(int i=(n+1)/2,j=(n+2)/2;1;i--,j++)//从中间向外扩张
				if(num[i]!=num[j]||(flag&&i==(n+1)/2&&num[i]!=key)){//两头出现不同或者数组中间不是出现奇数次的数字（数组为奇数）
					key=i-s;//最小区间到起点间隔的数字个数
					l=key;
					break;
                        }
                        //二分查找最小重排区间
                        //若中间有部分数字相同的话，下界就是中间开始不同的地方，上界就是最外围某一边的不同的数字位置
                        //若中间无相同数字的话，下界一定是中点，上界同上
			while(l<=r){ //上界在左边
				int mid=(l+r)>>1;
				if(check(s,s+mid))
					r=mid-1;
				else l=mid+1;
			}
			ans[cou2++]=sw(s,s+l);
			l=key,r=e-s;
			while(l<=r){//上界在右边
				int mid=(l+r)>>1;
				if(check(e-mid,e))
					r=mid-1;
				else l=mid+1;
			}
			ans[cou2++]=sw(e-l,e);
			break;
		}
		else mp[num[s]]-=2;//相同的把数字个数-2，这些数字不是必须要重排的
	}
	if(cou2==0){//若本身就是回文，则答案就是1+2+……+n-1+n，即（1+n）*n/2
		res=1LL*(n+1)*n/2;
		cout<<res<<endl;
		return 0;
	}
		int l1,l2,r1,r2;
		l1=ans[0].l,l2=ans[1].l;
		r1=ans[0].r,r2=ans[1].r;
		res+=l1*(n-r1+1)+(n-r2+1)*l2;//左右两个区间方案数的总和
		res-=l1*(n-r2+1);//容斥定理减去两者共同的方案数
		cout<<res<<endl;
	return 0;
}
