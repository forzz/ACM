#include <iostream>
#include <cstring>

using namespace std;

char TF[27];
char TM[27];

void TL( int p1, int p2, int q1, int q2, int root )  //起点终点根节点
{
	if ( p1 > p2 ) return;
	for ( root = q1 ; TM[root] != TF[p1] ; ++ root );//root为中序遍历根节点
	TL( p1+1, p1+root-q1, q1, root-1, 0 );
	TL( p1+root-q1+1, p2, root+1, q2, 0 );
	cout << TM[root];
}

int main()
{
	while ( cin >> TF >> TM ) {
		int L = strlen(TF)-1;
		TL( 0, L, 0, L, 0 );
		cout << endl;
	}
	return 0;
}
