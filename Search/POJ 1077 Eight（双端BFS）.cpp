#include <iostream>
#include <bitset>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <algorithm>
using namespace std;
int goalStatus; //目标状态
const int MAXS = 400000;
char result[MAXS]; //要输出的移动方案
struct Node {
    int status; //状态
    int father; //父节点指针，即myQueue的下标
    char move; //父节点到本节点的移动方式 u/d/r/l
    Node(int s,int f,char m):status(s), father(f),move( m) { }
    Node() { }
};
Node myQueue[2][MAXS]; //两个方向的状态队列，状态总数362880
int matchingStatus; //双向碰到的那个状态
int matchingQ; // 队列matchingQ的队头元素是双向碰到的那个状态
int qHead[2]; //队头指针
int qTail[2]; //队尾指针
char sz4Moves[] = "udrl"; //四种移动
void IntStatusToStrStatus( int n, char * strStatus)
{
    sprintf(strStatus,"%09d",n); //需要保留前导0
}
int NewStatus( int status, char cMove) {
    //求从status经过 cMove 移动后得到的新状态。若移动不可行则返回-1
    char szTmp[20];
    int zeroPos; //字符'0'的位置
    IntStatusToStrStatus(status,szTmp);
    for( int i = 0;i < 9; ++ i )
        if( szTmp[i] == '0' ) {
            zeroPos = i;
            break;
        } //返回空格的位置
    switch( cMove) {
        case 'u':
            if( zeroPos - 3 < 0 )
                return -1; //空格在第一行
            else {
                szTmp[zeroPos] = szTmp[zeroPos - 3];
                szTmp[zeroPos - 3] = '0';
            }
            break;
        case 'd':
            if( zeroPos + 3 > 8 )
                return -1; //空格在第三行
            else {
                szTmp[zeroPos] = szTmp[zeroPos + 3];
                szTmp[zeroPos + 3] = '0';
            }
            break;
        case 'l':
            if( zeroPos % 3 == 0)
                return -1; //空格在第一列
            else {
                szTmp[zeroPos] = szTmp[zeroPos -1];
                szTmp[zeroPos -1 ] = '0';
            }
            break;
        case 'r':
            if( zeroPos % 3 == 2)
                return -1; //空格在第三列
            else {
                szTmp[zeroPos] = szTmp[zeroPos + 1];
                szTmp[zeroPos + 1 ] = '0';
            }
            break;
    }
    return atoi(szTmp);
}
inline char ReverseMove(char c) {
    switch( c) {
        case 'u': return 'd';
        case 'l': return 'r';
        case 'r': return 'l';
        case 'd': return 'u';
    }
    return 0;
}
bool DBfs(int status){
    //寻找从初始状态status到目标的路径，找不到则返回false
    int newStatus;
    set<int> expanded[2];
    for( int i = 0;i < 2; ++ i ) {
        qHead[i] = 0; qTail[i] = 1;
    }
    myQueue[0][0] = Node(status,-1,0);
    expanded[0].insert(status);
    myQueue[1][0] = Node(goalStatus,-1,0);
    expanded[1].insert(goalStatus);
    while ( qHead[0] != qTail[0] ||
            qHead[1] != qTail[1] ) { //两个队列不都为空
        int qNo; //本次要扩展的队列
        if( qHead[0] == qTail[0])
            qNo = 1;
        else if( qHead[1] == qTail[1])
            qNo = 0;
        else {
            if( qTail[0] - qHead[0]
                    < qTail[1] - qHead[1] ) //比较两个队列元素个数
                qNo = 0;
            else
                qNo = 1;
        }
        int vqNo = 1 - qNo; //另一队列
        status = myQueue[qNo][qHead[qNo]].status;
        if(expanded[vqNo].find(status)!=
                expanded[vqNo].end()) {
            //status在另一队列扩展过，路径找到
            matchingStatus = status;
            matchingQ = qNo;
            return true;
        }
        else {
            for( int i = 0;i < 4;i ++ ) { //尝试4种移动
                newStatus = NewStatus(status,sz4Moves[i]);
                if( newStatus == -1 )
                    continue; //不可移，试下一种
                if(expanded[qNo].find(newStatus)!=expanded[qNo].end())
                    continue; //如果已经扩展过，则不能入队
                expanded[qNo].insert(newStatus);
                myQueue[qNo][qTail[qNo]] = Node(newStatus,qHead[qNo],sz4Moves[i]);
                qTail[qNo] ++;
            }
            qHead[qNo] ++;
        }
    }
    return false;
}
int main()
{
    char line1[50]; char line2[20];
    while(cin.getline(line1,48) ) {
        //将输入的原始字符串变为数字字符串
        int i,j;
        for( i = 0, j = 0; line1[i]; i ++ ) {
            if( line1[i] != ' ' ) {
                if( line1[i] == 'x' ) line2[j++] = '0';
                else line2[j++] = line1[i];
            }
        }
        line2[j] = 0;//字符串形式的初始状态
        //用奇偶性判定是否有解
        int sumGoal = 0;
        for( int i = 0;i < 8; ++i )
            sumGoal += i -1;
        int sumStart = 0;
        for( int i = 0;i < 9 ; ++i ) {
            if( line2[i] == '0')
                continue;
            for( int j = 0; j < i; ++j ) {
                if( line2[j] < line2[i] && line2[j] != '0' )
                    sumStart ++;
            }
        }
        if( sumStart %2 != sumGoal %2 ) {
            cout << "unsolvable" << endl;
            continue;
        }
        goalStatus = atoi("123456780");
        if(DBfs(atoi(line2))) {
            int moves = 0;
            int pos;
            if( matchingQ == 0)
                pos = qHead[0];
            else {
                for( int i = 0;i < qTail[0]; ++ i )
                    if( myQueue[0][i].status == matchingStatus ) {
                        pos = i;
                        break;
                    }
            }
            do {
                if( pos ) {
                    result[moves++] = myQueue[0][pos].move;
                    pos = myQueue[0][pos].father;
                }
            } while(pos);
            reverse(result,result+moves);
            if( matchingQ == 0) {
                for( int i = 0;i < qTail[1]; ++ i )
                    if( myQueue[1][i].status == matchingStatus ) {
                        pos = i;
                        break;
                    }
            }
            else
                pos = qHead[1];
            do {
                if(pos) {
                    result[moves++] = ReverseMove( myQueue[1][pos].move);
                    pos = myQueue[1][pos].father;
                }
            }while(pos);
            for( int i = 0;i < moves ; ++ i )
                cout << result[i];
            cout << endl;
        }
        else
            cout << "unsolvable" << endl;
    }
    return 0;
}
