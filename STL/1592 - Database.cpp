#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<map>
#include<sstream>
using namespace std;

typedef pair<int,int> PII;

const int maxr = 10000 + 5;
const int maxc = 10 + 5;

int m, n, db[maxr][maxc], cnt;

map<string, int> id;//Ϊÿ���ַ������
int ID(const string& s) {   //��ÿ���ַ������
	if(!id.count(s)) {//���֮ǰδ����
		id[s] = ++cnt;//�Զ���ʼ��һ��map�����Ҹ�ֵ
	}
	return id[s];
}

void find() {
	for(int c1 = 0; c1 < m; c1++)//���б���
		for(int c2 = c1+1; c2 < m; c2++) {//��һ��
			map<PII, int> d;
			for(int i = 0; i < n; i++) {//���б�����ÿһ�й���һ��pair
				PII p = make_pair(db[i][c1], db[i][c2]); //����һ���ѳ�ʼ����pair����p
				if(d.count(p)) {//���عؼ���Ϊp��Ԫ���������������ͨmap����0��1
					printf("NO\n");
					printf("%d %d\n", d[p]+1, i+1);
					printf("%d %d\n", c1+1, c2+1);
					return;
				}
				d[p] = i;
			}
		}
		printf("YES\n");
}


int main() {
	string s;
	while(getline(cin, s)) {       //ͳһ����ÿһ�У�Ȼ��浽ss���зֿ���ȡ
		stringstream ss(s);
		if(!(ss >> n >> m)) break;
		cnt = 0;
		id.clear();
		for(int i = 0; i < n; i++) {   //nΪ����
			getline(cin, s);   //����ÿ������
			int lastpos = -1;
			for(int j = 0; j < m; j++) {  //mΪ����
				int p = s.find(',', lastpos+1);    //��lastpos+1��ʼ���ҡ����� pΪ����λ��
				if(p == string::npos) p = s.length();//string::npos����Ϊ��֤�����κ���Ч�±��ֵ��������Ҳ���
				db[i][j] = ID(s.substr(lastpos+1, p - lastpos - 1));//�������ַ�������ָ��λ�ÿ�ʼ����ָ�����ȡ�
				lastpos = p;
			}//��ȫ����ÿһ������
		}
		find();
	}
	return 0;
}
